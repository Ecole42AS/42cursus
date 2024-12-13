from django.urls import path
from .views import RegisterView, UserProfileView, AddFriendView, FriendsListView, UserUpdateView, UserDetailView, FriendshipStatusView, SearchUserView


urlpatterns = [
    path('register/', RegisterView.as_view(), name='register'),
    path('profile/', UserProfileView.as_view(), name='profile'),
    path('update_user/', UserUpdateView.as_view(), name='update_user'),
    path('add_friend/<int:user_id>/', AddFriendView.as_view(), name='add_friend'),
    path('friends/', FriendsListView.as_view(), name='friends_list'),
    path('<int:user_id>/', UserDetailView.as_view(), name='user_detail'),
    path('friendship-status/<int:user1_id>/<int:user2_id>/', FriendshipStatusView.as_view(), name='friendship_status'),
    path('search/', SearchUserView.as_view(), name='search_user'),
]
