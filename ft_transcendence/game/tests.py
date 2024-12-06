from django.test import TestCase
from rest_framework.test import APITestCase, APIClient
from rest_framework import status
from django.urls import reverse
from django.utils.timezone import now
from .models import GameSession, Tournament, TournamentMatch
from .utils import generate_tournament_matches
from django.contrib.auth import get_user_model

CustomUser = get_user_model()

# Utility function to create users
def create_user(username, email, password='password123'):
    return CustomUser.objects.create_user(username=username, email=email, password=password)

# -------------------------------
# Tests for GameSession Model
# -------------------------------
class GameSessionModelTests(TestCase):
    def setUp(self):
        self.player1 = create_user('player1', 'player1@example.com')
        self.player2 = create_user('player2', 'player2@example.com')

    def test_game_session_creation(self):
        game = GameSession.objects.create(player1=self.player1, player2=self.player2)
        self.assertEqual(game.player1.username, 'player1')
        self.assertEqual(game.player2.username, 'player2')
        self.assertTrue(game.is_active)

    def test_game_session_str(self):
        game = GameSession.objects.create(player1=self.player1, player2=self.player2)
        self.assertEqual(str(game), f"GameSession {game.id} between player1 and player2")

# -------------------------------
# Tests for GameSession API
# -------------------------------
class GameSessionAPITests(APITestCase):
    def setUp(self):
        self.player1 = create_user('player1', 'player1@example.com')
        self.player2 = create_user('player2', 'player2@example.com')
        self.client.login(username='player1', password='password123')
        self.other_user = create_user('otheruser', 'otheruser@example.com')
        self.tournament = Tournament.objects.create(name='Test Tournament')

    def test_create_game_session(self):
        url = reverse('game-list')
        data = {'player1': self.player1.id, 'player2': self.player2.id}
        response = self.client.post(url, data, format='json')
        self.assertEqual(response.status_code, status.HTTP_201_CREATED)
        self.assertEqual(GameSession.objects.count(), 1)

    def test_retrieve_game_session(self):
        game = GameSession.objects.create(player1=self.player1, player2=self.player2)
        url = reverse('game-detail', args=[game.id])
        response = self.client.get(url)
        self.assertEqual(response.status_code, status.HTTP_200_OK)
        self.assertEqual(response.data['player1'], self.player1.id)

    def test_list_game_sessions(self):
        GameSession.objects.create(player1=self.player1, player2=self.player2)
        GameSession.objects.create(player1=self.player2, player2=self.player1)
        url = reverse('game-list')
        response = self.client.get(url)
        self.assertEqual(response.status_code, status.HTTP_200_OK)
        self.assertEqual(len(response.data), 2)

    def test_update_game_session(self):
        game = GameSession.objects.create(player1=self.player1, player2=self.player2)
        url = reverse('game-detail', args=[game.id])
        data = {'is_active': False}
        response = self.client.patch(url, data, format='json')
        self.assertEqual(response.status_code, status.HTTP_200_OK)
        game.refresh_from_db()
        self.assertFalse(game.is_active)

    def test_delete_game_session(self):
        game = GameSession.objects.create(player1=self.player1, player2=self.player2)
        url = reverse('game-detail', args=[game.id])
        response = self.client.delete(url)
        self.assertEqual(response.status_code, status.HTTP_204_NO_CONTENT)
        self.assertEqual(GameSession.objects.count(), 0)

    def test_authenticated_user_sees_only_their_games(self):
        GameSession.objects.create(player1=self.player2, player2=self.other_user)
        response = self.client.get(reverse('game-list'))
        for game in response.data:
            self.assertIn(self.player1.id, [game['player1'], game['player2']])

    def test_generate_matches_with_single_player(self):
        self.tournament.players.add(self.player1)
        generate_tournament_matches(self.tournament)
        matches = TournamentMatch.objects.filter(tournament=self.tournament)
        self.assertEqual(matches.count(), 0)

# -------------------------------
# Tests for Tournament Model
# -------------------------------
class TournamentModelTests(TestCase):
    def setUp(self):
        self.player1 = create_user('player1', 'player1@example.com')
        self.player2 = create_user('player2', 'player2@example.com')
        self.tournament = Tournament.objects.create(name='Test Tournament')

    def test_add_players_to_tournament(self):
        self.tournament.players.add(self.player1, self.player2)
        self.assertEqual(self.tournament.players.count(), 2)
        self.assertIn(self.player1, self.tournament.players.all())

    def test_remove_player_from_tournament(self):
        self.tournament.players.add(self.player1, self.player2)
        self.tournament.players.remove(self.player1)
        self.assertEqual(self.tournament.players.count(), 1)
        self.assertNotIn(self.player1, self.tournament.players.all())

    def test_tournament_str(self):
        self.assertEqual(str(self.tournament), 'Test Tournament')

