# import json
# from channels.generic.websocket import AsyncWebsocketConsumer
# import logging

# logger = logging.getLogger("matchtracker-service.websocket")

# class MatchtrackerConsumer(AsyncWebsocketConsumer):
#     async def connect(self):
#         logger.info(f"Connexion WebSocket reçue : {self.channel_name}")
#         # Récupérer le "room_name" à partir de l'URL
#         self.room_name = self.scope["url_route"]["kwargs"].get("room_name")
#         if not self.room_name:
#             logger.error("Aucun room_name spécifié dans l'URL, fermeture de la connexion.")
#             await self.close()
#             return

#         self.group_name = f"matchtracker_{self.room_name}"
#         logger.info(f"Connexion WebSocket acceptée dans le groupe : {self.group_name}")

#         # Ajouter le canal WebSocket au groupe correspondant
#         await self.channel_layer.group_add(
#             self.group_name,
#             self.channel_name
#         )
#         await self.accept()

#     async def disconnect(self, close_code):
#         logger.info(f"Déconnexion du canal {self.channel_name} du groupe {self.group_name} (code de fermeture: {close_code})")
#         await self.channel_layer.group_discard(
#             self.group_name,
#             self.channel_name
#         )

#     async def receive(self, text_data):
#         try:
#             data = json.loads(text_data)
#         except json.JSONDecodeError:
#             logger.error("Message reçu n'est pas du JSON valide")
#             return

#         action = data.get("action")
#         payload = data.get("payload", {})
#         logger.debug(f"Message reçu : action={action}, payload={payload}")

#         # Exemple d'implémentation : gestion d'une action "move"
#         if action == "move":
#             await self.handle_move(payload)
#         else:
#             logger.warning(f"Action non gérée: {action}")

#     async def handle_move(self, payload):
#         # Ajoutez ici votre logique métier pour traiter l'action "move"
#         message = payload.get("message", "Aucune donnée fournie")
#         logger.info(f"Traitement de l'action 'move' avec le message: {message}")

#         # Diffuser le message à tous les clients connectés dans le groupe
#         await self.channel_layer.group_send(
#             self.group_name,
#             {
#                 "type": "broadcast_message",  # Cette valeur correspond à la méthode "broadcast_message"
#                 "message": message,
#             }
#         )

#     async def broadcast_message(self, event):
#         # Méthode appelée par group_send pour diffuser les messages
#         message = event.get("message", "")
#         logger.debug(f"Diffusion du message dans le groupe {self.group_name}: {message}")
#         await self.send(text_data=json.dumps({
#             "message": message,
#         }))

import json
import logging
from channels.generic.websocket import AsyncWebsocketConsumer

logger = logging.getLogger("matchtracker-service.websocket")

# class GameSessionConsumer(AsyncWebsocketConsumer):
#     async def connect(self):
#         # Ici, on utilise un groupe global pour toutes les notifications de game session.
#         self.group_name = "game_sessions"
#         logger.info(f"Connexion WebSocket : ajout au groupe {self.group_name}")
#         await self.channel_layer.group_add(self.group_name, self.channel_name)
#         await self.accept()

#     async def disconnect(self, close_code):
#         logger.info(f"Déconnexion WebSocket : retrait du groupe {self.group_name} (code: {close_code})")
#         await self.channel_layer.group_discard(self.group_name, self.channel_name)

#     # Méthode qui sera appelée lorsqu'un message de type "game_session.start" sera envoyé
#     async def game_session_start(self, event):
#         logger.info(f"Notification de démarrage de game session reçue: {event}")
#         await self.send(text_data=json.dumps({
#             "type": "game_session_start",
#             "data": event.get("data", {})
#         }))

# # TESTING
# class GameSessionConsumer(AsyncWebsocketConsumer):
#     async def connect(self):
#         # Pour les tests, autorisez la connexion même si l'utilisateur est anonyme
#         self.group_name = "game_sessions"
#         await self.channel_layer.group_add(self.group_name, self.channel_name)
#         await self.accept()
#         logger.info("Connexion WebSocket acceptée (test mode)")

# matchtracker-service/game/consumers.py
import json
import logging
from channels.generic.websocket import AsyncWebsocketConsumer

logger = logging.getLogger("matchtracker-service.websocket")

class FrontendGameConsumer(AsyncWebsocketConsumer):
    async def connect(self):
        # Ici, vous pouvez vérifier que l'utilisateur (authentifié via JWT dans le middleware) est valide
        if self.scope.get("user") is None or self.scope["user"].is_anonymous:
            # Refuser la connexion si l'authentification échoue
            await self.close(code=401)
            return

        # Pour le frontend, vous pouvez par exemple ajouter le client à un groupe spécifique
        self.group_name = "frontend_game"
        await self.channel_layer.group_add(self.group_name, self.channel_name)
        await self.accept()
        logger.info("Frontend WebSocket connecté.")

    async def disconnect(self, close_code):
        await self.channel_layer.group_discard(self.group_name, self.channel_name)
        logger.info("Frontend WebSocket déconnecté.")

    async def receive(self, text_data):
        # Traitement des messages reçus du frontend
        logger.debug(f"Frontend message reçu : {text_data}")
        # Vous pouvez renvoyer une réponse ou traiter le message selon votre logique

    # Méthode pour recevoir des notifications, par exemple
    async def game_notification(self, event):
        await self.send(text_data=json.dumps({
            "type": "game_notification",
            "data": event.get("data", {})
        }))


# Consumer pour la communication interne (sans authentification JWT)
# class GameSessionConsumer(AsyncWebsocketConsumer):
#     async def connect(self):
#         # Cette route est destinée aux notifications internes (ex. le moteur du jeu)
#         self.group_name = "game_sessions"
#         await self.channel_layer.group_add(self.group_name, self.channel_name)
#         await self.accept()
#         logger.info("Internal GameSession WebSocket connecté.")

#     async def disconnect(self, close_code):
#         await self.channel_layer.group_discard(self.group_name, self.channel_name)
#         logger.info("Internal GameSession WebSocket déconnecté.")

#     async def receive(self, text_data):
#         logger.debug(f"Internal message reçu : {text_data}")
#         # Traiter les messages internes ici

#     async def game_session_start(self, event):
#         # Envoi d'une notification interne, par exemple
#         await self.send(text_data=json.dumps({
#             "type": "game_session_start",
#             "data": event.get("data", {})
#         }))

import json
import logging
from channels.generic.websocket import AsyncWebsocketConsumer

logger = logging.getLogger("matchtracker-service.websocket")

class GameSessionConsumer(AsyncWebsocketConsumer):
    async def connect(self):
        # Cette route est destinée aux notifications internes (ex. le moteur du jeu)
        self.group_name = "game_sessions"
        await self.channel_layer.group_add(self.group_name, self.channel_name)
        await self.accept()
        logger.info("Internal GameSession WebSocket connecté.")

    async def disconnect(self, close_code):
        await self.channel_layer.group_discard(self.group_name, self.channel_name)
        logger.info("Internal GameSession WebSocket déconnecté.")

    async def receive(self, text_data):
        logger.debug(f"Internal message reçu : {text_data}")
        # Traiter les messages internes ici si nécessaire

    async def game_session_start(self, event):
        # Envoi d'une notification interne, par exemple
        await self.send(text_data=json.dumps({
            "type": "game_session_start",
            "data": event.get("data", {})
        }))

