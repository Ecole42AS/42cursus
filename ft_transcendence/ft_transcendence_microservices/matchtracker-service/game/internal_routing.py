# matchtracker-service/game/internal_routing.py
from django.urls import re_path
from .consumers import GameSessionConsumer  # Ce consumer ne vérifie pas JWT

websocket_urlpatterns = [
    # Route interne pour la création de game sessions (pas de JWT requis)
    re_path(r'^ws/game_sessions/$', GameSessionConsumer.as_asgi()),
]
