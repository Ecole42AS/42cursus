import requests
from django.conf import settings
import logging
from django.utils import timezone
from django.http import HttpResponse
from django.conf import settings
from functools import lru_cache

logger = logging.getLogger('matchtracker-service')

def test_logs(request):
    logger.debug("Test DEBUG log")
    logger.info("Test INFO log")
    logger.warning("Test WARNING log")
    logger.error("Test ERROR log")
    return HttpResponse("Logs testés, vérifiez le fichier de log.")
    
# def get_user_data(user_id, token):
#     """
#     Récupère les informations de l'utilisateur à partir du microservice `user-service`.
#     """
#     try:
#         headers = {"Authorization": f"Bearer {token}"}
#         user_service_url = f"{settings.USER_SERVICE_URL}/{user_id}/"
#         logger.debug(f"Attempting to fetch user data from {user_service_url} with token: {token}")

#         response = requests.get(user_service_url, headers=headers, timeout=5)
#         response.raise_for_status()
#         return response.json()
#     except requests.RequestException as e:
#         logger.error(f"Failed to fetch user data: {e}")
#         return None



# def get_user_data(user_id, token):
#     """
#     Récupère les informations de l'utilisateur à partir du microservice `user-service`.
#     """
#     try:
#         headers = {"Authorization": f"Bearer {token}"}
#         response = requests.get(f"{settings.USER_SERVICE_URL}/{user_id}/", headers=headers, timeout=5)
#         response.raise_for_status()

#         data = response.json()
#         if not data or 'username' not in data:
#             logger.error(f"Invalid data for user_id {user_id}: {data}")
#             return None

#         return data
#     except requests.RequestException as e:
#         logger.error(f"Error fetching user data for user_id {user_id}: {e}")
#         return None

def get_user_data(user_id, token):
    """
    Récupère les informations de l'utilisateur à partir du microservice `user-service`.
    """
    try:
        headers = {"Authorization": f"Bearer {token}"}
        url = f"{settings.USER_SERVICE_URL}/{user_id}/"
        logger.debug(f"Fetching user data from {url} with headers {headers}")
        
        response = requests.get(url, headers=headers, timeout=5)
        logger.debug(f"Response received: {response.status_code} - {response.text}")
        
        response.raise_for_status()
        data = response.json()
        
        if not data or 'username' not in data:
            logger.error(f"Invalid data received for user_id {user_id}: {data}")
            return None

        logger.info(f"Successfully fetched user data for user_id {user_id}: {data}")
        return data
    except requests.RequestException as e:
        logger.error(f"Error fetching user data for user_id {user_id} from {url}: {e}")
        return None
    
# @staticmethod
# # @lru_cache(maxsize=128)
# def get_user(user_id, token=None):
#     """
#     Récupère les données utilisateur. Retourne None si l'utilisateur est introuvable ou en cas d'erreur.
#     """
#     if not user_id:
#         return None
#     try:
#         return get_user_data(user_id, token)
#     except KeyError as e:
#         logger.error(f"KeyError while fetching user data for user_id {user_id}: {e}")
#         return {"username": "Unknown"}
#     except requests.RequestException as e:
#         logger.error(f"RequestException while fetching user data for user_id {user_id}: {e}")
#         return {"username": "Unknown"}

@staticmethod
def get_user(user_id, token=None):
    """
    Récupère les données utilisateur. Retourne None si l'utilisateur est introuvable ou en cas d'erreur.
    """
    logger.debug(f"get_user called with user_id: {user_id} and token: {token}")
    
    if not user_id:
        logger.warning("get_user called with an invalid user_id: None")
        return None
    
    try:
        user_data = get_user_data(user_id, token)
        if user_data:
            logger.info(f"User data retrieved: {user_data}")
        else:
            logger.warning(f"No user data found for user_id {user_id}")
        return user_data
    except KeyError as e:
        logger.error(f"KeyError while fetching user data for user_id {user_id}: {e}")
        return {"username": "Unknown"}
    except requests.RequestException as e:
        logger.error(f"RequestException while fetching user data for user_id {user_id}: {e}")
        return {"username": "Unknown"}

    
