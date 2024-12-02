from rest_framework import viewsets, permissions
from .models import GameSession, Tournament, TournamentMatch
from .serializers import GameSerializer, TournamentSerializer, TournamentMatchSerializer
from .utils import generate_tournament_matches
from rest_framework.exceptions import PermissionDenied

class GameViewSet(viewsets.ModelViewSet): # viewset DRF gère les actions CRUD (list, retrieve, create, update, delete)
    queryset = GameSession.objects.all()
    serializer_class = GameSerializer
    permission_classes = [permissions.IsAuthenticated]

    def get_queryset(self): # surcharge de la méthode get_queryset pour filtrer les parties en fonction de l'utilisateur connecté et impliqué (soit user1, soit user2)
        return GameSession.objects.filter(player1=self.request.user) | GameSession.objects.filter(player2=self.request.user)
    
class TournamentViewSet(viewsets.ModelViewSet):
    queryset = Tournament.objects.all()
    serializer_class = TournamentSerializer
    permission_classes = [permissions.IsAuthenticated]

    def perform_create(self, serializer):
        tournament = serializer.save()
        generate_tournament_matches(tournament)

class TournamentMatchViewSet(viewsets.ModelViewSet):
    queryset = TournamentMatch.objects.all()
    serializer_class = TournamentMatchSerializer
    permission_classes = [permissions.IsAuthenticated]
