import random
from django.utils import timezone
from .models import TournamentMatch

def generate_tournament_matches(tournament):
    players = list(tournament.players.all())
    random.shuffle(players)
    while len(players) >= 2:
        player1 = players.pop()
        player2 = players.pop()
        match = TournamentMatch.objects.create(
            tournament=tournament,
            player1=player1,
            player2=player2,
            scheduled_at=timezone.now()
        )