# def get_user_profile(user_id, token):
#     """
#     Récupère les informations du profil utilisateur à partir du microservice `user-service`.
#     """
#     try:
#         headers = {"Authorization": f"Bearer {token}"}
#         response = requests.get(f"{settings.USER_SERVICE_URL}/profile/{user_id}/", headers=headers)
#         response.raise_for_status()
#         return response.json()  # Retourne le JSON contenant les données du profil
#     except requests.RequestException as e:
#         print(f"Erreur lors de la récupération du profil utilisateur : {e}")
#         return None

def get_user_profile(user_id, token):
    """
    Récupère les informations du profil utilisateur à partir du microservice `user-service`.
    """
    logger.debug(f"Fetching profile for user_id={user_id} using token={token}")
    try:
        headers = {"Authorization": f"Bearer {token}"}
        url = f"{settings.USER_SERVICE_URL}/profile/{user_id}/"
        logger.debug(f"Making GET request to {url} with headers={headers}")
        response = requests.get(url, headers=headers, timeout=5)
        response.raise_for_status()

        logger.debug(f"Profile fetched successfully for user_id={user_id}: {response.json()}")
        return response.json()
    except requests.HTTPError as e:
        logger.error(f"HTTP error while fetching profile for user_id={user_id}: {e}")
        return None
    except requests.RequestException as e:
        logger.error(f"Request exception while fetching profile for user_id={user_id}: {e}")
        return None



import logging
import requests
from django.conf import settings
from rest_framework.exceptions import ValidationError

logger = logging.getLogger(__name__)

def get_friendship(user_id, token):
    """
    Récupère les amitiés pour un utilisateur donné depuis le microservice `user`.
    """
    try:
        headers = {"Authorization": f"Bearer {token}"}
        url = f"{settings.USER_SERVICE_URL}/friendships/{user_id}/"
        timeout = getattr(settings, "USER_SERVICE_TIMEOUT", 5)  # Timeout configurable

        logger.debug(f"Appel à {url} pour récupérer les amitiés avec user_id={user_id}")
        response = requests.get(url, headers=headers, timeout=timeout)

        response.raise_for_status()  # Génère une exception pour les codes HTTP 4xx/5xx

        try:
            return response.json()  # Renvoie les amitiés au format JSON
        except ValueError:
            logger.error(f"Réponse non JSON reçue du service utilisateur : {response.text}")
            raise ValidationError("Le service des amis a renvoyé une réponse invalide.")
    
    except requests.exceptions.Timeout:
        logger.error(f"Timeout lors de la récupération des amitiés pour user_id {user_id}.")
        raise ValidationError("Le service des amis ne répond pas dans les délais.")
    
    except requests.exceptions.HTTPError as http_err:
        logger.error(f"Erreur HTTP {response.status_code} lors de la récupération des amitiés : {http_err}")
        raise ValidationError(f"Erreur HTTP lors de l'appel au service des amis : {response.status_code}")
    
    except requests.RequestException as e:
        logger.error(f"Erreur lors de la communication avec le service utilisateur : {e}")
        raise ValidationError("Une erreur est survenue lors de la communication avec le service utilisateur.")


class TokenManager:
    _cached_token = None

    @staticmethod
    def get_jwt_token():
        """
        Retourne un token JWT valide. Génère un nouveau token si le cache est vide ou expiré.
        """
        if TokenManager._cached_token:
            return TokenManager._cached_token

        # Endpoint pour obtenir un nouveau token
        url = f"{settings.BASE_USER_SERVICE_URL}/api/token/"
        payload = {
            "username": settings.SERVICE_USERNAME,
            "password": settings.SERVICE_PASSWORD
        }

        try:
            response = requests.post(url, json=payload, timeout=5)
            response.raise_for_status()
            data = response.json()

            # Cachez le token
            TokenManager._cached_token = data['access']
            return TokenManager._cached_token
        except requests.RequestException as e:
            logger.error(f"Failed to fetch JWT token: {e}")
            return None

def validate_user_token(token):
    """
    Valide le token JWT auprès du User Service et récupère les informations utilisateur.
    """
    headers = {"Authorization": f"Bearer {token}"}
    user_service_url = f"{settings.BASE_USER_SERVICE_URL}/validate/"

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

