from django.urls import path
from .views import RegisterView, UserProfileView, AddFriendView, FriendsListView, UserUpdateView, test_redis_session,\
UserDetailView, FriendshipStatusView, SearchUserView, UserProfileDetailView,\
InternalUpdateStatsView, ValidateTokenView, FriendshipsView

urlpatterns = [
    path('register/', RegisterView.as_view(), name='register'),
    path('profile/', UserProfileView.as_view(), name='profile'),
    path('profile/<int:user_id>/', UserProfileDetailView.as_view(), name='profile_detail'),
    path('internal/update-stats/', InternalUpdateStatsView.as_view(), name='internal_update_stats'),
    path('update_user/', UserUpdateView.as_view(), name='update_user'),
    path('<int:user_id>/', UserDetailView.as_view(), name='user_detail'),
    path('friends/', FriendsListView.as_view(), name='friends_list'),
    path('friendships/<int:user_id>/', FriendshipsView.as_view(), name='friendships'),
    path('add_friend/<int:user_id>/', AddFriendView.as_view(), name='add_friend'),
    path('friendship-status/<int:user1_id>/<int:user2_id>/', FriendshipStatusView.as_view(), name='friendship_status'),
    path('search/', SearchUserView.as_view(), name='search_user'),
    path('validate/', ValidateTokenView.as_view(), name='validate_user'),
    path('test-redis-session/', test_redis_session, name='test_redis_session'),
]
