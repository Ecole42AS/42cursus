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

# class GameViewSet(viewsets.ModelViewSet):
#     queryset = GameSession.objects.all()
#     serializer_class = GameSerializer
    # authentication_classes = [JWTAuthentication]
#     permission_classes = [IsAuthenticated]  # Ajout de la vérification d'authentification

#     def get_queryset(self):
#         user = self.request.user
#         if not user or not user.is_authenticated:
#             raise AuthenticationFailed("User not authenticated")
#         return GameSession.objects.filter(
#             Q(player1_id=user.id) | Q(player2_id=user.id)
#         )

# class GameViewSet(viewsets.ModelViewSet):
#     """
#     ViewSet pour gérer les sessions de jeu.
#     """
#     queryset = GameSession.objects.all()
#     serializer_class = GameSerializer
    # authentication_classes = [JWTAuthentication]

#     @action(detail=True, methods=['patch'], url_path='end')
#     def end_game(self, request, pk=None):
#         game = self.get_object()

#         if not game.is_active:
#             return Response({'error': 'Le match est déjà terminé.'}, status=status.HTTP_400_BAD_REQUEST)

#         game.is_active = False
#         game.ended_at = now()
#         game.save()

#         return Response({'message': 'Le match a été terminé avec succès.'})

#     def get_queryset(self):
#         """
#         Filtre les parties pour l'utilisateur authentifié.
#         """
#         user = self.request.user
#         if not user or not user.is_authenticated:
#             raise AuthenticationFailed("User not authenticated")

#         logger.debug(f"Filtering games for user_id: {user.id}")

#         return GameSession.objects.filter(
#             Q(player1_id=user.id) | Q(player2_id=user.id)
#         )

class GameViewSet(viewsets.ModelViewSet):
    queryset = GameSession.objects.all()
    serializer_class = GameSerializer
    # authentication_classes = [JWTAuthentication]
    # Retirez temporairement les permissions
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

    # authentication_classes = [JWTAuthentication]
    permission_classes = [IsAuthenticated]  # Ajout de la vérification d'authentification

    def post(self, request, user_id):
        """
        Endpoint pour créer une session de jeu entre deux utilisateurs.
        """
        logger.info(f"CreateGameSessionView.post called for user {getattr(request.user, 'id', None)} and opponent {user_id}")
        try:
            # Vérifie si un utilisateur authentifié est attaché à la requête
            user = request.user
            if not user or not getattr(user, 'is_authenticated', False):
                logger.error("No authenticated user found on the request")
                raise AuthenticationFailed("User not authenticated")

            # Récupère les données de l'opposant via le microservice `user_service`
            logger.debug(f"Fetching opponent data for user_id={user_id}")
            opponent_data = get_user(user_id, request.auth)
            if not opponent_data:
                logger.warning(f"Opponent with user_id={user_id} not found in User Service")
                return Response({'error': 'Utilisateur non trouvé.'}, status=404)

            logger.debug(f"Opponent data retrieved: {opponent_data}")

            # Vérifie si l'utilisateur tente de jouer contre lui-même
            if user.id == user_id:
                logger.warning("User attempted to create a game against themselves")
                return Response({'error': 'Vous ne pouvez pas jouer contre vous-même.'}, status=400)

            # Vérifie l'existence d'une session de jeu active entre les deux utilisateurs
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
            
            # Crée une nouvelle session de jeu
            logger.debug(f"Creating a new game session between user {user.id} and {user_id}")
            game_session = GameSession.objects.create(player1_id=user.id, player2_id=user_id)
            serializer = GameSerializer(game_session)

            logger.info(f"Game session created successfully: {serializer.data}")
            return Response(serializer.data, status=201)

        except AuthenticationFailed as auth_error:
            logger.error(f"Authentication failed: {auth_error}")
            return Response({'error': 'Authentification échouée.'}, status=401)
        except Exception as e:
            logger.error(f"Unexpected error during game creation: {e}")
            return Response({'error': 'Une erreur est survenue.'}, status=500)

# class UpdateGameScoreView(APIView):
#     """
#     Vue pour mettre à jour le score d'une session de jeu.
#     """
#     permission_classes = [IsAuthenticated]  # Vérification d'authentification

#     def post(self, request, game_id):
#         logger.debug(f"Requête reçue pour mettre à jour le score du jeu {game_id} par l'utilisateur {request.user.id}")

#         try:
#             # Assurez-vous que l'utilisateur est authentifié
#             user = request.user
#             if not user or not user.is_authenticated:
#                 logger.error("Utilisateur non authentifié.")
#                 raise AuthenticationFailed("User authentication failed")

#             # Récupérer la session de jeu
#             try:
#                 game = GameSession.objects.get(pk=game_id)
#                 logger.debug(f"GameSession récupérée : {game}")
#             except GameSession.DoesNotExist:
#                 logger.warning(f"GameSession {game_id} non trouvée.")
#                 return Response({'error': 'Match non trouvé.'}, status=status.HTTP_404_NOT_FOUND)

#             # Vérifiez que le champ start_time est défini
#             if not game.start_time:
#                 logger.error("L'heure de début du match n'est pas définie.")
#                 return Response(
#                     {'error': "L'heure de début du match (start_time) n'est pas définie."},
#                     status=status.HTTP_500_INTERNAL_SERVER_ERROR
#                 )

