from django.urls import reverse
from rest_framework.test import APITestCase
from rest_framework import status
from .models import Profile, Friendship
from django.core.files.uploadedfile import SimpleUploadedFile
from django.utils import timezone
from PIL import Image
from django.contrib.auth import get_user_model
import io

CustomUser = get_user_model()

def create_user(username, email, password='password123', display_name=None):
    user = CustomUser.objects.create_user(username=username, password=password, email=email)
    if display_name:
        user.profile.display_name = display_name
        user.profile.save()
    return user

class UserRegistrationTests(APITestCase):
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
        self.assertEqual(CustomUser.objects.count(), 1)
        self.assertEqual(Profile.objects.count(), 1)
        user = CustomUser.objects.get(username='testuser')
        self.assertEqual(user.profile.display_name, 'TestUser')

    def test_user_registration_with_duplicate_display_name(self):
        existing_user = create_user('existinguser', 'existing@example.com', display_name='UniqueDisplayName')

        data = self.valid_user_data.copy()
        data.update({
            'username': 'newuser',
            'email': 'newuser@example.com',
            'display_name': 'UniqueDisplayName',
        })
        response = self.client.post(self.REGISTER_URL, data, format='json')
        self.assertEqual(response.status_code, status.HTTP_400_BAD_REQUEST)
        self.assertIn('display_name', response.data)

    def test_user_registration_without_display_name(self):
        data = self.valid_user_data.copy()
        del data['display_name']
        response = self.client.post(self.REGISTER_URL, data, format='json')
        self.assertEqual(response.status_code, status.HTTP_400_BAD_REQUEST)
        self.assertIn('display_name', response.data)

    def test_user_registration_with_avatar(self):
        url = reverse('register')
        image = Image.new('RGB', (100, 100))
        image_file = io.BytesIO()
        image.save(image_file, format='JPEG')
        image_file.seek(0)
        avatar = SimpleUploadedFile(
            name=f'test_avatar_{timezone.now().timestamp()}.jpg',
            content=image_file.read(),
            content_type='image/jpeg'
        )
        data = {
            'username': 'avataruser',
            'email': 'avataruser@example.com',
            'password': 'password123',
            'display_name': 'AvatarUser',
            'avatar': avatar,
        }
        response = self.client.post(url, data, format='multipart')
        self.assertEqual(response.status_code, status.HTTP_201_CREATED)
        user = CustomUser.objects.get(username='avataruser')
        self.assertIsNotNone(user.profile.avatar)
        self.assertTrue(user.profile.avatar.name.endswith('.jpg'))

class UserLoginTests(APITestCase):
    def setUp(self):
        self.user = CustomUser.objects.create_user(username='loginuser', password='password123')

    def test_user_login_with_valid_credentials(self):
        url = '/api-auth/login/'
        data = {'username': 'loginuser', 'password': 'password123'}
        response = self.client.post(url, data)
        self.assertEqual(response.status_code, 302)  # DRF redirige vers la page register si les informations sont valides
        self.assertIn('sessionid', response.cookies)  # Vérifiez les cookies si applicable

    def test_user_login_with_invalid_credentials(self):
        url = '/api-auth/login/'
        data = {'username': 'loginuser', 'password': 'wrongpassword'}
        response = self.client.post(url, data)
        self.assertEqual(response.status_code, 200)  # DRF retourne un 200 avec une erreur de formulaire
        self.assertContains(response, 'Please enter a correct username and password.')  # Vérifiez le message d'erreur