def update_player_stats(winner_id, loser_id, score_winner=None, score_loser=None, jwt_token=None):
    """
    Notifie le User Service pour mettre à jour les statistiques des joueurs.
    """
    user_service_url = f"{settings.USER_SERVICE_URL}/internal/update-stats/"
    
    # Construire le payload pour la mise à jour
    payload = {
        "winner_id": winner_id,
        "loser_id": loser_id,
        "score_winner": score_winner,
        "score_loser": score_loser,
    }
    
    # Utiliser le JWT transmis par le moteur de jeu
    headers = {"Authorization": f"Bearer {jwt_token or settings.INTERNAL_API_KEY}"}
    logger.debug(f"Authorization header used: {headers}")
    logger.debug(f"Payload sent to User Service: {payload}")

    try:
        # Envoyer la requête POST au User Service
        response = requests.post(user_service_url, json=payload, headers=headers)
        
        if response.status_code == 200:
            logger.info("Statistiques mises à jour avec succès dans le User Service.")
        else:
            logger.error(
                f"Erreur lors de la mise à jour des stats : {response.status_code}, {response.json()}"
            )
            raise Exception(f"User Service error: {response.status_code}, {response.json()}")

    except requests.RequestException as e:
        logger.error(f"Échec de la communication avec le User Service : {e}")
        raise Exception(f"Failed to communicate with User Service: {e}")


# def update_player_stats(winner_id, loser_id):
#     """
#     Notifie le User Service pour mettre à jour les statistiques des joueurs.
#     """
#     user_service_url = f"{settings.USER_SERVICE_URL}/internal/update-stats/"

#     payload = {
#         "winner_id": winner_id,
#         "loser_id": loser_id
#     }
#     headers = {"Authorization": f"Bearer {settings.INTERNAL_API_KEY}"}
#     logger.debug(f"Authorization header used: {headers}")


#     try:
#         response = requests.post(user_service_url, json=payload, headers=headers)
#         if response.status_code == 200:
#             logger.info("Statistiques mises à jour avec succès dans le User Service.")
#         else:
#             logger.error(f"Erreur lors de la mise à jour des stats : {response.status_code}, {response.json()}")
#             raise Exception(f"User Service error: {response.status_code}, {response.json()}")
#     except requests.RequestException as e:
#         logger.error(f"Échec de la communication avec le User Service : {e}")
#         raise

# def generate_elimination_matches(tournament):
#     """
#     Génère les matchs pour un tournoi à élimination directe.
#     """

#     from .models import TournamentMatch

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


from rest_framework.exceptions import AuthenticationFailed
import jwt

def validate_service_jwt(token):
    """
    Valide le JWT utilisé pour l'authentification des services internes.
    """
    try:
        decoded_token = jwt.decode(
            token,
            settings.SERVICE_JWT_SECRET,  # Clé secrète partagée pour les services
            algorithms=["HS256"]
        )
        # Vérifiez les revendications spécifiques, si nécessaire
        if "service" not in decoded_token or decoded_token["service"] != "game_engine":
            logger.error(f"JWT invalide : {decoded_token}")
            raise AuthenticationFailed("JWT non valide.")
        return True
    except jwt.ExpiredSignatureError:
        logger.error("JWT expiré.")
        raise AuthenticationFailed("JWT expiré.")
    except jwt.InvalidTokenError as e:
        logger.error(f"JWT invalide : {e}")
        raise AuthenticationFailed("JWT invalide.")
    
from django.utils.timezone import now
from .utils import update_player_stats
from .models import GameSession

