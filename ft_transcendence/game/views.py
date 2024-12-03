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

    # def perform_create(self, serializer):
    #     user = self.request.user
    #     friends = serializer.validated_data.get('players')
    #     if len(friends) < 2:
    #         raise PermissionDenied("You must select at least two friends to create a tournament.")
    #     tournament = serializer.save(creator=user)
    #     tournament.players.add(user, *friends)
    #     generate_tournament_matches(tournament)

    
    def perform_create(self, serializer):
        user = self.request.user
        friends = serializer.validated_data.get('players')
        if len(friends) < 2:
            raise PermissionDenied("You must select at least two friends to create a tournament.")
        
        # Save the tournament instance without committing to the database
        tournament = serializer.save(commit=False)
        tournament.creator = user
        tournament.save()  # Save the instance first to get an ID
        
        # Add the players to the tournament
        tournament.players.add(user, *friends)
        
        # Validate the instance after adding the players
        tournament.clean()
        
        # Generate tournament matches
        generate_tournament_matches(tournament)

class TournamentMatchViewSet(viewsets.ModelViewSet):
    queryset = TournamentMatch.objects.all()
    serializer_class = TournamentMatchSerializer
    permission_classes = [permissions.IsAuthenticated]
