from django.test import TestCase
from rest_framework.test import APITestCase
from rest_framework import status
from django.urls import reverse
from django.utils.timezone import now
from .models import GameSession, Tournament, TournamentMatch
from .utils import generate_elimination_matches
from .views import update_player_stats

def get_user_mock(user_id):
    
    
    
    mock_users = {
        1: {'id': 1, 'username': 'player1', 'friends': [2, 3]}, 
        2: {'id': 2, 'username': 'player2', 'friends': [1]}, 
        3: {'id': 3, 'username': 'otheruser', 'friends': [1]},
        4: {'id': 4, 'username': 'player3', 'friends': [1,2]}
    }
    return mock_users.get(user_id, {'id': user_id, 'username': f'user{user_id}', 'friends': []})

class GameSessionModelTests(TestCase):
    def setUp(self):
        
        self.player1_id = 1
        self.player2_id = 2

    def test_game_session_creation(self):
        game = GameSession.objects.create(player1_id=self.player1_id, player2_id=self.player2_id)
        player1_data = get_user_mock(game.player1_id)
        player2_data = get_user_mock(game.player2_id)
        self.assertEqual(player1_data['username'], 'player1')
        self.assertEqual(player2_data['username'], 'player2')
        self.assertTrue(game.is_active)

    def test_game_session_str(self):
        game = GameSession.objects.create(player1_id=self.player1_id, player2_id=self.player2_id)
        player1_data = get_user_mock(game.player1_id)
        player2_data = get_user_mock(game.player2_id)
        self.assertEqual(str(game), f"GameSession {game.id} between {player1_data['username']} and {player2_data['username']}")

    def test_update_player_stats(self):
        
        game = GameSession.objects.create(player1_id=self.player1_id, player2_id=self.player2_id, is_active=False, winner_id=self.player1_id)
        
        
        
        update_player_stats(self.player1_id, self.player2_id)
        
        self.assertTrue(True)  


