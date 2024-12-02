from django.db import models
from django.conf import settings

class GameSession(models.Model):
    player1 = models.ForeignKey(settings.AUTH_USER_MODEL, related_name='games_as_player1', on_delete=models.CASCADE)
    player2 = models.ForeignKey(settings.AUTH_USER_MODEL, related_name='games_as_player2', on_delete=models.CASCADE)
    score_player1 = models.IntegerField(default=0)
    score_player2 = models.IntegerField(default=0)
    is_active = models.BooleanField(default=True)
    created_at = models.DateTimeField(auto_now_add=True)

    def __str__(self):
            return f"GameSession {self.id} between {self.player1.username} and {self.player2.username}"

class Tournament(models.Model):
    name = models.CharField(max_length=255)
    players = models.ManyToManyField(settings.AUTH_USER_MODEL, related_name='tournaments') # many to many relationship with the User model
    created_at = models.DateTimeField(auto_now_add=True)

    def __str__(self):
        return self.name
    
class TournamentMatch(models.Model):
    tournament = models.ForeignKey(Tournament, on_delete=models.CASCADE) # many to one relationship with the Tournament model ( automatically sets up a reverse relationship ) add a column which stock id from the tournament
    player1 = models.ForeignKey(settings.AUTH_USER_MODEL, related_name='tournament_matches_as_player1', on_delete=models.CASCADE)
    player2 = models.ForeignKey(settings.AUTH_USER_MODEL, related_name='tournament_matches_as_player2', on_delete=models.CASCADE)
    winner = models.ForeignKey(settings.AUTH_USER_MODEL, related_name='won_matches', on_delete=models.SET_NULL, null=True, blank=True)
    scheduled_at = models.DateTimeField()
    is_completed = models.BooleanField(default=False)

    def __str__(self):
        return f"Match in {self.tournament.name} between {self.player1.username} and {self.player2.username}"

