import logging
from rest_framework import viewsets, permissions
from .models import GameSession, Tournament, TournamentMatch
from .serializers import GameSerializer, TournamentSerializer, TournamentMatchSerializer
from rest_framework.views import APIView
from rest_framework.response import Response
from django.db.models import Q
from rest_framework import status
from .utils import update_player_stats, get_user_profile, validate_user_token, get_user
from django.utils.timezone import now
from rest_framework_simplejwt.authentication import JWTAuthentication
from rest_framework.exceptions import AuthenticationFailed
from django.http import HttpResponse
from rest_framework.decorators import action
from rest_framework.permissions import IsAuthenticated
from .utils import  update_scores_and_stats
from channels.layers import get_channel_layer
from asgiref.sync import async_to_sync

import logging

logger = logging.getLogger('matchtracker-service')

def log_test_view(request):
    logger.debug("Test DEBUG log")
    logger.info("Test INFO log")
    logger.warning("Test WARNING log")
    logger.error("Test ERROR log")
    logger.critical("Test CRITICAL log")
    return HttpResponse("Logs testés.")

class TestUserView(APIView):
    def get(self, request):
        user = getattr(request, 'user', None)
        logger.debug(f"User in TestUserView: {user}")
        if user:
            return Response({"message": f"User {user.username} authenticated"})
        return Response({"error": "User not authenticated"}, status=401)

from rest_framework.exceptions import AuthenticationFailed
from .utils import validate_user_token

class GameViewSet(viewsets.ModelViewSet):
    queryset = GameSession.objects.all()
    serializer_class = GameSerializer

    permission_classes = [IsAuthenticated]

    def get_queryset(self):
        user = self.request.user
        logger.debug(f"GameViewSet: Requête reçue pour user={user}, is_authenticated={getattr(user, 'is_authenticated', False)}")

        if not user or not user.is_authenticated:
            logger.warning("GameViewSet: Utilisateur non authentifié")
            raise AuthenticationFailed("User not authenticated")

        logger.debug(f"GameViewSet: Filtrage des parties pour user_id={user.id}")
        games = GameSession.objects.filter(
            Q(player1_id=user.id) | Q(player2_id=user.id)
        )
        logger.debug(f"GameViewSet: {games.count()} parties trouvées pour user_id={user.id}")
        return games

class TestGamesNoPermissionsView(APIView):
    def get(self, request):
        user = request.user
        logger.debug(f"TestGamesNoPermissionsView: user={user}, is_authenticated={getattr(user, 'is_authenticated', False)}")
        games = GameSession.objects.filter(
            Q(player1_id=user.id) | Q(player2_id=user.id)
        )
        logger.debug(f"TestGamesNoPermissionsView: {games.count()} parties trouvées pour user_id={user.id}")
        return Response({"games_count": games.count()})

class TestGamesView(APIView):
    def get(self, request):
        user = request.user
        logger.debug(f"TestGamesView: Requête reçue pour user={user}, is_authenticated={getattr(user, 'is_authenticated', False)}")
        if not user or not user.is_authenticated:
            return Response({"error": "User not authenticated"}, status=401)

        games = GameSession.objects.filter(
            Q(player1_id=user.id) | Q(player2_id=user.id)
        )
        return Response({"games_count": games.count()})

class TestGamesQueryView(APIView):
    def get(self, request):
        user = request.user
        logger.debug(f"TestGamesQueryView: Requête reçue pour user={user}, is_authenticated={getattr(user, 'is_authenticated', False)}")
        if not user or not user.is_authenticated:
            return Response({"error": "User not authenticated"}, status=401)

        games = GameSession.objects.filter(
            Q(player1_id=user.id) | Q(player2_id=user.id)
        )
        logger.debug(f"TestGamesQueryView: {games.count()} parties trouvées pour user_id={user.id}")
        return Response({"games_count": games.count()})

