from rest_framework import viewsets, permissions
from .models import GameSession
from .serializers import GameSerializer

class GameViewSet(viewsets.ModelViewSet): # viewset DRF gère les actions CRUD (list, retrieve, create, update, delete)
    queryset = GameSession.objects.all()
    serializer_class = GameSerializer
    permission_classes = [permissions.IsAuthenticated]

    def get_queryset(self): # surcharge de la méthode get_queryset pour filtrer les parties en fonction de l'utilisateur connecté et impliqué (soit user1, soit user2)
        return GameSession.objects.filter(player1=self.request.user) | GameSession.objects.filter(player2=self.request.user)