# -------------------------------
# Tests for Tournament API
# -------------------------------
class TournamentAPITests(APITestCase):
    def setUp(self):
        self.player1 = create_user('player1', 'player1@example.com')
        self.player2 = create_user('player2', 'player2@example.com')
        self.client.login(username='player1', password='password123')

    def test_create_tournament(self):
        url = reverse('tournament-list')
        data = {
            'name': 'Test Tournament',
            'players': [self.player1.id, self.player2.id],  # Ajoutez les joueurs ici
        }
        response = self.client.post(url, data, format='json')
        self.assertEqual(response.status_code, status.HTTP_201_CREATED)
        self.assertEqual(Tournament.objects.count(), 1)


    def test_list_tournaments(self):
        Tournament.objects.create(name='Tournament 1')
        Tournament.objects.create(name='Tournament 2')
        url = reverse('tournament-list')
        response = self.client.get(url)
        self.assertEqual(response.status_code, status.HTTP_200_OK)
        self.assertEqual(len(response.data), 2)

    def test_add_players_to_tournament(self):
        tournament = Tournament.objects.create(name='Test Tournament')
        url = reverse('tournament-detail', args=[tournament.id])
        data = {'players': [self.player1.id, self.player2.id]}
        response = self.client.patch(url, data, format='json')
        self.assertEqual(response.status_code, status.HTTP_200_OK)
        tournament.refresh_from_db()
        self.assertEqual(tournament.players.count(), 2)

    def test_delete_tournament(self):
        tournament = Tournament.objects.create(name='Tournament to Delete')
        url = reverse('tournament-detail', args=[tournament.id])
        response = self.client.delete(url)
        self.assertEqual(response.status_code, status.HTTP_204_NO_CONTENT)
        self.assertEqual(Tournament.objects.count(), 0)

# -------------------------------
# Tests for Tournament Match Model
# -------------------------------
class TournamentMatchModelTests(TestCase):
    def setUp(self):
        self.player1 = create_user('player1', 'player1@example.com')
        self.player2 = create_user('player2', 'player2@example.com')
        self.tournament = Tournament.objects.create(name='Test Tournament')

    def test_tournament_match_creation(self):
        match = TournamentMatch.objects.create(
            tournament=self.tournament,
            player1=self.player1,
            player2=self.player2,
            scheduled_at=now(),
            is_completed=False
        )
        self.assertEqual(match.tournament.name, 'Test Tournament')
        self.assertEqual(match.player1.username, 'player1')
        self.assertEqual(match.player2.username, 'player2')
        self.assertFalse(match.is_completed)

    def test_tournament_match_str(self):
        match = TournamentMatch.objects.create(
            tournament=self.tournament,
            player1=self.player1,
            player2=self.player2,
            scheduled_at=now(),
        )
        self.assertEqual(str(match), f"Match in Test Tournament between player1 and player2")

    def test_generate_matches(self):
        self.tournament.players.add(self.player1, self.player2)
        generate_tournament_matches(self.tournament)
        matches = TournamentMatch.objects.filter(tournament=self.tournament)
        self.assertEqual(matches.count(), 1)

class NonAuthenticatedUserTests(APITestCase):
    def setUp(self):
        self.player1 = create_user('player1', 'player1@example.com')
        self.player2 = create_user('player2', 'player2@example.com')
        self.game = GameSession.objects.create(player1=self.player1, player2=self.player2)
        self.tournament = Tournament.objects.create(name='Test Tournament')

    def test_non_authenticated_user_cannot_access(self):
        url = reverse('game-detail', args=[self.game.id])
        response = self.client.get(url)
        self.assertEqual(response.status_code, status.HTTP_403_FORBIDDEN)

class GameSessionPermissionsTestCase(APITestCase):
    def setUp(self):
        self.player1 = create_user('player1', 'player1@example.com')
        self.player2 = create_user('player2', 'player2@example.com')
        self.client.login(username='player1', password='password123')  # S'assurer que le login est bien fait
        self.other_user = create_user('otheruser', 'otheruser@example.com')
        self.game = GameSession.objects.create(player1=self.player1, player2=self.player2)
        self.tournament = Tournament.objects.create(name='Test Tournament')

    def test_user_cannot_modify_others_game(self):
        self.client.login(username='otheruser', password='password123')
        url = reverse('game-detail', args=[self.game.id])
        data = {'is_active': False}
        response = self.client.patch(url, data, format='json')
        self.assertEqual(response.status_code, status.HTTP_404_NOT_FOUND)

    def test_user_can_modify_own_game(self):
        self.client.login(username='player1', password='password123')
        url = reverse('game-detail', args=[self.game.id])
        data = {'is_active': False}
        response = self.client.patch(url, data, format='json')
        self.assertEqual(response.status_code, status.HTTP_200_OK)
        self.game.refresh_from_db()
        self.assertFalse(self.game.is_active)

    def test_create_game_session_with_missing_player(self):
        url = reverse('game-list')
        data = {'player1': self.player1.id}  # player2 missing
        response = self.client.post(url, data, format='json')
        self.assertEqual(response.status_code, status.HTTP_400_BAD_REQUEST)

    def test_delete_player_removes_from_tournament(self):
        self.tournament.players.add(self.player1, self.player2)
        self.player1.delete()
        self.assertNotIn(self.player1, self.tournament.players.all())

    def test_create_tournament_with_duplicate_name(self):
        Tournament.objects.create(name='Duplicate Tournament')
        url = reverse('tournament-list')
        data = {'name': 'Duplicate Tournament', 'players': [self.player1.id, self.player2.id]}
        response = self.client.post(url, data, format='json')
        self.assertEqual(response.status_code, status.HTTP_400_BAD_REQUEST)