class UserProfileUpdateTests(APITestCase):
    def setUp(self):
        self.user = create_user('updateuser', 'updateuser@example.com')
        self.client.login(username='updateuser', password='password123')

    def test_update_profile_with_valid_data(self):
        url = reverse('profile')
        data = {'display_name': 'NewDisplayName'}
        response = self.client.patch(url, data, format='json')
        self.assertEqual(response.status_code, status.HTTP_200_OK)
        self.user.refresh_from_db()
        self.assertEqual(self.user.profile.display_name, 'NewDisplayName')

    def test_update_profile_with_duplicate_display_name(self):
        other_user = create_user('otheruser', 'otheruser@example.com', display_name='ExistingDisplayName')
        url = reverse('profile')
        data = {'display_name': 'ExistingDisplayName'}
        response = self.client.patch(url, data, format='json')
        self.assertEqual(response.status_code, status.HTTP_400_BAD_REQUEST)
        self.assertIn('display_name', response.data)

    def test_update_profile_without_authentication(self):
        self.client.logout()
        url = reverse('profile')
        response = self.client.patch(url, {}, format='json')
        self.assertEqual(response.status_code, status.HTTP_403_FORBIDDEN)

    def test_update_profile_with_empty_display_name(self):
        url = reverse('profile')
        data = {'display_name': ''}
        response = self.client.patch(url, data, format='json')
        self.assertEqual(response.status_code, status.HTTP_400_BAD_REQUEST)
        self.assertIn('display_name', response.data)

    def test_update_profile_with_null_display_name(self):
        url = reverse('profile')
        data = {'display_name': None}
        response = self.client.patch(url, data, format='json')
        self.assertEqual(response.status_code, status.HTTP_400_BAD_REQUEST)
        self.assertIn('display_name', response.data)

class FriendTests(APITestCase):
    def setUp(self):
        self.user1 = create_user('user1', 'user1@example.com', display_name='User One')
        self.user2 = create_user('user2', 'user2@example.com', display_name='User Two')
        self.client.login(username='user1', password='password123')

    def test_add_friend_valid(self):
        url = reverse('add_friend', kwargs={'user_id': self.user2.id})
        response = self.client.post(url)
        self.assertEqual(response.status_code, status.HTTP_201_CREATED)
        self.assertTrue(Friendship.objects.filter(from_user=self.user1, to_user=self.user2).exists())

    def test_add_friend_already_added(self):
        Friendship.objects.create(from_user=self.user1, to_user=self.user2)
        url = reverse('add_friend', kwargs={'user_id': self.user2.id})
        response = self.client.post(url)
        self.assertEqual(response.status_code, status.HTTP_400_BAD_REQUEST)

    def test_add_friend_nonexistent_user(self):
        url = reverse('add_friend', kwargs={'user_id': 999})
        response = self.client.post(url)
        self.assertEqual(response.status_code, status.HTTP_404_NOT_FOUND)

    def test_add_friend_without_authentication(self):
        self.client.logout()
        url = reverse('add_friend', kwargs={'user_id': self.user2.id})
        response = self.client.post(url)
        self.assertEqual(response.status_code, status.HTTP_403_FORBIDDEN)

    def test_cannot_add_self_as_friend(self):
        url = reverse('add_friend', kwargs={'user_id': self.user1.id})
        response = self.client.post(url)
        self.assertEqual(response.status_code, status.HTTP_400_BAD_REQUEST)
        self.assertEqual(response.data['error'], 'Vous ne pouvez pas vous ajouter en tant qu’ami.')


class FriendsListTests(APITestCase):
    def setUp(self):
        self.user1 = create_user('user1', 'user1@example.com')
        self.user2 = create_user('user2', 'user2@example.com')
        self.user3 = create_user('user3', 'user3@example.com')
        Friendship.objects.create(from_user=self.user1, to_user=self.user2)
        self.client.login(username='user1', password='password123')

    def test_get_friends_list(self):
        # user1 a un ami user2
        expected_friend_count = Friendship.objects.filter(from_user=self.user1).count()
        url = reverse('friends_list')
        response = self.client.get(url)
        self.assertEqual(response.status_code, status.HTTP_200_OK)
        self.assertEqual(len(response.data), expected_friend_count)

    def test_get_friends_list_no_friends(self):
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
