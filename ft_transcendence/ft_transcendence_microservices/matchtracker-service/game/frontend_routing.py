# from channels.auth import AuthMiddlewareStack
# from channels.routing import ProtocolTypeRouter, URLRouter
# from django.urls import path
# from game.consumers import GameConsumer

# application = ProtocolTypeRouter({
#     "websocket": AuthMiddlewareStack(
#         URLRouter([
#             # Exemple : un endpoint WebSocket pour une partie donnée
#             path('ws/game/<int:game_id>/', GameConsumer.as_asgi()),
#         ])
#     ),
# })
# matchtracker-service/game/frontend_routing.py
from django.urls import re_path
from .consumers import FrontendGameConsumer  # Ce consumer est dédié aux connexions du frontend

websocket_urlpatterns = [
    # Route pour le frontend, qui sera protégée par un middleware JWT
    re_path(r'^ws/frontend/game/$', FrontendGameConsumer.as_asgi()),
]