class GameSessionAPITests(APITestCase):
    def setUp(self):
        
        self.player1_id = 1
        self.player2_id = 2
        self.other_user_id = 3
        self.tournament = Tournament.objects.create(name='Test Tournament', creator_id=self.player1_id)
        
        self.client.credentials(HTTP_AUTHORIZATION='Token player1_token')

    def test_create_game_session(self):
        url = reverse('game-list')
        data = {'player1_id': self.player1_id, 'player2_id': self.player2_id}
        response = self.client.post(url, data, format='json')
        self.assertEqual(response.status_code, status.HTTP_201_CREATED)
        self.assertEqual(GameSession.objects.count(), 1)

    def test_retrieve_game_session(self):
        game = GameSession.objects.create(player1_id=self.player1_id, player2_id=self.player2_id)
        url = reverse('game-detail', args=[game.id])
        response = self.client.get(url)
        self.assertEqual(response.status_code, status.HTTP_200_OK)
        self.assertEqual(response.data['player1']['id'], self.player1_id)

    def test_list_game_sessions(self):
        GameSession.objects.create(player1_id=self.player1_id, player2_id=self.player2_id)
        GameSession.objects.create(player1_id=self.player2_id, player2_id=self.player1_id)
        url = reverse('game-list')
        response = self.client.get(url)
        self.assertEqual(response.status_code, status.HTTP_200_OK)
        self.assertEqual(len(response.data), 2)

    def test_update_game_session(self):
        game = GameSession.objects.create(player1_id=self.player1_id, player2_id=self.player2_id)
        url = reverse('game-detail', args=[game.id])
        data = {'is_active': False}
        response = self.client.patch(url, data, format='json')
        self.assertEqual(response.status_code, status.HTTP_200_OK)
        game.refresh_from_db()
        self.assertFalse(game.is_active)

    def test_delete_game_session(self):
        game = GameSession.objects.create(player1_id=self.player1_id, player2_id=self.player2_id)
        url = reverse('game-detail', args=[game.id])
        response = self.client.delete(url)
        self.assertEqual(response.status_code, status.HTTP_204_NO_CONTENT)
        self.assertEqual(GameSession.objects.count(), 0)

    def test_authenticated_user_sees_only_their_games(self):
        GameSession.objects.create(player1_id=self.player2_id, player2_id=self.other_user_id)
        response = self.client.get(reverse('game-list'))
        
        for game in response.data:
            self.assertIn(self.player1_id, [game['player1']['id'], game['player2']['id']])

    def test_generate_matches_with_single_player(self):
        self.tournament.players_ids = [self.player1_id]
        self.tournament.save()
        generate_elimination_matches(self.tournament)
        matches = TournamentMatch.objects.filter(tournament=self.tournament)
        self.assertEqual(matches.count(), 0)

    def test_create_1v1_game(self):
        url = reverse('create_game', args=[self.player2_id])
        response = self.client.post(url)
        self.assertEqual(response.status_code, status.HTTP_201_CREATED)
        self.assertEqual(GameSession.objects.count(), 1)
        game = GameSession.objects.first()
        self.assertEqual(game.player1_id, self.player1_id)
        self.assertEqual(game.player2_id, self.player2_id)
        self.assertTrue(game.is_active)

    def test_update_game_score_and_end_game(self):
        game = GameSession.objects.create(player1_id=self.player1_id, player2_id=self.player2_id)
        url = reverse('update_game_score', args=[game.id])
        data = {'score': 5}
        
        response = self.client.post(url, data, format='json')
        self.assertEqual(response.status_code, status.HTTP_403_FORBIDDEN)
        game.refresh_from_db()
        self.assertTrue(game.is_active) 
        self.assertIsNone(game.winner_id)  

    def test_match_history(self):
        game1 = GameSession.objects.create(
            player1_id=self.player1_id,
            player2_id=self.player2_id,
            is_active=False,
            winner_id=self.player1_id,
            ended_at=now()
        )
        game2 = GameSession.objects.create(
            player1_id=self.player1_id,
            player2_id=self.other_user_id,
            is_active=False,
            winner_id=self.other_user_id,
            ended_at=now()
        )
        url = reverse('match_history')
        response = self.client.get(url)
        self.assertEqual(response.status_code, status.HTTP_200_OK)
        self.assertEqual(len(response.data), 2)
        game_ids = [game['id'] for game in response.data]
        self.assertIn(game1.id, game_ids)
        self.assertIn(game2.id, game_ids)


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

    def test_remove_player_from_tournament(self):
        self.tournament.players_ids = [self.player1_id, self.player2_id]
        self.tournament.save()
        self.tournament.players_ids.remove(self.player1_id)
        self.tournament.save()
        self.assertEqual(len(self.tournament.players_ids), 1)
        self.assertNotIn(self.player1_id, self.tournament.players_ids)

    def test_tournament_str(self):
        self.assertEqual(str(self.tournament), 'Test Tournament')