class CreateGameSessionView(APIView):
    """
    Vue pour créer une nouvelle session de jeu.
    """

    permission_classes = [IsAuthenticated]

    def post(self, request, user_id):
        """
        Endpoint pour créer une session de jeu entre deux utilisateurs.
        """
        logger.info(f"CreateGameSessionView.post called for user {getattr(request.user, 'id', None)} and opponent {user_id}")
        try:

            user = request.user
            if not user or not getattr(user, 'is_authenticated', False):
                logger.error("No authenticated user found on the request")
                raise AuthenticationFailed("User not authenticated")

            logger.debug(f"Fetching opponent data for user_id={user_id}")
            opponent_data = get_user(user_id, request.auth)
            if not opponent_data:
                logger.warning(f"Opponent with user_id={user_id} not found in User Service")
                return Response({'error': 'Utilisateur non trouvé.'}, status=404)

            logger.debug(f"Opponent data retrieved: {opponent_data}")

            if user.id == user_id:
                logger.warning("User attempted to create a game against themselves")
                return Response({'error': 'Vous ne pouvez pas jouer contre vous-même.'}, status=400)

            logger.debug(f"Checking for existing active games between user {user.id} and {user_id}")
            existing_game = GameSession.objects.filter(
                Q(player1_id=user.id, player2_id=user_id) |
                Q(player1_id=user_id, player2_id=user.id),
                is_active=True
            ).first()

            if existing_game:
                logger.warning(f"An active game already exists between user {user.id} and {user_id}")
                serializer = GameSerializer(existing_game, context={'request': request})
                return Response(
                    {'error': 'Un match est déjà en cours entre ces deux joueurs.', 'active_game': serializer.data},
                    status=400
                )

            logger.debug(f"Creating a new game session between user {user.id} and {user_id}")
            game_session = GameSession.objects.create(player1_id=user.id, player2_id=user_id)
            serializer = GameSerializer(game_session)

            notification_data = {
                "game_session_id": game_session.id,
                "player1": game_session.player1_id,
                "player2": game_session.player2_id,
                "start_time": game_session.start_time.isoformat() if game_session.start_time else None,
                "duration": game_session.duration,
            }
            channel_layer = get_channel_layer()
            async_to_sync(channel_layer.group_send)(
                "game_sessions",
                {
                    "type": "game_session.start",
                    "data": notification_data,
                }
            )

            logger.info(f"Game session created successfully: {serializer.data}")
            return Response(serializer.data, status=201)

        except AuthenticationFailed as auth_error:
            logger.error(f"Authentication failed: {auth_error}")
            return Response({'error': 'Authentification échouée.'}, status=401)
        except Exception as e:
            logger.error(f"Unexpected error during game creation: {e}")
            return Response({'error': 'Une erreur est survenue.'}, status=500)

class UpdateGameScoreView(APIView):
    """
    Vue pour mettre à jour le score d'une session de jeu.
    """

    permission_classes = [IsAuthenticated]

    def post(self, request, game_id):
        logger.debug(f"Requête reçue pour mettre à jour le score du jeu {game_id}.")
        try:

            score_player1 = request.data.get('score_player1')
            score_player2 = request.data.get('score_player2')
            if score_player1 is None or score_player2 is None:
                logger.warning("Scores non fournis dans la requête.")
                return Response({'error': 'Les scores doivent être fournis.'}, status=status.HTTP_400_BAD_REQUEST)

            try:
                score_player1 = int(score_player1)
                score_player2 = int(score_player2)
                logger.debug(f"Scores reçus : Player1={score_player1}, Player2={score_player2}")
            except ValueError:
                logger.warning(f"Scores invalides fournis : {score_player1}, {score_player2}")
                return Response({'error': 'Scores invalides. Ils doivent être des entiers.'}, status=status.HTTP_400_BAD_REQUEST)

            result = update_scores_and_stats(game_id, score_player1, score_player2)
            return Response(result, status=status.HTTP_200_OK)

        except Exception as e:
            logger.error(f"Erreur inattendue : {e}")
            return Response({'error': 'Erreur interne du serveur.'}, status=status.HTTP_500_INTERNAL_SERVER_ERROR)

class TournamentViewSet(viewsets.ModelViewSet):
    """
    ViewSet pour gérer les actions CRUD des tournois.
    """
    queryset = Tournament.objects.all()
    serializer_class = TournamentSerializer

    permission_classes = [IsAuthenticated]

class TournamentMatchViewSet(viewsets.ModelViewSet):
    """
    ViewSet pour gérer les actions CRUD des matchs de tournoi.
    """
    queryset = TournamentMatch.objects.all()
    serializer_class = TournamentMatchSerializer

    permission_classes = [IsAuthenticated]

    def perform_create(self, serializer):
        """
        Si nécessaire, ajoutez la logique pour enregistrer l'utilisateur créateur.
        """
        creator_id = self.request.user.id
        serializer.save(creator_id=creator_id)

class MatchHistoryView(APIView):
    """
    Vue pour récupérer l'historique des matchs d'un utilisateur.
    """
    permission_classes = [IsAuthenticated]

    def get(self, request):
        user_id = request.user.id
        logger.debug(f"Fetching match history for user_id={user_id}")

        game_sessions = GameSession.objects.filter(
            Q(player1_id=user_id) | Q(player2_id=user_id),
            is_active=False
        ).order_by('-ended_at')
        logger.debug(f"Found {game_sessions.count()} matches for user_id={user_id}")

        serializer = GameSerializer(game_sessions, many=True, context={'request': request})

        return Response(serializer.data)

from django.http import HttpResponse

def test_redis_session(request):

    if 'unique_key' not in request.session:
        request.session['unique_key'] = "my-default-unique-key"

    value = request.session.get('unique_key', 'default')
    return HttpResponse(f"Session unique_key is: {value}")
