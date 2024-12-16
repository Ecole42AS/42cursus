import requests
from django.conf import settings
import logging
from django.utils import timezone

logger = logging.getLogger(__name__)

def get_user_data(user_id):
    """
    Récupère les informations de l'utilisateur à partir du microservice `user-service`.
    """
    try:
        response = requests.get(f"{settings.USER_SERVICE_URL}/{user_id}/")
        response.raise_for_status()
        return response.json()
    except requests.RequestException as e:
        print(f"Erreur lors de la récupération des données de l'utilisateur : {e}")
        return None

def get_user_profile(user_id):
    """
    Récupère les informations du profil utilisateur à partir du microservice `user-service`.
    """
    try:
        response = requests.get(f"{settings.USER_SERVICE_URL}/profile/{user_id}/")
        response.raise_for_status()
        return response.json()  # Retourne le JSON contenant les données du profil
    except requests.RequestException as e:
        print(f"Erreur lors de la récupération du profil utilisateur : {e}")
        return None

def get_friendship(user_id):
    """
    Récupère les amitiés pour un utilisateur donné depuis le microservice `user`.
    """
    try:
        response = requests.get(f"{settings.USER_SERVICE_URL}/friendships/{user_id}/")
        response.raise_for_status()  # Vérifie si le statut HTTP est 200
        return response.json()
    except requests.RequestException as e:
        print(f"Erreur lors de la communication avec user-service : {e}")
        return None


def update_player_stats(winner, loser):
    """
    Notifie le User Service pour mettre à jour les statistiques des joueurs.
    """
    user_service_url = settings.USER_SERVICE_URL + "/internal/update-stats/"

    payload = {
        "winner_id": winner.id,
        "loser_id": loser.id
    }
    headers = {"Authorization": f"Bearer {settings.INTERNAL_API_KEY}"}

    try:
        response = requests.post(user_service_url, json=payload, headers=headers)
        if response.status_code == 200:
            print("Statistiques mises à jour avec succès dans le User Service.")
        else:
            print(f"Erreur lors de la mise à jour des stats : {response.status_code}, {response.json()}")
    except Exception as e:
        print(f"Échec de la communication avec le User Service : {e}")

def generate_elimination_matches(tournament):
    """
    Génère les matchs pour un tournoi à élimination directe.
    """

    from .models import TournamentMatch

    players = list(tournament.players.all())
    if len(players) < 3:
        raise ValueError("Le tournoi doit avoir au moins trois joueurs.")

    matches = []
    round_number = 1

    while len(players) > 1:
        round_matches = []
        for i in range(0, len(players), 2):
            if i + 1 < len(players):
                match = TournamentMatch.objects.create(
                    tournament=tournament,
                    player1=players[i],
                    player2=players[i + 1],
                    scheduled_at=timezone.now(),
                    round_number=round_number
                )
                round_matches.append(match)
                matches.append(match)
            else:
                # Si le nombre de joueurs est impair, le dernier joueur avance automatiquement
                players[i].advance_to_next_round = True
                players[i].save()

        # Préparer les joueurs pour le prochain tour
        players = [match.winner for match in round_matches if match.winner]
        round_number += 1

    logger.info(f"Generated {len(matches)} elimination matches for tournament {tournament.name}.")
    return matches