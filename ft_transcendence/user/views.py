from django.shortcuts import render # permet de render les templates HTML
from rest_framework import generics, permissions, status # permet de créer des vues génériques et de gérer les permissions
from .serializers import UserSerializer, ProfileSerializer
from rest_framework.parsers import MultiPartParser, FormParser, JSONParser
from rest_framework.views import APIView
from rest_framework.response import Response
from django.db import IntegrityError
from .models import Friendship
from django.contrib.auth import get_user_model


CustomUser = get_user_model()

# Les classes sont appelées lorsqu'une requête HTTP est envoyée à l'URL correspondante

# Register (queryset, serializer_class, permission_classes sont des attributs de classe) 
class RegisterView(generics.CreateAPIView): # CreateAPIView : Vue générique pour créer un objet (POST)
    queryset = CustomUser.objects.all() # récupère tous les utilisateurs (requête SQL ORM)
    serializer_class = UserSerializer
    permission_classes = [permissions.AllowAny] # autorise les utilisateurs non authentifiés à accéder à la vue
    parser_classes = (JSONParser, MultiPartParser, FormParser)

# User Update
class UserUpdateView(generics.UpdateAPIView): # méthode PUT
    serializer_class = UserSerializer
    permission_classes = [permissions.IsAuthenticated]

    def get_object(self): # surcharge de la méthode get_object pour renvoyer l'utilisateur authentifiée (par défaut, la méthode get_object renvoie l'objet correspondant à la clé primaire de l'URL)
        return self.request.user


# Profil Utilisateur
class UserProfileView(generics.RetrieveUpdateAPIView):# méthode GET et PUT
    serializer_class = ProfileSerializer
    permission_classes = [permissions.IsAuthenticated] # autorise uniquement les utilisateurs authentifiés à accéder à la vue
    parser_classes = (MultiPartParser, FormParser, JSONParser) # permet de gérer les fichiers envoyés avec la requête

    def get_object(self):
        return self.request.user.profile

class AddFriendView(APIView): # APIView : Vue de base pour définir manuellement les comportements des requêtes HTTP (GET, POST, etc.), si une méthode n'est pas définie, c'est qu'elle n'est pas autorisée
    permission_classes = [permissions.IsAuthenticated]

    def post(self, request, user_id):
        try:
            to_user = CustomUser.objects.get(pk=user_id)
            
            if request.user == to_user:
                return Response({'error': 'Vous ne pouvez pas vous ajouter en tant qu’ami.'}, status=status.HTTP_400_BAD_REQUEST)
            
            Friendship.objects.create(from_user=request.user, to_user=to_user) # ajout dans le modèle Friendship
            return Response({'status': 'Ami ajouté avec succès'}, status=status.HTTP_201_CREATED)
        except CustomUser.DoesNotExist:
            return Response({'error': 'Utilisateur non trouvé'}, status=status.HTTP_404_NOT_FOUND)
        except IntegrityError:
            return Response({'error': 'Vous êtes déjà ami avec cet utilisateur.'}, status=status.HTTP_400_BAD_REQUEST)

class FriendsListView(APIView):
    permission_classes = [permissions.IsAuthenticated]

    def get(self, request):
        friendships = request.user.friendships.all()
        serializer = UserSerializer([f.to_user for f in friendships], many=True) # many=True pour sérialiser une liste d'objets et pour chaque ami de l'utilisateur authentifié, on renvoie un objet UserSerializer
        return Response(serializer.data)
