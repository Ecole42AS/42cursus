from django.shortcuts import render
from .serializers import UserSerializer, ProfileSerializer
from rest_framework import generics, permissions, status
from rest_framework.parsers import MultiPartParser, FormParser, JSONParser
from rest_framework.views import APIView
from rest_framework.response import Response
from rest_framework.permissions import IsAuthenticated
from django.db import IntegrityError
from .models import Friendship
from django.contrib.auth import get_user_model
from .models import Profile


CustomUser = get_user_model()


class RegisterView(generics.CreateAPIView):
    queryset = CustomUser.objects.all()
    serializer_class = UserSerializer
    permission_classes = [permissions.AllowAny]
    parser_classes = (JSONParser, MultiPartParser, FormParser)

class UserUpdateView(generics.UpdateAPIView):
    serializer_class = UserSerializer
    permission_classes = [permissions.IsAuthenticated]

    def get_object(self):
        return self.request.user


class UserProfileView(generics.RetrieveUpdateAPIView):# méthode GET et PUT
    serializer_class = ProfileSerializer
    permission_classes = [permissions.IsAuthenticated]
    parser_classes = (MultiPartParser, FormParser, JSONParser)

    def get_object(self):
        return self.request.user.profile

# class AddFriendView(APIView):
#     permission_classes = [permissions.IsAuthenticated]

#     def post(self, request, user_id):
#         try:
#             to_user = CustomUser.objects.get(pk=user_id)
            
#             if request.user == to_user:
#                 return Response({'error': 'Vous ne pouvez pas vous ajouter en tant qu’ami.'}, status=status.HTTP_400_BAD_REQUEST)
            
#             Friendship.objects.create(from_user=request.user, to_user=to_user)
#             return Response({'status': 'Ami ajouté avec succès'}, status=status.HTTP_201_CREATED)
#         except CustomUser.DoesNotExist:
#             return Response({'error': 'Utilisateur non trouvé'}, status=status.HTTP_404_NOT_FOUND)
#         except IntegrityError:
#             return Response({'error': 'Vous êtes déjà ami avec cet utilisateur.'}, status=status.HTTP_400_BAD_REQUEST)

class AddFriendView(APIView):
    permission_classes = [permissions.IsAuthenticated]

    def post(self, request, user_id):
        try:
            to_user = CustomUser.objects.get(pk=user_id)
            
            if request.user == to_user:
                return Response(
                    {'error': 'Vous ne pouvez pas vous ajouter en tant qu’ami.'},
                    status=status.HTTP_400_BAD_REQUEST
                )
            
            if Friendship.objects.filter(
                from_user=request.user, to_user=to_user
            ).exists() or Friendship.objects.filter(
                from_user=to_user, to_user=request.user
            ).exists():
                return Response(
                    {'error': 'Vous êtes déjà ami avec cet utilisateur.'},
                    status=status.HTTP_400_BAD_REQUEST
                )
            
            Friendship.objects.create(from_user=request.user, to_user=to_user)
            return Response({'status': 'Ami ajouté avec succès'}, status=status.HTTP_201_CREATED)
        
        except CustomUser.DoesNotExist:
            return Response(
                {'error': 'Utilisateur non trouvé'},
                status=status.HTTP_404_NOT_FOUND
            )

class FriendsListView(APIView):
    permission_classes = [permissions.IsAuthenticated]

    def get(self, request):
        friendships = request.user.friendships.all()
        serializer = UserSerializer([f.to_user for f in friendships], many=True)
        return Response(serializer.data)

class UserDetailView(APIView):
    permission_classes = [permissions.AllowAny]

    def get(self, request, user_id):
        try:
            user = CustomUser.objects.get(pk=user_id)
            serializer = UserSerializer(user)
            return Response(serializer.data, status=status.HTTP_200_OK)
        except CustomUser.DoesNotExist:
            return Response({'error': 'Utilisateur non trouvé'}, status=status.HTTP_404_NOT_FOUND)

