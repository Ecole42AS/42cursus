from django.urls import path # Django.urls est une collection de fonctions permettant de gérer les URL (dossier créer lors de l'installation de Django)
from .views import RegisterView, UserProfileView, AddFriendView, FriendsListView, UserUpdateView


urlpatterns = [ # contient la liste des URL associées aux vues
    path('register/', RegisterView.as_view(), name='register'), # exemple d'utilisation du name -> <a href="{% url 'register' %}">Inscription</a>
    path('profile/', UserProfileView.as_view(), name='profile'),
    path('update_user/', UserUpdateView.as_view(), name='update_user'),
    path('add_friend/<int:user_id>/', AddFriendView.as_view(), name='add_friend'),
    path('friends/', FriendsListView.as_view(), name='friends_list'),
]
