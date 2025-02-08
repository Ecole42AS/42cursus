
from django.urls import re_path
from .consumers import FrontendGameConsumer

websocket_urlpatterns = [

    re_path(r'^ws/frontend/game/$', FrontendGameConsumer.as_asgi()),
]
