from rest_framework import viewsets, permissions
from .models import GameSession, Tournament, TournamentMatch
from .serializers import GameSerializer, TournamentSerializer, TournamentMatchSerializer
from .utils import generate_tournament_matches
from rest_framework.exceptions import PermissionDenied
from user.models import Profile
from rest_framework.views import APIView
from rest_framework.response import Response
from rest_framework.permissions import IsAuthenticated
from django.db.models import Q
from user.models import Profile
from django.contrib.auth import get_user_model
from rest_framework import status
from django.utils import timezone

CustomUser = get_user_model()

def update_player_stats(winner, loser): # doit être appelée après chaque partie pour mettre à jour les statistiques des joueurs
    winner_profile = Profile.objects.get(user=winner)
    loser_profile = Profile.objects.get(user=loser)
    winner_profile.wins += 1
    loser_profile.losses += 1
    winner_profile.save()
    loser_profile.save()

class GameViewSet(viewsets.ModelViewSet): # viewset DRF gère les actions CRUD (list, retrieve, create, update, delete)
    queryset = GameSession.objects.all()
    serializer_class = GameSerializer
    permission_classes = [permissions.IsAuthenticated]

    def get_queryset(self): # surcharge de la méthode get_queryset pour filtrer les parties en fonction de l'utilisateur connecté et impliqué (soit user1, soit user2)
        return GameSession.objects.filter(player1=self.request.user) | GameSession.objects.filter(player2=self.request.user)


class CreateGameSessionView(APIView):
    permission_classes = [IsAuthenticated]

    def post(self, request, user_id):
        try:
            opponent = CustomUser.objects.get(pk=user_id)
            if request.user == opponent:
                return Response({'error': 'Vous ne pouvez pas jouer contre vous-même.'}, status=status.HTTP_400_BAD_REQUEST)

            # Vérifiez si un match actif existe déjà entre ces deux joueurs
            existing_game = GameSession.objects.filter(
                player1__in=[request.user, opponent],
                player2__in=[request.user, opponent],
                is_active=True
            ).first()

            if existing_game:
                return Response({'error': 'Un match est déjà en cours entre ces deux joueurs.'}, status=status.HTTP_400_BAD_REQUEST)

            game_session = GameSession.objects.create(player1=request.user, player2=opponent)
            serializer = GameSerializer(game_session)
            return Response(serializer.data, status=status.HTTP_201_CREATED)
        except CustomUser.DoesNotExist:
            return Response({'error': 'Utilisateur non trouvé.'}, status=status.HTTP_404_NOT_FOUND)


class UpdateGameScoreView(APIView):
    permission_classes = [IsAuthenticated]

    def post(self, request, game_id):
        try:
            game = GameSession.objects.get(pk=game_id)

            if not game.is_active:
                return Response({'error': 'Ce match est terminé. Les scores ne peuvent pas être modifiés.'}, status=status.HTTP_400_BAD_REQUEST)

            if request.user not in [game.player1, game.player2]:
                return Response({'error': 'Vous ne participez pas à ce match.'}, status=status.HTTP_403_FORBIDDEN)

            player_score = request.data.get('score')
            if player_score is None:
                return Response({'error': 'Score non fourni.'}, status=status.HTTP_400_BAD_REQUEST)

            if request.user == game.player1:
                game.score_player1 = player_score
            else:
                game.score_player2 = player_score

            if game.score_player1 >= 5 or game.score_player2 >= 5:
                game.is_active = False
                game.ended_at = timezone.now()

                if game.score_player1 > game.score_player2:
                    game.winner = game.player1
                    winner = game.player1
                    loser = game.player2
                else:
                    game.winner = game.player2
                    winner = game.player2
                    loser = game.player1

                game.save()
                update_player_stats(winner, loser)

                serializer = GameSerializer(game)
                return Response(serializer.data)

            game.save()
            return Response({'detail': 'Score mis à jour.'})
        except GameSession.DoesNotExist:
            return Response({'error': 'Match non trouvé.'}, status=status.HTTP_404_NOT_FOUND)



class TournamentViewSet(viewsets.ModelViewSet):
    queryset = Tournament.objects.all()
    serializer_class = TournamentSerializer
    permission_classes = [permissions.IsAuthenticated]

    def perform_create(self, serializer):
        serializer.save(creator=self.request.user)



class TournamentMatchViewSet(viewsets.ModelViewSet):
    queryset = TournamentMatch.objects.all()
    serializer_class = TournamentMatchSerializer
    permission_classes = [permissions.IsAuthenticated]

class MatchHistoryView(APIView):
    permission_classes = [IsAuthenticated]

    def get(self, request):
        user = request.user
        game_sessions = GameSession.objects.filter(
            Q(player1=user) | Q(player2=user),
            is_active=False
        ).order_by('-ended_at')
        serializer = GameSerializer(game_sessions, many=True)
        return Response(serializer.data)
