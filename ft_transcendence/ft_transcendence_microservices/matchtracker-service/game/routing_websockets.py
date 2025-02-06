from django.urls import re_path
from .consumers import MatchtrackerConsumer

websocket_urlpatterns = [
    # La route accepte une chaîne alphanumérique comme room_name.
    re_path(r'^ws/matchtracker/(?P<room_name>\w+)/$', MatchtrackerConsumer.as_asgi()),
]
