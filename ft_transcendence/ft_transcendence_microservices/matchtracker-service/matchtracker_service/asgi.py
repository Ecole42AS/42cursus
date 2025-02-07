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

import os
import django
from channels.routing import ProtocolTypeRouter, URLRouter
from django.core.asgi import get_asgi_application
from channels.auth import AuthMiddlewareStack
# Importez votre middleware personnalisé
from matchtracker_service.jwt_auth_ws_middleware import JWTAuthMiddleware
from matchtracker_service.routing import websocket_urlpatterns  # ou depuis game/routing_websockets.py selon votre organisation

os.environ.setdefault("DJANGO_SETTINGS_MODULE", "matchtracker_service.settings")
django.setup()

application = ProtocolTypeRouter({
    "http": get_asgi_application(),
    "websocket": JWTAuthMiddleware(
        URLRouter(websocket_urlpatterns)
    ),
})
