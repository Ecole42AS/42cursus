
import json
import logging
from channels.generic.websocket import AsyncWebsocketConsumer

logger = logging.getLogger("matchtracker-service.websocket")

import json
import logging
from channels.generic.websocket import AsyncWebsocketConsumer

logger = logging.getLogger("matchtracker-service.websocket")

class FrontendGameConsumer(AsyncWebsocketConsumer):
    async def connect(self):

        if self.scope.get("user") is None or self.scope["user"].is_anonymous:

            await self.close(code=401)
            return

        self.group_name = "frontend_game"
        await self.channel_layer.group_add(self.group_name, self.channel_name)
        await self.accept()
        logger.info("Frontend WebSocket connecté.")

    async def disconnect(self, close_code):
        await self.channel_layer.group_discard(self.group_name, self.channel_name)
        logger.info("Frontend WebSocket déconnecté.")

    async def receive(self, text_data):

        logger.debug(f"Frontend message reçu : {text_data}")

    async def game_notification(self, event):
        await self.send(text_data=json.dumps({
            "type": "game_notification",
            "data": event.get("data", {})
        }))

import json
import logging
from channels.generic.websocket import AsyncWebsocketConsumer

logger = logging.getLogger("matchtracker-service.websocket")

class GameSessionConsumer(AsyncWebsocketConsumer):
    async def connect(self):

        self.group_name = "game_sessions"
        await self.channel_layer.group_add(self.group_name, self.channel_name)
        await self.accept()
        logger.info("Internal GameSession WebSocket connecté.")

    async def disconnect(self, close_code):
        await self.channel_layer.group_discard(self.group_name, self.channel_name)
        logger.info("Internal GameSession WebSocket déconnecté.")

    async def receive(self, text_data):
        logger.debug(f"Internal message reçu : {text_data}")

    async def game_session_start(self, event):

        await self.send(text_data=json.dumps({
            "type": "game_session_start",
            "data": event.get("data", {})
        }))