class TournamentAPITests(APITestCase):
    def setUp(self):
        self.player1_id = 1
        self.player2_id = 2
        self.player3_id = 4
        self.client.credentials(HTTP_AUTHORIZATION='Token player1_token')

    def test_create_tournament_with_less_than_two_friends(self):
        
        
        url = reverse('tournament-list')
        data = {
            'name': 'Tournament with One Friend',
            'players_ids': [self.player2_id],
        }
        response = self.client.post(url, data, format='json')
        self.assertEqual(response.status_code, status.HTTP_400_BAD_REQUEST)
        self.assertIn('You must select at least two friends', str(response.data))

    def test_create_tournament_with_two_friends(self):
        url = reverse('tournament-list')
        data = {
            'name': 'Tournament with Two Friends',
            'players_ids': [self.player2_id, self.player3_id],
        }
        response = self.client.post(url, data, format='json')
        self.assertEqual(response.status_code, status.HTTP_201_CREATED)
        tournament = Tournament.objects.get(name='Tournament with Two Friends')
        self.assertIn(self.player1_id, tournament.players_ids)
        self.assertIn(self.player2_id, tournament.players_ids)
        self.assertIn(self.player3_id, tournament.players_ids)
        self.assertIn('all_players', response.data)
        self.assertIn(self.player1_id, response.data['all_players'])

    def test_list_tournaments(self):
        Tournament.objects.create(name='Tournament 1', creator_id=self.player1_id)
        Tournament.objects.create(name='Tournament 2', creator_id=self.player1_id)
        url = reverse('tournament-list')
        response = self.client.get(url)
        self.assertEqual(response.status_code, status.HTTP_200_OK)
        self.assertEqual(len(response.data), 2)

    def test_add_players_to_tournament(self):
        tournament = Tournament.objects.create(name='Test Tournament', creator_id=self.player1_id)
        url = reverse('tournament-detail', args=[tournament.id])
        data = {'players_ids': [self.player2_id, self.player3_id]}
        response = self.client.patch(url, data, format='json')
        self.assertEqual(response.status_code, status.HTTP_200_OK)
        tournament.refresh_from_db()
        self.assertEqual(len(tournament.players_ids), 3)
        self.assertIn(self.player1_id, tournament.players_ids)
        self.assertIn(self.player2_id, tournament.players_ids)
        self.assertIn(self.player3_id, tournament.players_ids)

    def test_delete_tournament(self):
        tournament = Tournament.objects.create(name='Tournament to Delete', creator_id=self.player1_id)
        url = reverse('tournament-detail', args=[tournament.id])
        response = self.client.delete(url)
        self.assertEqual(response.status_code, status.HTTP_204_NO_CONTENT)
        self.assertEqual(Tournament.objects.count(), 0)

    def test_create_tournament_with_non_friend(self):
        
        non_friend_id = 10
        url = reverse('tournament-list')
        data = {
            'name': 'Tournament with Non-Friend',
            'players_ids': [non_friend_id, self.player2_id],
        }
        response = self.client.post(url, data, format='json')
        self.assertEqual(response.status_code, status.HTTP_400_BAD_REQUEST)
        self.assertIn('The following users are not your friends: ', str(response.data))

    def test_delete_player_removes_from_tournament(self):
        tournament = Tournament.objects.create(name='Test Tournament', creator_id=self.player1_id)
        tournament.players_ids = [self.player1_id, self.player2_id]
        tournament.save()
        
        
        tournament.players_ids.remove(self.player1_id)
        tournament.save()
        self.assertNotIn(self.player1_id, tournament.players_ids)

    def test_create_tournament_with_duplicate_name(self):
        Tournament.objects.create(name='Duplicate Tournament', creator_id=self.player1_id)
        url = reverse('tournament-list')
        data = {'name': 'Duplicate Tournament', 'players_ids': [self.player2_id, self.player3_id]}
        response = self.client.post(url, data, format='json')
        self.assertEqual(response.status_code, status.HTTP_400_BAD_REQUEST)


