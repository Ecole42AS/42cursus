# Les signaux dans Django permettent d'exécuter du code en réponse à des 
# événements spécifiques, comme la sauvegarde ou la suppression d'un objet.
# Dans ce cas, nous utilisons les signaux pour créer un profil utilisateur lorsque le user est créé et cela automatiquement.
from django.db.models.signals import post_save
from django.contrib.auth.models import User
from django.dispatch import receiver # Permet de recevoir des signaux
from .models import Profile

@receiver(post_save, sender=User) # Lorsqu'un objet User est sauvegardé, le signal post_save est envoyé et reçu par la fonction create_user_profile
def create_user_profile(sender, instance, created, **kwargs): #created est un booléen qui indique si un objet a été créé (True) ou modifié (False)
    if created:
        Profile.objects.create(user=instance, display_name=instance.username) # Crée un profil lié à l'utilisateur

@receiver(post_save, sender=User)
def save_user_profile(sender, instance, **kwargs):
    if not hasattr(instance, 'profile'):
        Profile.objects.create(user=instance, display_name=instance.username)
    else:
        instance.profile.save()