def update_scores_and_stats(game_id, score_player1, score_player2):
    """
    Met à jour les scores, termine le match si nécessaire, et met à jour les statistiques.
    """
    try:
        game = GameSession.objects.get(pk=game_id)
        logger.debug(f"GameSession récupérée : {game}")

        if not game.start_time:
            logger.error("L'heure de début du match n'est pas définie.")
            raise ValueError("L'heure de début du match (start_time) n'est pas définie.")

        if not game.is_active:
            logger.warning(f"Match {game_id} déjà terminé.")
            raise ValueError("Ce match est terminé. Les scores ne peuvent pas être modifiés.")

        # Mettre à jour les scores
        game.score_player1 = score_player1
        game.score_player2 = score_player2

        # Vérifiez si le match a dépassé la limite de temps
        if (now() - game.start_time).total_seconds() >= 60:
            logger.info(f"Le match {game_id} dépasse la limite de temps. Il sera terminé.")
            game.is_active = False
            game.ended_at = now()

            # Déterminer le gagnant
            if game.score_player1 > game.score_player2:
                game.winner_id = game.player1_id
            elif game.score_player2 > game.score_player1:
                game.winner_id = game.player2_id
            else:
                game.winner_id = None  # Match nul

            logger.info(f"Match {game_id} terminé. Vainqueur : {game.winner_id if game.winner_id else 'Match nul'}.")

            # Mettre à jour les statistiques des joueurs
            if game.winner_id:
                update_player_stats(
                    winner_id=game.winner_id,
                    loser_id=game.player1_id if game.winner_id == game.player2_id else game.player2_id
                )

        # Sauvegarder les changements
        game.save()
        return {'detail': f"Match {game_id} mis à jour avec succès."}

    except GameSession.DoesNotExist:
        logger.warning(f"GameSession {game_id} non trouvée.")
        raise ValueError("Match non trouvé.")
    except Exception as e:
        logger.error(f"Erreur lors de la mise à jour des scores : {e}")
        raise



def notify_game_engine(game_session, token):
    """
    Notifie le moteur de jeu qu'une GameSession a été créée.
    """
    from rest_framework import serializers

    try:
        headers = {"Authorization": f"Bearer {token}"}
        url = f"{settings.GAME_ENGINE_URL}/start-game/"
        payload = {
            "game_session_id": game_session.id,
            "player1_id": game_session.player1_id,
            "player2_id": game_session.player2_id,
            "duration": game_session.duration,
            "start_time": game_session.start_time.isoformat(),
        }

        logger.debug(f"Appel à {url} pour notifier le moteur de jeu avec la GameSession {game_session.id}")
        response = requests.post(url, json=payload, headers=headers, timeout=settings.GAME_ENGINE_TIMEOUT)

        response.raise_for_status()  # Exception si code HTTP 4xx/5xx

        try:
            return response.json()  # Retourne la réponse JSON du moteur de jeu
        except ValueError:
            logger.error(f"Réponse non JSON reçue du moteur de jeu : {response.text}")
            raise serializers.ValidationError("Réponse invalide du moteur de jeu.")
    except requests.RequestException as e:
        logger.error(f"Erreur lors de la communication avec le moteur de jeu : {e}")
        raise serializers.ValidationError("Erreur lors de la communication avec le moteur de jeu.")

def generate_elimination_matches(tournament, token):
    """
    Génère les matchs pour un tournoi à élimination directe et notifie le moteur de jeu.
    """
    from .models import TournamentMatch, GameSession
    from rest_framework import serializers

    players = list(tournament.players)  # Si c'est un champ JSONField
    logger.debug(f"Generating elimination matches for tournament {tournament.name} with {len(players)} players.")
    matches = []
    round_number = 1

    # Génération des matchs par rounds
    while len(players) > 1:
        round_matches = []
        for i in range(0, len(players), 2):
            # Créez une GameSession pour chaque match
            game_session = GameSession.objects.create(
                player1_id=players[i],
                player2_id=players[i + 1],
                is_active=True,
                created_at=timezone.now(),
                start_time=timezone.now(),
                duration=60,  # Durée par défaut de la session
            )
            logger.debug(f"Created GameSession for match {game_session.id}")

            # Créez un TournamentMatch et associez-le à la GameSession
            match = TournamentMatch.objects.create(
                tournament=tournament,
                player1_id=players[i],
                player2_id=players[i + 1],
                scheduled_at=timezone.now(),
                round_number=round_number,
                game_session=game_session,  # Associez la GameSession au match
            )
            round_matches.append(match)
            matches.append(match)

            # Notifiez le moteur de jeu pour la GameSession
            try:
                notify_game_engine(game_session, token)
                logger.debug(f"Notified Game Engine for GameSession {game_session.id}")
            except Exception as e:
                logger.error(f"Failed to notify Game Engine for GameSession {game_session.id}: {e}")
                raise serializers.ValidationError(f"Erreur lors de la notification du moteur de jeu pour la session {game_session.id}.")

        # Préparer les joueurs pour le prochain tour en fonction des gagnants
        players = [
            match.winner_id for match in round_matches if match.winner_id
        ]
        round_number += 1

    logger.info(f"Generated {len(matches)} elimination matches for tournament {tournament.name}.")
    return matches
