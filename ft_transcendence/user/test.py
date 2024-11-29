from django.urls import reverse
from rest_framework.test import APITestCase, APIClient
from rest_framework import status
from django.contrib.auth.models import User
from .models import Profile, Friendship
from django.core.files.uploadedfile import SimpleUploadedFile
from django.utils import timezone
from datetime import timedelta


class UserRegistrationTests(APITestCase):
    def test_user_registration_with_valid_data(self):
        url = reverse('register')
        data = {
            'username': 'testuser',
            'email': 'testuser@example.com',
            'password': 'password123',
            'profile': {
                'display_name': 'TestUser',
            }
        }
        response = self.client.post(url, data, format='json')
        self.assertEqual(response.status_code, status.HTTP_201_CREATED)
        self.assertEqual(User.objects.count(), 1)
        self.assertEqual(Profile.objects.count(), 1)
        user = User.objects.get(username='testuser')
        self.assertEqual(user.profile.display_name, 'TestUser')

    def test_user_registration_with_duplicate_display_name(self):
        # Créer un utilisateur existant
        existing_user = User.objects.create_user(username='existinguser', password='password123')
        existing_profile = existing_user.profile
        existing_profile.display_name = 'UniqueDisplayName'
        existing_profile.save()

        url = reverse('register')
        data = {
            'username': 'newuser',
            'email': 'newuser@example.com',
            'password': 'password123',
            'profile': {
                'display_name': 'UniqueDisplayName',  # Même display_name
            }
        }
        response = self.client.post(url, data, format='json')
        self.assertEqual(response.status_code, status.HTTP_400_BAD_REQUEST)
        self.assertIn('display_name', response.data)

    def test_user_registration_without_display_name(self):
        url = reverse('register')
        data = {
            'username': 'testuser2',
            'email': 'testuser2@example.com',
            'password': 'password123',
            'profile': {
                # Pas de 'display_name'
            }
        }
        response = self.client.post(url, data, format='json')
        self.assertEqual(response.status_code, status.HTTP_400_BAD_REQUEST)
        self.assertIn('display_name', response.data)

    def test_user_registration_with_avatar(self):
        url = reverse('register')
        avatar = SimpleUploadedFile(
            name='test_avatar.jpg',
            content=b'file_content',
            content_type='image/jpeg'
        )
        data = {
            'username': 'avataruser',
            'email': 'avataruser@example.com',
            'password': 'password123',
            'profile': {
                'display_name': 'AvatarUser',
                'avatar': avatar
            }
        }
        response = self.client.post(url, data, format='multipart')
        self.assertEqual(response.status_code, status.HTTP_201_CREATED)
        user = User.objects.get(username='avataruser')
        self.assertTrue(user.profile.avatar.url.endswith('test_avatar.jpg'))



class UserLoginTests(APITestCase):
    def setUp(self):
        self.user = User.objects.create_user(username='loginuser', password='password123')

    def test_user_login_with_valid_credentials(self):
        url = '/api-auth/login/'
        data = {'username': 'loginuser', 'password': 'password123'}
        response = self.client.post(url, data)
        # self.assertEqual(response.status_code, status.HTTP_200_OK)
        # self.assertTrue('_auth_user_id' in self.client.session)
        self.assertEqual(response.status_code, 302)
        self.assertTrue(response.url.startswith('/'))


    def test_user_login_with_invalid_credentials(self):
        url = '/api-auth/login/'
        data = {'username': 'loginuser', 'password': 'wrongpassword'}
        response = self.client.post(url, data)
        self.assertEqual(response.status_code, status.HTTP_200_OK)  # Django returns 200 with form errors
        self.assertFalse('_auth_user_id' in self.client.session)
        self.assertContains(response, 'Please enter a correct username and password. Note that both fields may be case-sensitive.')



class UserProfileUpdateTests(APITestCase):
    def setUp(self):
        self.user = User.objects.create_user(username='updateuser', password='password123')
        self.client.login(username='updateuser', password='password123')

    def test_update_profile_with_valid_data(self):
        url = reverse('profile')
        data = {
            'email': 'newemail@example.com',
            'profile': {
                'display_name': 'NewDisplayName',
            }
        }
        response = self.client.put(url, data, format='json')
        self.assertEqual(response.status_code, status.HTTP_200_OK)
        self.user.refresh_from_db()
        self.assertEqual(self.user.email, 'newemail@example.com')
        self.assertEqual(self.user.profile.display_name, 'NewDisplayName')

    def test_update_profile_with_duplicate_display_name(self):
        # Créer un autre utilisateur avec un display_name spécifique
        other_user = User.objects.create_user(username='otheruser', password='password123')
        other_user.profile.display_name = 'ExistingDisplayName'
        other_user.profile.save()

        url = reverse('profile')
        data = {
            'profile': {
                'display_name': 'ExistingDisplayName',  # Display name déjà utilisé
            }
        }
        response = self.client.put(url, data, format='json')
        self.assertEqual(response.status_code, status.HTTP_400_BAD_REQUEST)
        self.assertIn('display_name', response.data['profile'])

    def test_update_profile_without_authentication(self):
        self.client.logout()
        url = reverse('profile')
        data = {
            'email': 'unauthenticated@example.com',
        }
        response = self.client.put(url, data, format='json')
        self.assertEqual(response.status_code, status.HTTP_403_FORBIDDEN)



