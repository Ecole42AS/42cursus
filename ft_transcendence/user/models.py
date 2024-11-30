from django.db import models
from django.contrib.auth.models import AbstractUser
from django.utils import timezone
from datetime import timedelta
from django.conf import settings


def user_directory_path(instance, filename): # instance est une instance du modèle Profile
    # Le fichier sera uploadé vers MEDIA_ROOT/user_<id>/<filename>
    return f'user_{instance.user.id}/{filename}'

class Profile(models.Model):
    user = models.OneToOneField(settings.AUTH_USER_MODEL, on_delete=models.CASCADE) # Un profil est lié à un et un seul utilisateur, si un utilisateur est supprimé, le profil est supprimé
    display_name = models.CharField(max_length=50, unique=True)
    avatar = models.ImageField(upload_to=user_directory_path, default='default_avatar.png')
    wins = models.IntegerField(default=0)
    losses = models.IntegerField(default=0)
    last_activity = models.DateTimeField(null=True, blank=True)

    def is_online(self):
        if self.last_activity:
            now = timezone.now()
            return now - self.last_activity < timedelta(minutes=5)
        return False

    def __str__(self):
        return self.display_name # Affiche le nom d'affichage du profil dans l'interface admin sous forme de chaîne de caractères

class Friendship(models.Model):
    from_user = models.ForeignKey(settings.AUTH_USER_MODEL, related_name='friendships', on_delete=models.CASCADE) # related_name permet de renommer la relation dans l'autre sens
    to_user = models.ForeignKey(settings.AUTH_USER_MODEL, related_name='followers', on_delete=models.CASCADE)
    created_at = models.DateTimeField(auto_now_add=True)

    class Meta:
        unique_together = ('from_user', 'to_user')

class CustomUser(AbstractUser):
    email = models.EmailField(unique=True)
    username = models.CharField(max_length=150, unique=True)

    def __str__(self):
        return self.username