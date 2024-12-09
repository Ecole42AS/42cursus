import logging
from django.utils import timezone
from .models import TournamentMatch

logger = logging.getLogger(__name__)

def generate_tournament_matches(tournament):
    """
    Génère les matchs pour un tournoi donné (chaque joueur affronte tous les autres une fois).
    """
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
    logger.info(f"Generated {len(matches)} matches for tournament {tournament.name}.")
    return matches







