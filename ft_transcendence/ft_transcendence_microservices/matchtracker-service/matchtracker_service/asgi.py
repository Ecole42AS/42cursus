# import os
# import django
# from channels.routing import ProtocolTypeRouter, URLRouter
# from channels.auth import AuthMiddlewareStack
# from django.core.asgi import get_asgi_application
# from .routing_websockets import websocket_urlpatterns

# os.environ.setdefault("DJANGO_SETTINGS_MODULE", "matchtracker_service.settings")
# django.setup()

# django_application = get_asgi_application()

# application = ProtocolTypeRouter({
#     "http": django_application,
#     "websocket": AuthMiddlewareStack(
#         URLRouter(websocket_urlpatterns)
#     ),
# })


# import os
# import django
# from channels.routing import ProtocolTypeRouter, URLRouter
# from channels.auth import AuthMiddlewareStack
# from django.core.asgi import get_asgi_application
# from matchtracker_service.routing import websocket_urlpatterns

# os.environ.setdefault("DJANGO_SETTINGS_MODULE", "matchtracker_service.settings")
# django.setup()

# application = ProtocolTypeRouter({
#     "http": get_asgi_application(),
#     "websocket": AuthMiddlewareStack(
#         URLRouter(websocket_urlpatterns)
#     ),
# })

# import os
# import django
# from channels.routing import ProtocolTypeRouter, URLRouter
# from django.core.asgi import get_asgi_application
# from channels.auth import AuthMiddlewareStack
# # Importez votre middleware personnalisé
# from matchtracker_service.jwt_auth_ws_middleware import JWTAuthMiddleware
# from matchtracker_service.routing import websocket_urlpatterns  # ou depuis game/routing_websockets.py selon votre organisation

# os.environ.setdefault("DJANGO_SETTINGS_MODULE", "matchtracker_service.settings")
# django.setup()

# application = ProtocolTypeRouter({
#     "http": get_asgi_application(),
#     "websocket": JWTAuthMiddleware(
#         URLRouter(websocket_urlpatterns)
#     ),
# })


import os
import django
from channels.routing import ProtocolTypeRouter, URLRouter
from django.core.asgi import get_asgi_application
from django.urls import re_path
from matchtracker_service.jwt_auth_ws_middleware import JWTAuthMiddleware  # Votre middleware pour JWT
from game.internal_routing import websocket_urlpatterns as internal_ws_patterns
from game.frontend_routing import websocket_urlpatterns as frontend_ws_patterns

os.environ.setdefault("DJANGO_SETTINGS_MODULE", "matchtracker_service.settings")
django.setup()

application = ProtocolTypeRouter({
    "http": get_asgi_application(),
    "websocket": URLRouter([
        # Route pour le frontend : on applique le middleware JWT pour authentifier la connexion.
        re_path(r'^ws/frontend/game/$', JWTAuthMiddleware(frontend_ws_patterns[0].callback)),
        # Route pour la communication interne : pas d'authentification JWT.
        re_path(r'^ws/game_sessions/$', internal_ws_patterns[0].callback),
    ]),
})
