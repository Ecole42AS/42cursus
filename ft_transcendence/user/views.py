from django.shortcuts import render # permet de render les templates HTML
from rest_framework import generics, permissions # permet de créer des vues génériques et de gérer les permissions
from .serializers import UserSerializer
from .serializers import UserProfileSerializer
from django.contrib.auth.models import User

# INSCRIPTION (queryset, serializer_class, permission_classes sont des attributs de classe) 
class RegisterView(generics.CreateAPIView):
    queryset = User.objects.all() # récupère tous les utilisateurs (requête SQL ORM)
    serializer_class = UserSerializer
    permission_classes = [permissions.AllowAny] # autorise les utilisateurs non authentifiés à accéder à la vue

# Profil Utilisateur
class UserProfileView(generics.RetrieveUpdateAPIView):
    serializer_class = UserProfileSerializer
    permission_classes = [permissions.IsAuthenticated] # autorise uniquement les utilisateurs authentifiés à accéder à la vue

    def get_object(self):
        return self.request.user
