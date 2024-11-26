from django.urls import reverse
from rest_framework.test import APITestCase, APIClient
from rest_framework import status
from django.contrib.auth.models import User
from django.test import TestCase
from .models import Friendship, Profile
from .serializers import UserSerializer
from django.utils.timezone import now, timedelta


# 1. Tests pour les utilisateurs (inscription et connexion)
class UserTests(APITestCase):
    """
    Tests pour la création et la connexion des utilisateurs.
    """

    def test_register_user(self):
        """
        Vérifie que l'enregistrement d'un utilisateur fonctionne correctement.
        """
        url = reverse('register')
        data = {
            'username': 'testuser',
            'email': 'test@example.com',
            'password': 'password123',
            'profile': {'display_name': 'Test User'}
        }
        response = self.client.post(url, data, format='json')
        self.assertEqual(response.status_code, status.HTTP_201_CREATED)
        self.assertEqual(User.objects.count(), 1)
        self.assertEqual(User.objects.get().username, 'testuser')

    def test_login_user(self):
        """
        Vérifie que la connexion fonctionne avec les bonnes informations.
        """
        user = User.objects.create_user(username='testuser', password='password123')
        url = reverse('rest_framework:login')
        data = {'username': 'testuser', 'password': 'password123'}
        client = APIClient()
        response = client.post(url, data, format='json')
        self.assertEqual(response.status_code, status.HTTP_200_OK)


# 2. Tests pour l'ajout d'amis
class AddFriendViewTest(APITestCase):
    """
    Tests pour l'ajout d'amis.
    """

    def setUp(self):
        """
        Crée deux utilisateurs pour les tests.
        """
        self.user1 = User.objects.create_user(username='alex', password='deplanta1')
        self.user2 = User.objects.create_user(username='friend2', password='friend2')
        self.client.login(username='alex', password='deplanta1')

    def test_add_friend(self):
        """
        Vérifie qu'un utilisateur peut ajouter un autre utilisateur comme ami.
        """
        response = self.client.post(f'/api/user/add_friend/{self.user2.id}/')
        self.assertEqual(response.status_code, 201)
        self.assertTrue(Friendship.objects.filter(from_user=self.user1, to_user=self.user2).exists())

    def test_add_nonexistent_friend(self):
        """
        Vérifie le comportement lorsqu'un utilisateur inexistant est ajouté comme ami.
        """
        response = self.client.post('/api/user/add_friend/999/')  # ID inexistant
        self.assertEqual(response.status_code, 404)
        self.assertEqual(response.data['error'], 'Utilisateur non trouvé')

    def test_add_existing_friend(self):
        """
        Vérifie le comportement lorsqu'un utilisateur déjà ami est ajouté.
        """
        Friendship.objects.create(from_user=self.user1, to_user=self.user2)
        response = self.client.post(f'/api/user/add_friend/{self.user2.id}/')
        self.assertEqual(response.status_code, 400)
        self.assertEqual(response.data['error'], 'Déjà ami')


# 3. Tests pour le sérialiseur UserSerializer
class UserSerializerTest(TestCase):
    """
    Tests pour le sérialiseur UserSerializer.
    """

    def setUp(self):
        """
        Prépare les données pour les tests.
        """
        self.user_data = {
            'username': 'testuser',
            'password': 'testpassword',
            'email': 'testuser@example.com',
            'profile': {
                'display_name': 'Test User',
                'avatar': None
            }
        }
        self.user = User.objects.create_user(username='existinguser', password='password', email='existing@example.com')
        Profile.objects.create(user=self.user, display_name='Existing User')

    def test_create_user_success(self):
        """
        Vérifie que le sérialiseur crée un utilisateur correctement.
        """
        serializer = UserSerializer(data=self.user_data)
        self.assertTrue(serializer.is_valid())
        user = serializer.save()
        self.assertEqual(user.username, self.user_data['username'])
        self.assertEqual(user.profile.display_name, self.user_data['profile']['display_name'])

    def test_create_user_duplicate_display_name(self):
        """
        Vérifie que le sérialiseur rejette un nom d'affichage dupliqué.
        """
        self.user_data['profile']['display_name'] = 'Existing User'
        serializer = UserSerializer(data=self.user_data)
        self.assertFalse(serializer.is_valid())
        self.assertIn('display_name', serializer.errors['profile'])

    def test_create_user_missing_display_name(self):
        """
        Vérifie que le sérialiseur rejette une création sans nom d'affichage.
        """
        del self.user_data['profile']['display_name']
        serializer = UserSerializer(data=self.user_data)
        self.assertFalse(serializer.is_valid())
        self.assertIn('display_name', serializer.errors['profile'])

    def test_update_user_success(self):
        """
        Vérifie que le sérialiseur met à jour les données utilisateur.
        """
        user = User.objects.create_user(username='updateuser', password='password', email='update@example.com')
        Profile.objects.create(user=user, display_name='Update User')
        update_data = {
            'username': 'updateduser',
            'email': 'updated@example.com',
            'profile': {
                'display_name': 'Updated User',
                'avatar': None
            }
        }
        serializer = UserSerializer(user, data=update_data)
        self.assertTrue(serializer.is_valid())
        updated_user = serializer.save()
        self.assertEqual(updated_user.username, update_data['username'])
        self.assertEqual(updated_user.profile.display_name, update_data['profile']['display_name'])

    def test_update_profile_success(self):
        """
        Vérifie que le sérialiseur met à jour uniquement le profil.
        """
        user = User.objects.create_user(username='updateuser', password='password', email='update@example.com')
        Profile.objects.create(user=user, display_name='Update User')
        update_data = {
            'profile': {
                'display_name': 'Updated User',
                'avatar': None
            }
        }
        serializer = UserSerializer(user, data=update_data, partial=True)
        self.assertTrue(serializer.is_valid())
        updated_user = serializer.save()
        self.assertEqual(updated_user.profile.display_name, update_data['profile']['display_name'])


# 4. Tests pour les modèles Profile
class ProfileModelTest(TestCase):
    """
    Tests pour le modèle Profile.
    """

    def setUp(self):
        """
        Crée un utilisateur et un profil pour les tests.
        """
        self.user = User.objects.create_user(username='testuser', password='password123')
        self.profile = self.user.profile

    def test_is_online(self):
        """
        Vérifie que la méthode is_online retourne correctement True ou False.
        """
        self.profile.last_activity = now() - timedelta(minutes=3)
        self.profile.save()
        self.assertTrue(self.profile.is_online())

        self.profile.last_activity = now() - timedelta(minutes=10)
        self.profile.save()
        self.assertFalse(self.profile.is_online())
