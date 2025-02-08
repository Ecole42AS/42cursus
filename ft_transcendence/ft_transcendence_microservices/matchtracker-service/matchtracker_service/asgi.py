
import os
import django
from channels.routing import ProtocolTypeRouter, URLRouter
from django.core.asgi import get_asgi_application
from django.urls import re_path
from matchtracker_service.jwt_auth_ws_middleware import JWTAuthMiddleware
from game.internal_routing import websocket_urlpatterns as internal_ws_patterns
from game.frontend_routing import websocket_urlpatterns as frontend_ws_patterns

os.environ.setdefault("DJANGO_SETTINGS_MODULE", "matchtracker_service.settings")
django.setup()

application = ProtocolTypeRouter({
    "http": get_asgi_application(),
    "websocket": URLRouter([

        re_path(r'^ws/frontend/game/$', JWTAuthMiddleware(frontend_ws_patterns[0].callback)),

        re_path(r'^ws/game_sessions/$', internal_ws_patterns[0].callback),
    ]),
})
