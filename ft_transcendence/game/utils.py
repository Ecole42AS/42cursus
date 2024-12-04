from django.utils import timezone
from .models import TournamentMatch

def generate_tournament_matches(tournament):
    players = list(tournament.players.all())
    matches = []
    for i in range(len(players)):
        for j in range(i + 1, len(players)):
            match = TournamentMatch.objects.create(
                tournament=tournament,
                player1=players[i],
                player2=players[j],
                scheduled_at=timezone.now()
            )
            matches.append(match)
    return matches