# class UpdateUserStatsView(APIView):
#     """
#     Vue pour mettre à jour les statistiques d'un utilisateur (victoires et défaites).
#     """
#     permission_classes = [IsAuthenticated]

#     def patch(self, request, user_id):
#         try:
#             profile = Profile.objects.get(user_id=user_id)
#             wins = request.data.get('wins', 0)
#             losses = request.data.get('losses', 0)

#             profile.wins += int(wins)
#             profile.losses += int(losses)
#             profile.save()

#             serializer = ProfileSerializer(profile)
#             return Response(serializer.data, status=status.HTTP_200_OK)
#         except Profile.DoesNotExist:
#             return Response({'error': 'Profil non trouvé.'}, status=status.HTTP_404_NOT_FOUND)

class InternalUpdateStatsView(APIView):
    """
    Met à jour les statistiques des utilisateurs (wins et losses).
    Accessible uniquement aux services internes.
    """
    permission_classes = [permissions.IsAuthenticated]  # Utilisez un token interne sécurisé.

    def post(self, request):
        winner_id = request.data.get('winner_id')
        loser_id = request.data.get('loser_id')

        if not winner_id or not loser_id:
            return Response({"error": "IDs gagnant et perdant requis."}, status=status.HTTP_400_BAD_REQUEST)

        try:
            # Mettre à jour les statistiques
            winner_profile = Profile.objects.get(user_id=winner_id)
            winner_profile.wins += 1
            winner_profile.save()

            loser_profile = Profile.objects.get(user_id=loser_id)
            loser_profile.losses += 1
            loser_profile.save()

            return Response({"status": "Statistiques mises à jour avec succès."}, status=status.HTTP_200_OK)

        except Profile.DoesNotExist:
            return Response({"error": "Profil utilisateur non trouvé."}, status=status.HTTP_404_NOT_FOUND)


class UserProfileDetailView(APIView):
    """
    Vue pour récupérer les informations de profil d'un utilisateur spécifique.
    """
    permission_classes = [IsAuthenticated]

    def get(self, request, user_id):
        try:
            profile = Profile.objects.get(user_id=user_id)
            serializer = ProfileSerializer(profile)
            return Response(serializer.data, status=status.HTTP_200_OK)
        except Profile.DoesNotExist:
            return Response({'error': 'Profil non trouvé.'}, status=status.HTTP_404_NOT_FOUND)

class FriendshipStatusView(APIView):
    permission_classes = [permissions.AllowAny]

    def get(self, request, user1_id, user2_id):
        try:
            user1 = CustomUser.objects.get(pk=user1_id)
            user2 = CustomUser.objects.get(pk=user2_id)
            is_friend = Friendship.objects.filter(from_user=user1, to_user=user2).exists()
            return Response({'is_friend': is_friend}, status=status.HTTP_200_OK)
        except CustomUser.DoesNotExist:
            return Response({'error': 'Un ou plusieurs utilisateurs non trouvés'}, status=status.HTTP_404_NOT_FOUND)

class SearchUserView(APIView):
    permission_classes = [permissions.IsAuthenticated]

    def get(self, request):
        query = request.query_params.get('q', '')
        if not query:
            return Response({'error': 'Veuillez fournir une requête de recherche.'}, status=status.HTTP_400_BAD_REQUEST)
        
        users = CustomUser.objects.filter(username__icontains=query)[:10]
        serializer = UserSerializer(users, many=True)
        return Response(serializer.data)

from django.http import HttpResponse
from uuid import uuid4

def test_redis_session(request):
    session_key = str(uuid4())  # Créer une clé unique pour chaque session
    request.session['unique_key'] = session_key  # Ajouter une valeur unique dans la session
    request.session.save()  # Forcer la sauvegarde de la session
    return HttpResponse(f"Session unique_key is: {request.session['unique_key']}")
