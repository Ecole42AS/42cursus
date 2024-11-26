from django.urls import reverse
from rest_framework.test import APITestCase, APIClient
from rest_framework import status
from django.contrib.auth.models import User
from .models import Friendship

class UserTests(APITestCase):

    def test_register_user(self):
        url = reverse('register')
        data = {'username': 'testuser', 'email': 'test@example.com', 'password': 'password123', 'profile': {'display_name': 'Test User'}}
        response = self.client.post(url, data, format='json')
        self.assertEqual(response.status_code, status.HTTP_201_CREATED)
        self.assertEqual(User.objects.count(), 1)
        self.assertEqual(User.objects.get().username, 'testuser')

    def test_login_user(self):
        user = User.objects.create_user(username='testuser', password='password123')
        url = reverse('rest_framework:login')
        data = {'username': 'testuser', 'password': 'password123'}
        client = APIClient()
        response = client.post(url, data, format='json')
        self.assertEqual(response.status_code, status.HTTP_200_OK)

class AddFriendViewTest(APITestCase):
    def setUp(self):
        self.user1 = User.objects.create_user(username='alex', password='deplanta1')
        self.user2 = User.objects.create_user(username='friend2', password='friend2')
        self.client.login(username='alex', password='deplanta1')

    def test_add_friend(self):
        response = self.client.post(f'/api/user/add_friend/{self.user2.id}/')
        self.assertEqual(response.status_code, 201)
        self.assertTrue(Friendship.objects.filter(from_user=self.user1, to_user=self.user2).exists())

    def test_add_nonexistent_friend(self):
        response = self.client.post('/api/user/add_friend/999/')  # ID d'un utilisateur inexistant
        self.assertEqual(response.status_code, 404)
        self.assertEqual(response.data['error'], 'Utilisateur non trouvé')

    def test_add_existing_friend(self):
        Friendship.objects.create(from_user=self.user1, to_user=self.user2)
        response = self.client.post(f'/api/user/add_friend/{self.user2.id}/')
        self.assertEqual(response.status_code, 400)
        self.assertEqual(response.data['error'], 'Déjà ami')