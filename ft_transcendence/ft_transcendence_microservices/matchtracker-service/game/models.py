from django.db import models
from .utils import get_user, TokenManager

class GameSession(models.Model):
    player1_id = models.IntegerField(null=True, blank=True)
    player2_id = models.IntegerField(null=True, blank=True)
    score_player1 = models.IntegerField(default=0)
    score_player2 = models.IntegerField(default=0)
    winner_id = models.IntegerField(null=True, blank=True)
    pong_game_id = models.IntegerField(null=True, blank=True)
    is_active = models.BooleanField(default=True)
    created_at = models.DateTimeField(auto_now_add=True)
    start_time = models.DateTimeField(null=True, blank=True)
    duration = models.IntegerField(default=60)
    ended_at = models.DateTimeField(null=True, blank=True)
    
    def __str__(self):
        try:
            token = TokenManager.get_jwt_token()
            player1 = get_user(self.player1_id, token)
            player2 = get_user(self.player2_id, token)

            if player1 and player2:
                return f"GameSession {self.id} between {player1['username']} and {player2['username']}"
            elif player1:
                return f"GameSession {self.id} with {player1['username']} (player2 unknown)"
            elif player2:
                return f"GameSession {self.id} with {player2['username']} (player1 unknown)"
        except Exception as e:
            return f"GameSession {self.id} with unknown players (error: {e})"
        
class Tournament(models.Model):
    name = models.CharField(max_length=255, unique=True)
    creator_id = models.IntegerField(null=True, blank=True)
    players = models.JSONField(default=list)
    winner_id = models.IntegerField(null=True, blank=True)
    created_at = models.DateTimeField(auto_now_add=True)

    def __str__(self):
        return self.name

class TournamentMatch(models.Model):
    tournament = models.ForeignKey(Tournament, on_delete=models.CASCADE)
    game_session = models.ForeignKey(GameSession, null=True, blank=True, on_delete=models.SET_NULL)
    player1_id = models.IntegerField(null=True, blank=True)
    player2_id = models.IntegerField(null=True, blank=True)
    winner_id = models.IntegerField(null=True, blank=True)
    is_completed = models.BooleanField(default=False)
    scheduled_at = models.DateTimeField()
    round_number = models.IntegerField(default=1)
    advance_to_next_round = models.BooleanField(default=False)


    def __str__(self):
        return self.format_match_str()

    def format_match_str(self):
        """
        Génère une chaîne de caractères pour représenter un match de tournoi.
        """
        try:
            token = TokenManager.get_jwt_token()
            player1 = get_user(self.player1_id, token)
            player2 = get_user(self.player2_id, token)

            if player1 and player2:
                return f"Match in {self.tournament.name} between {player1['username']} and {player2['username']}"
            elif player1:
                return f"Match in {self.tournament.name} with {player1['username']} (player2 unknown)"
            elif player2:
                return f"Match in {self.tournament.name} with {player2['username']} (player1 unknown)"
        except Exception as e:
            return f"Match in {self.tournament.name} with unknown players (error: {e})"