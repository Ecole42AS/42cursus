from channels.generic.websocket import AsyncWebsocketConsumer
import json

class GameConsumer(AsyncWebsocketConsumer):
    async def connect(self):
        
        self.match_id = self.scope['url_route']['kwargs']['match_id']
        self.group_name = f"match_{self.match_id}"

        
        await self.channel_layer.group_add(
            self.group_name,
            self.channel_name
        )
        await self.accept()  

    async def disconnect(self, close_code):
        
        await self.channel_layer.group_discard(
            self.group_name,
            self.channel_name
        )

    async def receive(self, text_data):
        
        data = json.loads(text_data)
        action = data.get('action', None)
        player = data.get('player', None)

        
        if action == "move":
            
            await self.channel_layer.group_send(
                self.group_name,
                {
                    "type": "game_update",
                    "message": f"Player {player} moved."
                }
            )

    async def game_update(self, event):
        
        await self.send(text_data=json.dumps({
            "message": event["message"]
        }))
