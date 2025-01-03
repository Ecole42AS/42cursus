import requests
from django.conf import settings
import logging
from django.utils import timezone
from django.http import HttpResponse


logger = logging.getLogger('matchtracker-service')


def test_logs(request):
    logger.debug("Test DEBUG log")
    logger.info("Test INFO log")
    logger.warning("Test WARNING log")
    logger.error("Test ERROR log")
    return HttpResponse("Logs testés, vérifiez le fichier de log.")
    
def get_user_data(user_id, token):
    """
    Récupère les informations de l'utilisateur à partir du microservice `user-service`.
    """
    try:
        headers = {"Authorization": f"Bearer {token}"}
        user_service_url = f"{settings.USER_SERVICE_URL}/{user_id}/"
        logger.debug(f"Attempting to fetch user data from {user_service_url} with token: {token}")

        response = requests.get(user_service_url, headers=headers, timeout=5)
        response.raise_for_status()
        return response.json()
    except requests.RequestException as e:
        logger.error(f"Failed to fetch user data: {e}")
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


import requests
import logging
from django.conf import settings

logger = logging.getLogger('myapp')

def validate_user_token(token):
    """
    Valide le token JWT auprès du User Service et récupère les informations utilisateur.
    """
    headers = {"Authorization": f"Bearer {token}"}
    user_service_url = f"{settings.USER_SERVICE_URL}/validate/"

    try:
        logger.debug(f"Sending token validation request to: {user_service_url}")
        response = requests.get(user_service_url, headers=headers)
        logger.debug(f"Response status code: {response.status_code}")
        logger.debug(f"Response content: {response.content}")

        response.raise_for_status()
        data = response.json()
        logger.debug(f"Decoded user data: {data}")
        return data

    except requests.RequestException as e:
        logger.error(f"Error while validating token: {e}")
        return None

def is_token_revoked(token):
    """
    Vérifie si un token est révoqué.
    """
    # Implémentez une vérification dans votre base de données ou cache pour les tokens révoqués.
    revoked_tokens = ["list", "of", "revoked", "tokens"]  # Exemple simple
    return token in revoked_tokens


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