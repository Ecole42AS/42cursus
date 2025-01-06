import logging
from rest_framework import viewsets, permissions
from .models import GameSession, Tournament, TournamentMatch
from .serializers import GameSerializer, TournamentSerializer, TournamentMatchSerializer
from rest_framework.views import APIView
from rest_framework.response import Response
from rest_framework.permissions import IsAuthenticated
from django.db.models import Q
from rest_framework import status
from .utils import update_player_stats, get_user_profile, validate_user_token
from django.utils.timezone import now
from rest_framework_simplejwt.authentication import JWTAuthentication
from rest_framework.exceptions import AuthenticationFailed
 

import logging


logger = logging.getLogger('matchtracker-service')

def example_function():
    logger.debug("Ceci est un message DEBUG.")
    logger.info("Ceci est un message INFO.")
    logger.warning("Ceci est un message WARNING.")
    logger.error("Ceci est un message ERROR.")



# logger = logging.getLogger(__name__)

# def update_player_stats(winner, loser):
#     """
#     Met à jour les statistiques des joueurs après chaque partie.
#     """
#     winner_profile = Profile.objects.get(user=winner)
#     loser_profile = Profile.objects.get(user=loser)
#     winner_profile.wins += 1
#     loser_profile.losses += 1
#     winner_profile.save()
#     loser_profile.save()


from rest_framework.exceptions import AuthenticationFailed
from .utils import validate_user_token

class GameViewSet(viewsets.ModelViewSet):
    """
    ViewSet pour gérer les sessions de jeu.
    """
    queryset = GameSession.objects.all()
    serializer_class = GameSerializer
    permission_classes = [permissions.IsAuthenticated]  # JWTAuthentication s'exécute automatiquement

    def get_queryset(self):
        """
        Filtre les parties pour l'utilisateur authentifié.
        """
        user = self.request.user
        if not user or not user.is_authenticated:
            raise AuthenticationFailed("User not authenticated")

        logger.debug(f"Filtering games for user_id: {user.id}")

        return GameSession.objects.filter(
            Q(player1_id=user.id) | Q(player2_id=user.id)
        )

class CreateGameSessionView(APIView):
    """
    Vue pour créer une nouvelle session de jeu.
    """
    permission_classes = [IsAuthenticated]
    authentication_classes = [JWTAuthentication]

    def post(self, request, user_id):
        try:
            user = request.user  # Utilisateur extrait depuis le token JWT
            if not user:
                raise AuthenticationFailed("User not authenticated")

            # Passez le token JWT au User Service
            opponent_data = get_user_profile(user_id, request.auth)
            if not opponent_data:
                return Response({'error': 'Utilisateur non trouvé.'}, status=status.HTTP_404_NOT_FOUND)

            if user.id == user_id:
                return Response({'error': 'Vous ne pouvez pas jouer contre vous-même.'}, status=status.HTTP_400_BAD_REQUEST)

            existing_game = GameSession.objects.filter(
                Q(player1_id=user.id, player2_id=user_id) |
                Q(player1_id=user_id, player2_id=user.id),
                is_active=True
            ).first()

            if existing_game:
                return Response({'error': 'Un match est déjà en cours entre ces deux joueurs.'}, status=status.HTTP_400_BAD_REQUEST)

            game_session = GameSession.objects.create(player1_id=user.id, player2_id=user_id)
            serializer = GameSerializer(game_session)
            return Response(serializer.data, status=status.HTTP_201_CREATED)
        except Exception as e:
            logger.error(f"Erreur lors de la création du match : {e}")
            return Response({'error': 'Une erreur est survenue.'}, status=status.HTTP_500_INTERNAL_SERVER_ERROR)

class UpdateGameScoreView(APIView):
    """
    Vue pour mettre à jour le score d'une session de jeu.
    """
    permission_classes = [IsAuthenticated]
    authentication_classes = [JWTAuthentication]

    def post(self, request, game_id):
        try:
            # Assurez-vous que l'utilisateur est authentifié via JWT
            user = request.user
            if not user:
                raise AuthenticationFailed("User authentication failed")

            # Récupérer la session de jeu
            game = GameSession.objects.get(pk=game_id)

            if not game.is_active:
                return Response(
                    {'error': 'Ce match est terminé. Les scores ne peuvent pas être modifiés.'},
                    status=status.HTTP_400_BAD_REQUEST
                )

            # Vérifier si l'utilisateur participe à ce match
            if user.id not in [game.player1_id, game.player2_id]:
                return Response(
                    {'error': 'Vous ne participez pas à ce match.'},
                    status=status.HTTP_403_FORBIDDEN
                )

            # Mise à jour du score
            player_score = request.data.get('score')
            if player_score is None:
                return Response({'error': 'Score non fourni.'}, status=status.HTTP_400_BAD_REQUEST)

            if user.id == game.player1_id:
                game.score_player1 = player_score
            else:
                game.score_player2 = player_score

            # Vérifier le temps écoulé
            if (now() - game.start_time).total_seconds() >= 60:
                game.is_active = False
                game.ended_at = now()

                if game.score_player1 > game.score_player2:
                    game.winner_id = game.player1_id
                elif game.score_player2 > game.score_player1:
                    game.winner_id = game.player2_id
                else:
                    game.winner_id = None  # Match nul

                game.save()

                if game.winner_id:
                    update_player_stats(
                        game.winner_id,
                        game.player1_id if game.winner_id == game.player2_id else game.player2_id
                    )

            game.save()
            return Response({'detail': 'Score mis à jour.'})
        except GameSession.DoesNotExist:
            return Response({'error': 'Match non trouvé.'}, status=status.HTTP_404_NOT_FOUND)


class TournamentViewSet(viewsets.ModelViewSet):
    """
    ViewSet pour gérer les actions CRUD des tournois.
    """
    queryset = Tournament.objects.all()
    serializer_class = TournamentSerializer
    permission_classes = [permissions.IsAuthenticated]
    authentication_classes = [JWTAuthentication]

    def perform_create(self, serializer):
        creator_id = self.request.user.id  # Récupération depuis JWT
        serializer.save(creator_id=creator_id)


class TournamentMatchViewSet(viewsets.ModelViewSet):
    """
    ViewSet pour gérer les actions CRUD des matchs de tournoi.
    """
    queryset = TournamentMatch.objects.all()
    serializer_class = TournamentMatchSerializer
    permission_classes = [permissions.IsAuthenticated]
    authentication_classes = [JWTAuthentication]

    def perform_create(self, serializer):
        """
        Si nécessaire, ajoutez la logique pour enregistrer l'utilisateur créateur.
        """
        creator_id = self.request.user.id  # Récupère l'ID depuis le token JWT
        serializer.save(creator_id=creator_id)


class MatchHistoryView(APIView):
    """
    Vue pour récupérer l'historique des matchs d'un utilisateur.
    """
    permission_classes = [IsAuthenticated]
    authentication_classes = [JWTAuthentication]

    def get(self, request):
        user_id = request.user.id  # Extrait depuis le JWT
        game_sessions = GameSession.objects.filter(
            Q(player1_id=user_id) | Q(player2_id=user_id),
            is_active=False
        ).order_by('-ended_at')
        serializer = GameSerializer(game_sessions, many=True)
        return Response(serializer.data)

from django.http import HttpResponse

def test_redis_session(request):
    # Lire la clé existante ou la définir si elle n'existe pas
    if 'unique_key' not in request.session:
        request.session['unique_key'] = "my-default-unique-key"

    value = request.session.get('unique_key', 'default')
    return HttpResponse(f"Session unique_key is: {value}")
