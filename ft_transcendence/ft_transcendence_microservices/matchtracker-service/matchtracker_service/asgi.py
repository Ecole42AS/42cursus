import os
import django
from channels.routing import ProtocolTypeRouter, URLRouter
from channels.auth import AuthMiddlewareStack
from django.core.asgi import get_asgi_application
from django.urls import path
from game.consumers import GameConsumer

os.environ.setdefault('DJANGO_SETTINGS_MODULE', 'matchtracker_service.settings')

django.setup()

django_application = get_asgi_application()

application = ProtocolTypeRouter({
    "http": django_application,
    "websocket": AuthMiddlewareStack(
        URLRouter([
            path("ws/game/<int:game_id>/", GameConsumer.as_asgi()),
        ])
    ),
})
