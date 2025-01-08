from django.urls import path, include
from rest_framework.routers import DefaultRouter
from game.views import GameViewSet, TournamentViewSet, TournamentMatchViewSet, MatchHistoryView,\
    CreateGameSessionView, UpdateGameScoreView, test_redis_session
from game.views import log_test_view  # Ajoutez cette ligne
from game.views import TestUserView  # Ajoutez cette ligne
from game.views import TestGamesView  # Ajoutez cette ligne
from game.views import TestGamesQueryView  # Ajoutez cette ligne
from game.views import TestGamesNoPermissionsView  # Ajoutez cette ligne

router = DefaultRouter()
router.register(r'games', GameViewSet, basename='game')
router.register(r'tournaments', TournamentViewSet, basename='tournament')
router.register(r'tournament-matches', TournamentMatchViewSet, basename='tournament-match')

urlpatterns = [
    path('', include(router.urls)),
    path('match-history/', MatchHistoryView.as_view(), name='match_history'),
    path('create-game/<int:user_id>/', CreateGameSessionView.as_view(), name='create_game'),
    path('update-game-score/<int:game_id>/', UpdateGameScoreView.as_view(), name='update_game_score'),
    path('test-redis-session/', test_redis_session, name='test_redis_session'),
    path('log-test/', log_test_view, name='log_test'),  # Ajoutez cette route
    path('test-user/', TestUserView.as_view(), name='test-user'),
    path('test-games/', TestGamesView.as_view(), name='test-games'),
    path('test-games-query/', TestGamesQueryView.as_view(), name='test-games-query'),
    path('test-games-no-permissions/', TestGamesNoPermissionsView.as_view(), name='test-games-no-permissions'),


]
