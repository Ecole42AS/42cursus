from django.db import models
from django.contrib.auth.models import User

def user_directory_path(instance, filename): # instance est une instance du modèle Profile
    # Le fichier sera uploadé vers MEDIA_ROOT/user_<id>/<filename>
    return f'user_{instance.user.id}/{filename}'

class Profile(models.Model):
    user = models.OneToOneField(User, on_delete=models.CASCADE) # Un profil est lié à un et un seul utilisateur, si un utilisateur est supprimé, le profil est supprimé
    display_name = models.CharField(max_length=50, unique=True)
    avatar = models.ImageField(upload_to=user_directory_path, default='default_avatar.png')
    wins = models.IntegerField(default=0)
    losses = models.IntegerField(default=0)

    def __str__(self):
        return self.display_name # Affiche le nom d'affichage du profil dans l'interface admin sous forme de chaîne de caractères
