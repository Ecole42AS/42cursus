import logging
from rest_framework import viewsets, permissions
from .models import GameSession, Tournament, TournamentMatch
from .serializers import GameSerializer, TournamentSerializer, TournamentMatchSerializer
from rest_framework.views import APIView
from rest_framework.response import Response
from rest_framework.permissions import IsAuthenticated
from django.db.models import Q
from rest_framework import status
from .utils import update_player_stats, get_user_profile
from django.utils.timezone import now

 
logger = logging.getLogger(__name__)

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


class GameViewSet(viewsets.ModelViewSet):
    """
    ViewSet pour gérer les actions CRUD des sessions de jeu.
    """
    queryset = GameSession.objects.all()
    serializer_class = GameSerializer
    permission_classes = [permissions.IsAuthenticated]

    def get_queryset(self):
        """
        Surcharge de la méthode get_queryset pour filtrer les parties en fonction de l'utilisateur connecté et impliqué (soit user1, soit user2).
        """
        user_id = self.request.user.id

        return GameSession.objects.filter(
            Q(player1_id=user_id) | Q(player2_id=user_id)
        )

class CreateGameSessionView(APIView):
    """
    Vue pour créer une nouvelle session de jeu.
    """
    permission_classes = [IsAuthenticated]

    def post(self, request, user_id):
        try:
            opponent_data = get_user_profile(user_id)  # Récupérer les données utilisateur via le microservice
            if not opponent_data:
                return Response({'error': 'Utilisateur non trouvé.'}, status=status.HTTP_404_NOT_FOUND)

            if request.user.id == user_id:
                return Response({'error': 'Vous ne pouvez pas jouer contre vous-même.'}, status=status.HTTP_400_BAD_REQUEST)

            existing_game = GameSession.objects.filter(
                Q(player1_id=request.user.id, player2_id=user_id) |
                Q(player1_id=user_id, player2_id=request.user.id),
                is_active=True
            ).first()

            if existing_game:
                return Response({'error': 'Un match est déjà en cours entre ces deux joueurs.'}, status=status.HTTP_400_BAD_REQUEST)

            game_session = GameSession.objects.create(player1_id=request.user.id, player2_id=user_id)
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

    def post(self, request, game_id):
        try:
            game = GameSession.objects.get(pk=game_id)

            if not game.is_active:
                return Response({'error': 'Ce match est terminé. Les scores ne peuvent pas être modifiés.'}, status=status.HTTP_400_BAD_REQUEST)

            if request.user.id not in [game.player1_id, game.player2_id]:
                return Response({'error': 'Vous ne participez pas à ce match.'}, status=status.HTTP_403_FORBIDDEN)

            player_score = request.data.get('score')
            if player_score is None:
                return Response({'error': 'Score non fourni.'}, status=status.HTTP_400_BAD_REQUEST)

            # Mise à jour du score
            if request.user.id == game.player1_id:
                game.score_player1 = player_score
            else:
                game.score_player2 = player_score

            # Vérification du temps écoulé
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

                # Mettre à jour les stats si un gagnant est défini
                if game.winner_id:
                    update_player_stats(game.winner_id, game.player1_id if game.winner_id == game.player2_id else game.player2_id)

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

    def perform_create(self, serializer):
        creator_id = self.request.user.id
        serializer.save(creator_id=creator_id)


class TournamentMatchViewSet(viewsets.ModelViewSet):
    """
    ViewSet pour gérer les actions CRUD des matchs de tournoi.
    """
    queryset = TournamentMatch.objects.all()
    serializer_class = TournamentMatchSerializer
    permission_classes = [permissions.IsAuthenticated]

class MatchHistoryView(APIView):
    """
    Vue pour récupérer l'historique des matchs d'un utilisateur.
    """
    permission_classes = [IsAuthenticated]

    def get(self, request):
        user_id = request.user.id
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

from django.http import JsonResponse

def check_session(request):
    if request.user.is_authenticated:
        return JsonResponse({"status": "success", "user": request.user.username})
    else:
        return JsonResponse({"status": "error", "detail": "User not authenticated"}, status=403)
