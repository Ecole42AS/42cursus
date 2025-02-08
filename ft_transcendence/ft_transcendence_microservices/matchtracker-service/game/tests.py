
from django.test import TestCase
from rest_framework.test import APITestCase
from rest_framework import status
from django.urls import reverse
from unittest.mock import patch
from .models import GameSession, Tournament
from rest_framework_simplejwt.tokens import AccessToken

def get_mock_jwt_token(user_id):
    """
    Génère un token JWT valide pour un utilisateur simulé.
    """
    token = AccessToken()
    token['user_id'] = user_id
    return str(token)

class GameSessionModelTests(TestCase):
    def setUp(self):
        self.player1_id = 1
        self.player2_id = 2

    def test_game_session_creation(self):
        game = GameSession.objects.create(player1_id=self.player1_id, player2_id=self.player2_id)
        self.assertTrue(game.is_active)
        self.assertEqual(game.player1_id, self.player1_id)
        self.assertEqual(game.player2_id, self.player2_id)

    def test_game_session_str(self):
        game = GameSession.objects.create(player1_id=self.player1_id, player2_id=self.player2_id)

        self.assertEqual(str(game), f"GameSession {game.id} between {game.player1_id} and {game.player2_id}")

class GameSessionAPITests(APITestCase):
    def setUp(self):
        self.player1_id = 1
        self.player2_id = 2
        self.other_user_id = 3
        token = get_mock_jwt_token(self.player1_id)
        self.client.credentials(HTTP_AUTHORIZATION=f"Bearer {token}")

    @patch('game.utils.get_user')
    def test_create_game_session(self, mock_get_user):
        mock_get_user.return_value = {'id': self.player2_id, 'username': 'player2'}
        url = reverse('create_game', args=[self.player2_id])
        response = self.client.post(url)
        self.assertEqual(response.status_code, status.HTTP_201_CREATED)
        self.assertEqual(GameSession.objects.count(), 1)

    def test_list_game_sessions(self):
        GameSession.objects.create(player1_id=self.player1_id, player2_id=self.player2_id)
        GameSession.objects.create(player1_id=self.player2_id, player2_id=self.player1_id)
        url = reverse('game-list')
        response = self.client.get(url)
        self.assertEqual(response.status_code, status.HTTP_200_OK)
        self.assertEqual(len(response.data), 2)

class TournamentModelTests(TestCase):
    def setUp(self):
        self.player1_id = 1
        self.player2_id = 2
        self.tournament = Tournament.objects.create(name='Test Tournament', creator_id=self.player1_id)

    def test_add_players_to_tournament(self):
        self.tournament.players_ids = [self.player1_id, self.player2_id]
        self.tournament.save()
        self.assertEqual(len(self.tournament.players_ids), 2)
        self.assertIn(self.player1_id, self.tournament.players_ids)

    def test_tournament_str(self):
        self.assertEqual(str(self.tournament), 'Test Tournament')

class NonAuthenticatedUserTests(APITestCase):
    def setUp(self):
        self.player1_id = 1
        self.player2_id = 2
        self.game = GameSession.objects.create(player1_id=self.player1_id, player2_id=self.player2_id)

    def test_non_authenticated_user_cannot_access(self):
        self.client.credentials()
        url = reverse('game-detail', args=[self.game.id])
        response = self.client.get(url)
        self.assertEqual(response.status_code, status.HTTP_401_UNAUTHORIZED)

class GameSessionPermissionsTestCase(APITestCase):
    def setUp(self):
        self.player1_id = 1
        self.player2_id = 2
        self.other_user_id = 3
        self.game = GameSession.objects.create(player1_id=self.player1_id, player2_id=self.player2_id)

    @patch('game.utils.get_user')
    def test_user_cannot_modify_others_game(self, mock_get_user):
        mock_get_user.return_value = {'id': self.other_user_id, 'username': 'other_user'}
        token = get_mock_jwt_token(self.other_user_id)
        self.client.credentials(HTTP_AUTHORIZATION=f"Bearer {token}")
        url = reverse('update_game_score', args=[self.game.id])
        data = {'score': 10}
        response = self.client.post(url, data, format='json')
        self.assertEqual(response.status_code, status.HTTP_403_FORBIDDEN)
