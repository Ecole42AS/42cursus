import json
from channels.generic.websocket import AsyncWebsocketConsumer
import logging

logger = logging.getLogger("matchtracker-service.websocket")

class MatchtrackerConsumer(AsyncWebsocketConsumer):
    async def connect(self):
        logger.info(f"Connexion WebSocket reçue : {self.channel_name}")
        # Récupérer le "room_name" à partir de l'URL
        self.room_name = self.scope["url_route"]["kwargs"].get("room_name")
        if not self.room_name:
            logger.error("Aucun room_name spécifié dans l'URL, fermeture de la connexion.")
            await self.close()
            return

        self.group_name = f"matchtracker_{self.room_name}"
        logger.info(f"Connexion WebSocket acceptée dans le groupe : {self.group_name}")

        # Ajouter le canal WebSocket au groupe correspondant
        await self.channel_layer.group_add(
            self.group_name,
            self.channel_name
        )
        await self.accept()

    async def disconnect(self, close_code):
        logger.info(f"Déconnexion du canal {self.channel_name} du groupe {self.group_name} (code de fermeture: {close_code})")
        await self.channel_layer.group_discard(
            self.group_name,
            self.channel_name
        )

    async def receive(self, text_data):
        try:
            data = json.loads(text_data)
        except json.JSONDecodeError:
            logger.error("Message reçu n'est pas du JSON valide")
            return

        action = data.get("action")
        payload = data.get("payload", {})
        logger.debug(f"Message reçu : action={action}, payload={payload}")

        # Exemple d'implémentation : gestion d'une action "move"
        if action == "move":
            await self.handle_move(payload)
        else:
            logger.warning(f"Action non gérée: {action}")

    async def handle_move(self, payload):
        # Ajoutez ici votre logique métier pour traiter l'action "move"
        message = payload.get("message", "Aucune donnée fournie")
        logger.info(f"Traitement de l'action 'move' avec le message: {message}")

        # Diffuser le message à tous les clients connectés dans le groupe
        await self.channel_layer.group_send(
            self.group_name,
            {
                "type": "broadcast_message",  # Cette valeur correspond à la méthode "broadcast_message"
                "message": message,
            }
        )

    async def broadcast_message(self, event):
        # Méthode appelée par group_send pour diffuser les messages
        message = event.get("message", "")
        logger.debug(f"Diffusion du message dans le groupe {self.group_name}: {message}")
        await self.send(text_data=json.dumps({
            "message": message,
        }))
