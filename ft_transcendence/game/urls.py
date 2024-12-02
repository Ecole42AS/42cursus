from django.urls import path, include
from rest_framework.routers import DefaultRouter # router DRF gères les URL avec les actions CRUD
from .views import GameViewSet

router = DefaultRouter()
router.register(r'games', GameViewSet, basename='game') 
# enregistrement de la vue GameViewSet sur l'URL /games 
# (r'games' signifie que toutes les routes commenceront par games)
# (basename='game' permet de donner un nom à la route (game-detail, game-list, game-create, game-update, game-delete))

urlpatterns = [
    path('', include(router.urls)),
]
