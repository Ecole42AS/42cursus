from django.urls import path, include
from rest_framework.routers import DefaultRouter
from .views import GameViewSet, TournamentViewSet, TournamentMatchViewSet, MatchHistoryView, CreateGameSessionView, UpdateGameScoreView

router = DefaultRouter()
router.register(r'games', GameViewSet, basename='game')
router.register(r'tournaments', TournamentViewSet, basename='tournament')
router.register(r'tournament-matches', TournamentMatchViewSet, basename='tournament-match')

urlpatterns = [
    path('', include(router.urls)),
    path('match-history/', MatchHistoryView.as_view(), name='match_history'),
    path('create-game/<int:user_id>/', CreateGameSessionView.as_view(), name='create_game'),
    path('update-game-score/<int:game_id>/', UpdateGameScoreView.as_view(), name='update_game_score'),
]
