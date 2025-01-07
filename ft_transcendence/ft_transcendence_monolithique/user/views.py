from django.shortcuts import render
from rest_framework import generics, permissions, status
from .serializers import UserSerializer, ProfileSerializer
from rest_framework.parsers import MultiPartParser, FormParser, JSONParser
from rest_framework.views import APIView
from rest_framework.response import Response
from django.db import IntegrityError
from .models import Friendship
from django.contrib.auth import get_user_model
from django.shortcuts import get_object_or_404
from rest_framework.exceptions import NotFound


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


class UserProfileView(generics.RetrieveUpdateAPIView):  
    serializer_class = ProfileSerializer
    permission_classes = [permissions.IsAuthenticated]
    parser_classes = (MultiPartParser, FormParser, JSONParser)

    def get_object(self):
        try:
            
            return self.request.user.profile
        except AttributeError:
            raise NotFound("Profile not found for the authenticated user.")

class AddFriendView(APIView):
    permission_classes = [permissions.IsAuthenticated]

    def post(self, request, user_id):
        try:
            to_user = CustomUser.objects.get(pk=user_id)
            
            if request.user == to_user:
                return Response({'error': 'Vous ne pouvez pas vous ajouter en tant qu’ami.'}, status=status.HTTP_400_BAD_REQUEST)
            
            Friendship.objects.create(from_user=request.user, to_user=to_user)
            return Response({'status': 'Ami ajouté avec succès'}, status=status.HTTP_201_CREATED)
        except CustomUser.DoesNotExist:
            return Response({'error': 'Utilisateur non trouvé'}, status=status.HTTP_404_NOT_FOUND)
        except IntegrityError:
            return Response({'error': 'Vous êtes déjà ami avec cet utilisateur.'}, status=status.HTTP_400_BAD_REQUEST)

class FriendsListView(APIView):
    permission_classes = [permissions.IsAuthenticated]

    def get(self, request):
        friendships = request.user.friendships.all()
        serializer = UserSerializer([f.to_user for f in friendships], many=True)
        return Response(serializer.data)