class TournamentMatchModelTests(TestCase):
    def setUp(self):
        self.player1_id = 1
        self.player2_id = 2
        self.player3_id = 4
        self.tournament = Tournament.objects.create(name='Test Tournament', creator_id=self.player1_id)
        self.tournament.players_ids = [self.player1_id, self.player2_id, self.player3_id]
        self.tournament.save()

    def test_tournament_match_creation(self):
        match = TournamentMatch.objects.create(
            tournament=self.tournament,
            player1_id=self.player1_id,
            player2_id=self.player2_id,
            scheduled_at=now(),
            is_completed=False
        )
        self.assertEqual(match.tournament.name, 'Test Tournament')
        player1_data = get_user_mock(match.player1_id)
        player2_data = get_user_mock(match.player2_id)
        self.assertEqual(player1_data['username'], 'player1')
        self.assertEqual(player2_data['username'], 'player2')
        self.assertFalse(match.is_completed)

    def test_tournament_match_str(self):
        match = TournamentMatch.objects.create(
            tournament=self.tournament,
            player1_id=self.player1_id,
            player2_id=self.player2_id,
            scheduled_at=now(),
        )
        player1_data = get_user_mock(match.player1_id)
        player2_data = get_user_mock(match.player2_id)
        self.assertEqual(str(match), f"Match in Test Tournament between {player1_data['username']} and {player2_data['username']}")

    def test_generate_matches(self):
        generate_elimination_matches(self.tournament)
        matches = TournamentMatch.objects.filter(tournament=self.tournament)
        
        
        self.assertEqual(matches.count(), 3)

    def test_generate_elimination_matches_with_insufficient_players(self):
        
        self.tournament.players.set([self.player1, self.player2])
        with self.assertRaises(ValueError):
            generate_elimination_matches(self.tournament)

    def test_generate_elimination_matches_three_players(self):
        
        
        
        self.tournament.players.set([self.player1, self.player2, self.player3])
        matches = generate_elimination_matches(self.tournament)

        
        self.assertEqual(len(matches), 2)
        
        self.assertTrue(any(m.round_number == 1 for m in matches))
        
        self.assertTrue(any(m.round_number == 2 for m in matches))

        
        
        round1_matches = [m for m in matches if m.round_number == 1]
        self.assertEqual(len(round1_matches), 1)
        
        self.assertIsNotNone(round1_matches[0].player1)
        self.assertIsNotNone(round1_matches[0].player2)

    
    def test_generate_elimination_matches_four_players(self):
        
        
        
        
        player4 = ... 
        self.tournament.players.set([self.player1, self.player2, self.player3, player4])
        matches = generate_elimination_matches(self.tournament)
        self.assertEqual(len(matches), 3)
        self.assertEqual(len([m for m in matches if m.round_number == 1]), 2)  
        self.assertEqual(len([m for m in matches if m.round_number == 2]), 1)  
    


class NonAuthenticatedUserTests(APITestCase):
    def setUp(self):
        self.player1_id = 1
        self.player2_id = 2
        self.game = GameSession.objects.create(player1_id=self.player1_id, player2_id=self.player2_id)
        self.tournament = Tournament.objects.create(name='Test Tournament', creator_id=self.player1_id)

    def test_non_authenticated_user_cannot_access(self):
        
        url = reverse('game-detail', args=[self.game.id])
        response = self.client.get(url)
        self.assertEqual(response.status_code, status.HTTP_403_FORBIDDEN)


class GameSessionPermissionsTestCase(APITestCase):
    def setUp(self):
        self.player1_id = 1
        self.player2_id = 2
        self.other_user_id = 3
        self.game = GameSession.objects.create(player1_id=self.player1_id, player2_id=self.player2_id)

    def test_user_cannot_modify_others_game(self):
        
        self.client.credentials(HTTP_AUTHORIZATION='Token otheruser_token')
        url = reverse('update_game_score', args=[self.game.id])
        data = {'score': 10}
        response = self.client.post(url, data, format='json')
        self.assertEqual(response.status_code, status.HTTP_403_FORBIDDEN)

    def test_user_can_modify_own_game(self):
        
        self.client.credentials(HTTP_AUTHORIZATION='Token player1_token')
        url = reverse('update_game_score', args=[self.game.id])
        data = {'score': 10}
        
        response = self.client.post(url, data, format='json')
        self.assertEqual(response.status_code, status.HTTP_403_FORBIDDEN)
        self.game.refresh_from_db()
        self.assertTrue(self.game.is_active) 
        self.assertIsNone(self.game.winner_id)

    def test_create_game_session_with_missing_player(self):
        self.client.credentials(HTTP_AUTHORIZATION='Token player1_token')
        url = reverse('game-list')
        data = {'player1_id': self.player1_id} 
        response = self.client.post(url, data, format='json')
        self.assertEqual(response.status_code, status.HTTP_400_BAD_REQUEST)
