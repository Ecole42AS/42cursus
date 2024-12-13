from channels.auth import AuthMiddlewareStack
from channels.routing import ProtocolTypeRouter, URLRouter
from django.urls import path
from game.consumers import GameConsumer

application = ProtocolTypeRouter({
    "websocket": AuthMiddlewareStack(
        URLRouter([
            # Exemple : un endpoint WebSocket pour une partie donnée
            path('ws/game/<int:game_id>/', GameConsumer.as_asgi()),
        ])
    ),
})