#             # Vérifier que le match est actif
#             if not game.is_active:
#                 logger.warning(f"Match {game_id} déjà terminé.")
#                 return Response(
#                     {'error': 'Ce match est terminé. Les scores ne peuvent pas être modifiés.'},
#                     status=status.HTTP_400_BAD_REQUEST
#                 )

#             # Vérifier si l'utilisateur participe au match
#             if user.id not in [game.player1_id, game.player2_id]:
#                 logger.warning(f"L'utilisateur {user.id} ne participe pas au match {game_id}.")
#                 return Response(
#                     {'error': 'Vous ne participez pas à ce match.'},
#                     status=status.HTTP_403_FORBIDDEN
#                 )

#             # Extraire et valider le score depuis la requête
#             player_score = request.data.get('score')
#             if player_score is None:
#                 logger.warning("Score non fourni dans la requête.")
#                 return Response({'error': 'Score non fourni.'}, status=status.HTTP_400_BAD_REQUEST)

#             try:
#                 player_score = int(player_score)
#                 logger.debug(f"Score reçu : {player_score}")
#             except ValueError:
#                 logger.warning(f"Score invalide fourni : {player_score}")
#                 return Response({'error': 'Score invalide. Il doit être un entier.'}, status=status.HTTP_400_BAD_REQUEST)

#             # Mettre à jour le score du joueur correspondant
#             if user.id == game.player1_id:
#                 logger.debug(f"Score de player1 mis à jour par {user.id}")
#                 game.score_player1 = player_score
#             else:
#                 logger.debug(f"Score de player2 mis à jour par {user.id}")
#                 game.score_player2 = player_score

#             # Vérifiez si le match a dépassé la limite de temps
#             if (now() - game.start_time).total_seconds() >= 60:
#                 logger.info(f"Le match {game_id} dépasse la limite de temps. Il sera terminé.")
#                 game.is_active = False
#                 game.ended_at = now()

#                 # Déterminer le gagnant
#                 if game.score_player1 > game.score_player2:
#                     game.winner_id = game.player1_id
#                 elif game.score_player2 > game.score_player1:
#                     game.winner_id = game.player2_id
#                 else:
#                     game.winner_id = None  # Match nul

#                 logger.info(f"Match {game_id} terminé. Vainqueur : {game.winner_id if game.winner_id else 'Match nul'}.")

#                 # Mettre à jour les statistiques des joueurs
#                 if game.winner_id:
#                     logger.debug(f"Mise à jour des statistiques pour le vainqueur {game.winner_id}.")
#                     update_player_stats(
#                         winner_id=game.winner_id,
#                         loser_id=game.player1_id if game.winner_id == game.player2_id else game.player2_id
#                     )


#             # Enregistrer les modifications
#             game.save()
#             logger.info(f"Match {game_id} mis à jour avec succès.")
#             return Response({'detail': 'Score mis à jour.'}, status=status.HTTP_200_OK)

#         except AuthenticationFailed as auth_error:
#             logger.error(f"Authentification échouée : {auth_error}")
#             return Response({'error': 'Authentification échouée.'}, status=status.HTTP_401_UNAUTHORIZED)
#         except Exception as e:
#             logger.error(f"Erreur inattendue : {e}")
#             return Response({'error': 'Erreur interne du serveur.'}, status=status.HTTP_500_INTERNAL_SERVER_ERROR)


class UpdateGameScoreView(APIView):
    """
    Vue pour mettre à jour le score d'une session de jeu.
    """
    # Par exemple, on peut exiger simplement que l'utilisateur soit authentifié via un autre mécanisme
    permission_classes = [IsAuthenticated]

    def post(self, request, game_id):
        logger.debug(f"Requête reçue pour mettre à jour le score du jeu {game_id}.")
        try:
            # Extraire les scores depuis la requête
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

            # Mettre à jour le match et les scores
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
    # authentication_classes = [JWTAuthentication]
    permission_classes = [IsAuthenticated]  # Ajout de la vérification d'authentification

    # def perform_create(self, serializer):
    #     logger.debug(f"Création d'un tournoi par l'utilisateur {self.request.user.id}")
    #     serializer.save()


class TournamentMatchViewSet(viewsets.ModelViewSet):
    """
    ViewSet pour gérer les actions CRUD des matchs de tournoi.
    """
    queryset = TournamentMatch.objects.all()
    serializer_class = TournamentMatchSerializer
    # authentication_classes = [JWTAuthentication]
    permission_classes = [IsAuthenticated]  # Ajout de la vérification d'authentification

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
    permission_classes = [IsAuthenticated]  # Ajout de la vérification d'authentification

    def get(self, request):
        user_id = request.user.id  # Récupérer l'ID de l'utilisateur depuis le token JWT
        logger.debug(f"Fetching match history for user_id={user_id}")
        
        # Filtrer les parties terminées de l'utilisateur
        game_sessions = GameSession.objects.filter(
            Q(player1_id=user_id) | Q(player2_id=user_id),
            is_active=False
        ).order_by('-ended_at')
        logger.debug(f"Found {game_sessions.count()} matches for user_id={user_id}")

        # Ajouter la requête dans le contexte du sérialiseur pour transmettre le token JWT
        serializer = GameSerializer(game_sessions, many=True, context={'request': request})
        
        return Response(serializer.data)


from django.http import HttpResponse

def test_redis_session(request):
    # Lire la clé existante ou la définir si elle n'existe pas
    if 'unique_key' not in request.session:
        request.session['unique_key'] = "my-default-unique-key"

    value = request.session.get('unique_key', 'default')
    return HttpResponse(f"Session unique_key is: {value}")