class FriendTests(APITestCase):
    def setUp(self):
        self.user1 = User.objects.create_user(username='user1', password='password123')
        self.user1.profile.display_name = 'User One'
        self.user1.profile.save()

        self.user2 = User.objects.create_user(username='user2', password='password123')
        self.user2.profile.display_name = 'User Two'
        self.user2.profile.save()

        self.client.login(username='user1', password='password123')

    def test_add_friend_valid(self):
        url = reverse('add_friend', kwargs={'user_id': self.user2.id})
        response = self.client.post(url)
        self.assertEqual(response.status_code, status.HTTP_201_CREATED)
        self.assertTrue(Friendship.objects.filter(from_user=self.user1, to_user=self.user2).exists())

    def test_add_friend_already_added(self):
        # Ajouter l'ami une première fois
        Friendship.objects.create(from_user=self.user1, to_user=self.user2)

        url = reverse('add_friend', kwargs={'user_id': self.user2.id})
        response = self.client.post(url)
        self.assertEqual(response.status_code, status.HTTP_400_BAD_REQUEST)
        self.assertIn('Déjà ami', response.data['error'])

    def test_add_friend_nonexistent_user(self):
        url = reverse('add_friend', kwargs={'user_id': 999})  # ID qui n'existe pas
        response = self.client.post(url)
        self.assertEqual(response.status_code, status.HTTP_404_NOT_FOUND)
        self.assertIn('Utilisateur non trouvé', response.data['error'])

    def test_add_friend_without_authentication(self):
        self.client.logout()
        url = reverse('add_friend', kwargs={'user_id': self.user2.id})
        response = self.client.post(url)
        self.assertEqual(response.status_code, status.HTTP_403_FORBIDDEN)


class FriendsListTests(APITestCase):
    def setUp(self):
        self.user1 = User.objects.create_user(username='user1', password='password123')
        self.user2 = User.objects.create_user(username='user2', password='password123')
        self.user3 = User.objects.create_user(username='user3', password='password123')

        # user1 est ami avec user2
        Friendship.objects.create(from_user=self.user1, to_user=self.user2)

        self.client.login(username='user1', password='password123')

    def test_get_friends_list(self):
        url = reverse('friends_list')
        response = self.client.get(url)
        self.assertEqual(response.status_code, status.HTTP_200_OK)
        self.assertEqual(len(response.data), 1)
        self.assertEqual(response.data[0]['username'], 'user2')

    def test_get_friends_list_no_friends(self):
        # Supprimer toutes les amitiés
        Friendship.objects.all().delete()

        url = reverse('friends_list')
        response = self.client.get(url)
        self.assertEqual(response.status_code, status.HTTP_200_OK)
        self.assertEqual(len(response.data), 0)

    def test_get_friends_list_without_authentication(self):
        self.client.logout()
        url = reverse('friends_list')
        response = self.client.get(url)
        self.assertEqual(response.status_code, status.HTTP_403_FORBIDDEN)


class OnlineStatusTests(APITestCase):
    def setUp(self):
        self.user = User.objects.create_user(username='onlineuser', password='password123')
        self.client.login(username='onlineuser', password='password123')

    def test_last_activity_updated_on_request(self):
        old_activity = self.user.profile.last_activity
        url = reverse('profile')
        response = self.client.get(url)
        self.assertEqual(response.status_code, status.HTTP_200_OK)
        self.user.profile.refresh_from_db()
        new_activity = self.user.profile.last_activity
        self.assertNotEqual(old_activity, new_activity)

    def test_is_online_method(self):
        # Simuler une activité il y a 2 minutes
        self.user.profile.last_activity = timezone.now() - timedelta(minutes=2)
        self.user.profile.save()
        self.assertTrue(self.user.profile.is_online())

        # Simuler une activité il y a 10 minutes
        self.user.profile.last_activity = timezone.now() - timedelta(minutes=10)
        self.user.profile.save()
        self.assertFalse(self.user.profile.is_online())

class UserProfileTests(APITestCase):
    def setUp(self):
        self.user = User.objects.create_user(username='testuser', password='password123')
        self.client.login(username='testuser', password='password123')

    def test_update_profile_with_valid_data(self):
        url = '/api/users/profile/'
        data = {
            'display_name': 'NewDisplayName',
        }
        response = self.client.patch(url, data, format='json')
        self.assertEqual(response.status_code, status.HTTP_200_OK)
        self.assertEqual(response.data['display_name'], 'NewDisplayName')


class PermissionsTests(APITestCase):
    def setUp(self):
        self.user = User.objects.create_user(username='user', password='password123')
        self.other_user = User.objects.create_user(username='otheruser', password='password123')

    def test_protected_views_require_authentication(self):
        url = reverse('profile')
        response = self.client.get(url)
        self.assertEqual(response.status_code, status.HTTP_403_FORBIDDEN)

    def test_user_cannot_update_another_users_profile(self):
        self.client.login(username='user', password='password123')
        # Essayer de mettre à jour le profil de 'otheruser'
        url = reverse('profile')
        data = {
            'username': 'otheruser',
            'email': 'hacked@example.com',
        }
        response = self.client.put(url, data, format='json')
        self.assertNotEqual(response.status_code, status.HTTP_200_OK)
        self.other_user.refresh_from_db()
        self.assertNotEqual(self.other_user.email, 'hacked@example.com')
