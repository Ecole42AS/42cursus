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
from django.urls import re_path
from game.consumers import GameSessionConsumer

websocket_urlpatterns = [
    # Ici, on écoute une URL globale pour les notifications de game sessions.
    re_path(r'^ws/game_sessions/$', GameSessionConsumer.as_asgi()),
]

