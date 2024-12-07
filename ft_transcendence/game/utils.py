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


# logger = logging.getLogger(__name__)

# def generate_elimination_matches(tournament):
#     """
#     Génère les matchs pour un tournoi à élimination directe.
#     """
#     players = list(tournament.players.all())
#     if len(players) < 3:
#         raise ValueError("Le tournoi doit avoir au moins trois joueurs.")

#     matches = []
#     round_number = 1

#     while len(players) > 1:
#         round_matches = []
#         for i in range(0, len(players), 2):
#             if i + 1 < len(players):
#                 match = TournamentMatch.objects.create(
#                     tournament=tournament,
#                     player1=players[i],
#                     player2=players[i + 1],
#                     scheduled_at=timezone.now(),
#                     round_number=round_number
#                 )
#                 round_matches.append(match)
#                 matches.append(match)
#             else:
#                 # Si le nombre de joueurs est impair, le dernier joueur avance automatiquement
#                 players[i].advance_to_next_round = True
#                 players[i].save()

#         # Préparer les joueurs pour le prochain tour
#         players = [match.winner for match in round_matches if match.winner]
#         round_number += 1

#     logger.info(f"Generated {len(matches)} elimination matches for tournament {tournament.name}.")
#     return matches