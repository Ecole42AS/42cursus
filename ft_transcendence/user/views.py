from django.shortcuts import render # permet de render les templates HTML
from rest_framework import generics, permissions, status # permet de créer des vues génériques et de gérer les permissions
from .serializers import UserSerializer, ProfileSerializer
from django.contrib.auth.models import User
from rest_framework.parsers import MultiPartParser, FormParser, JSONParser
from rest_framework.views import APIView
from rest_framework.response import Response
from django.db import IntegrityError
from .models import Friendship


# Register (queryset, serializer_class, permission_classes sont des attributs de classe) 
class RegisterView(generics.CreateAPIView):
    queryset = User.objects.all() # récupère tous les utilisateurs (requête SQL ORM)
    serializer_class = UserSerializer
    permission_classes = [permissions.AllowAny] # autorise les utilisateurs non authentifiés à accéder à la vue
    parser_classes = (JSONParser, MultiPartParser, FormParser)

# Profil Utilisateur
class UserProfileView(generics.RetrieveUpdateAPIView):
    serializer_class = ProfileSerializer
    permission_classes = [permissions.IsAuthenticated] # autorise uniquement les utilisateurs authentifiés à accéder à la vue
    parser_classes = (MultiPartParser, FormParser) # permet de gérer les fichiers envoyés avec la requête

    def get_object(self):
        return self.request.user.profile

class AddFriendView(APIView):
    permission_classes = [permissions.IsAuthenticated]

    def post(self, request, user_id):
        try:
            to_user = User.objects.get(pk=user_id)
            Friendship.objects.create(from_user=request.user, to_user=to_user)
            return Response({'status': 'Ami ajouté'}, status=status.HTTP_201_CREATED)
        except User.DoesNotExist:
            return Response({'error': 'Utilisateur non trouvé'}, status=status.HTTP_404_NOT_FOUND)
        except IntegrityError:
            return Response({'error': 'Déjà ami'}, status=status.HTTP_400_BAD_REQUEST)

class FriendsListView(APIView):
    # Liste des amis de l'utilisateur authentifié
    permission_classes = [permissions.IsAuthenticated]

    def get(self, request):
        friendships = request.user.friendships.all()
        serializer = UserSerializer([f.to_user for f in friendships], many=True)
        return Response(serializer.data)
