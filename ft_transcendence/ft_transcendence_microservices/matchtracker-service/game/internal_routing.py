
from django.urls import re_path
from .consumers import GameSessionConsumer

websocket_urlpatterns = [

    re_path(r'^ws/game_sessions/$', GameSessionConsumer.as_asgi()),
]
