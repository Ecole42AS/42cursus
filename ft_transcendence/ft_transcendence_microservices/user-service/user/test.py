
from django.urls import reverse
from rest_framework.test import APITestCase
from rest_framework import status
from .models import Profile, Friendship
from django.core.files.uploadedfile import SimpleUploadedFile
from django.utils import timezone
from PIL import Image
import io
from django.contrib.auth import get_user_model

class BaseAPITestCase(APITestCase):
    def authenticate_user(self, username, password):
        """
        Authentifie un utilisateur et retourne le token JWT.
        """
        url = reverse('token_obtain_pair')
        response = self.client.post(url, {'username': username, 'password': password}, format='json')
        self.assertEqual(response.status_code, status.HTTP_200_OK)
        return response.data['access']

    def set_authorization_header(self, token):
        """
        Ajoute le token JWT dans les en-têtes HTTP pour les requêtes suivantes.
        """
        self.client.credentials(HTTP_AUTHORIZATION=f'Bearer {token}')

class UserRegistrationTests(BaseAPITestCase):
    REGISTER_URL = reverse('register')

    def setUp(self):
        self.valid_user_data = {
            'username': 'testuser',
            'email': 'testuser@example.com',
            'password': 'password123',
            'display_name': 'TestUser',
        }

    def test_user_registration_with_valid_data(self):
        response = self.client.post(self.REGISTER_URL, self.valid_user_data, format='json')
        self.assertEqual(response.status_code, status.HTTP_201_CREATED)

class UserProfileUpdateTests(BaseAPITestCase):
    def setUp(self):

        self.user_data = {'username': 'updateuser', 'email': 'updateuser@example.com', 'password': 'password123'}
        self.client.post(reverse('register'), self.user_data, format='json')
        token = self.authenticate_user(self.user_data['username'], self.user_data['password'])
        self.set_authorization_header(token)

    def test_update_profile_with_valid_data(self):
        url = reverse('profile')
        data = {'display_name': 'NewDisplayName'}
        response = self.client.patch(url, data, format='json')
        self.assertEqual(response.status_code, status.HTTP_200_OK)

class FriendTests(BaseAPITestCase):
    def setUp(self):

        self.user1_data = {'username': 'user1', 'email': 'user1@example.com', 'password': 'password123'}
        self.user2_data = {'username': 'user2', 'email': 'user2@example.com', 'password': 'password123'}
        self.client.post(reverse('register'), self.user1_data, format='json')
        self.client.post(reverse('register'), self.user2_data, format='json')

        token = self.authenticate_user(self.user1_data['username'], self.user1_data['password'])
        self.set_authorization_header(token)

    def test_add_friend_valid(self):
        url = reverse('add_friend', kwargs={'user_id': 2})
        response = self.client.post(url)
        self.assertEqual(response.status_code, status.HTTP_201_CREATED)

class FriendsListTests(BaseAPITestCase):
    def setUp(self):

        self.user1_data = {'username': 'user1', 'email': 'user1@example.com', 'password': 'password123'}
        self.user2_data = {'username': 'user2', 'email': 'user2@example.com', 'password': 'password123'}
        self.client.post(reverse('register'), self.user1_data, format='json')
        self.client.post(reverse('register'), self.user2_data, format='json')

        token = self.authenticate_user(self.user1_data['username'], self.user1_data['password'])
        self.set_authorization_header(token)

    def test_get_friends_list(self):
        url = reverse('friends_list')
        response = self.client.get(url)
        self.assertEqual(response.status_code, status.HTTP_200_OK)

class JWTTests(APITestCase):
    def setUp(self):

        self.user = create_user('jwtuser', 'jwtuser@example.com', password='password123')
        self.token_url = reverse('token_obtain_pair')
        self.refresh_url = reverse('token_refresh')

    def test_obtain_tokens(self):
        """
        Vérifie que les tokens (access et refresh) sont générés avec des identifiants valides.
        """
        response = self.client.post(self.token_url, {'username': 'jwtuser', 'password': 'password123'})
        self.assertEqual(response.status_code, status.HTTP_200_OK)
        self.assertIn('access', response.data)
        self.assertIn('refresh', response.data)

    def test_access_protected_endpoint_with_access_token(self):
        """
        Vérifie qu'un access token permet d'accéder à un endpoint protégé.
        """

        response = self.client.post(self.token_url, {'username': 'jwtuser', 'password': 'password123'})
        access_token = response.data['access']

        self.client.credentials(HTTP_AUTHORIZATION=f"Bearer {access_token}")
        protected_url = reverse('profile')
        response = self.client.get(protected_url)
        self.assertEqual(response.status_code, status.HTTP_200_OK)

    def test_refresh_token(self):
        """
        Vérifie que le refresh token fonctionne et retourne un nouveau access token.
        """

        response = self.client.post(self.token_url, {'username': 'jwtuser', 'password': 'password123'})
        refresh_token = response.data['refresh']

        response = self.client.post(self.refresh_url, {'refresh': refresh_token})
        self.assertEqual(response.status_code, status.HTTP_200_OK)
        self.assertIn('access', response.data)

    def test_refresh_token_rotation(self):
        """
        Vérifie la rotation des tokens et l'invalidation de l'ancien refresh token.
        """

        response = self.client.post(self.token_url, {'username': 'jwtuser', 'password': 'password123'})
        initial_refresh_token = response.data['refresh']

        response = self.client.post(self.refresh_url, {'refresh': initial_refresh_token})
        new_refresh_token = response.data['refresh']
        self.assertNotEqual(initial_refresh_token, new_refresh_token)

        response = self.client.post(self.refresh_url, {'refresh': initial_refresh_token})
        self.assertEqual(response.status_code, status.HTTP_401_UNAUTHORIZED)

        response = self.client.post(self.refresh_url, {'refresh': new_refresh_token})
        self.assertEqual(response.status_code, status.HTTP_200_OK)
        self.assertIn('access', response.data)
