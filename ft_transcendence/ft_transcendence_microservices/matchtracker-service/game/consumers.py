from channels.generic.websocket import AsyncWebsocketConsumer
import json

class GameConsumer(AsyncWebsocketConsumer):
    async def connect(self):
        # Récupérez l'ID du match depuis l'URL WebSocket
        self.match_id = self.scope['url_route']['kwargs']['match_id']
        self.group_name = f"match_{self.match_id}"

        # Ajoutez le canal WebSocket au groupe de ce match
        await self.channel_layer.group_add(
            self.group_name,
            self.channel_name
        )
        await self.accept()  # Accepter la connexion WebSocket

    async def disconnect(self, close_code):
        # Retirer le canal WebSocket du groupe
        await self.channel_layer.group_discard(
            self.group_name,
            self.channel_name
        )

    async def receive(self, text_data):
        # Traiter les données reçues via le WebSocket
        data = json.loads(text_data)
        action = data.get('action', None)
        player = data.get('player', None)

        # Exemple de logique d'action
        if action == "move":
            # Diffuser le mouvement à tous les clients connectés au groupe
            await self.channel_layer.group_send(
                self.group_name,
                {
                    "type": "game_update",
                    "message": f"Player {player} moved."
                }
            )

    async def game_update(self, event):
        # Diffuser les mises à jour de jeu reçues
        await self.send(text_data=json.dumps({
            "message": event["message"]
        }))
