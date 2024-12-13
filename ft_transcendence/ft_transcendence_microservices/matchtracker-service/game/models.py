from django.db import models
from django.conf import settings
from django.core.exceptions import ValidationError

class GameSession(models.Model):
    player1_id = models.IntegerField
    player2_id = models.IntegerField
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
            return f"GameSession {self.id} between {self.player1.username} and {self.player2.username}"


class Tournament(models.Model):
    name = models.CharField(max_length=255, unique=True)
    creator_id = models.IntegerField()
    players = models.JSONField(default=list)
    winner_id = models.IntegerField(null=True, blank=True)
    created_at = models.DateTimeField(auto_now_add=True)

    def __str__(self):
        return self.name

class TournamentMatch(models.Model):
    tournament = models.ForeignKey(Tournament, on_delete=models.CASCADE)
    player1_id = models.IntegerField()
    player2_id = models.IntegerField()
    winner_id = models.IntegerField(null=True, blank=True)
    is_completed = models.BooleanField(default=False)
    scheduled_at = models.DateTimeField()


    def __str__(self):
        return f"Match in {self.tournament.name} between {self.player1.username} and {self.player2.username}"

