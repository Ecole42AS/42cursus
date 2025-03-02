from django.db import models
from django.conf import settings
from django.core.exceptions import ValidationError

class GameSession(models.Model):
    player1 = models.ForeignKey(settings.AUTH_USER_MODEL, related_name='games_as_player1', on_delete=models.CASCADE)
    player2 = models.ForeignKey(settings.AUTH_USER_MODEL, related_name='games_as_player2', on_delete=models.CASCADE)
    score_player1 = models.IntegerField(default=0)
    score_player2 = models.IntegerField(default=0)
    winner = models.ForeignKey(settings.AUTH_USER_MODEL, related_name='won_games', on_delete=models.SET_NULL, null=True, blank=True)
    is_active = models.BooleanField(default=True)
    created_at = models.DateTimeField(auto_now_add=True)
    ended_at = models.DateTimeField(null=True, blank=True)


    def __str__(self):
            return f"GameSession {self.id} between {self.player1.username} and {self.player2.username}"


class Tournament(models.Model):
    name = models.CharField(max_length=255, unique=True)
    creator = models.ForeignKey(settings.AUTH_USER_MODEL, related_name='created_tournaments', on_delete=models.CASCADE)
    players = models.ManyToManyField(settings.AUTH_USER_MODEL, related_name='tournaments')
    created_at = models.DateTimeField(auto_now_add=True)

    def __str__(self):
        return self.name

class TournamentMatch(models.Model):
    tournament = models.ForeignKey(Tournament, on_delete=models.CASCADE)
    player1 = models.ForeignKey(settings.AUTH_USER_MODEL, related_name='tournament_matches_as_player1', on_delete=models.CASCADE)
    player2 = models.ForeignKey(settings.AUTH_USER_MODEL, related_name='tournament_matches_as_player2', on_delete=models.CASCADE)
    winner = models.ForeignKey(settings.AUTH_USER_MODEL, related_name='won_matches', on_delete=models.SET_NULL, null=True, blank=True)
    scheduled_at = models.DateTimeField()
    is_completed = models.BooleanField(default=False)


    def __str__(self):
        return f"Match in {self.tournament.name} between {self.player1.username} and {self.player2.username}"

