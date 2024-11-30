# Les signaux dans Django permettent d'exécuter du code en réponse à des 
# événements spécifiques, comme la sauvegarde ou la suppression d'un objet.
# Dans ce cas, nous utilisons les signaux pour créer un profil utilisateur lorsque le user est créé et cela automatiquement.
from django.db.models.signals import post_save
from django.dispatch import receiver # Permet de recevoir des signaux
from .models import Profile
from django.conf import settings

@receiver(post_save, sender=settings.AUTH_USER_MODEL)
def create_user_profile(sender, instance, created, **kwargs):
    if created:
        Profile.objects.get_or_create(user=instance, defaults={'display_name': instance.username})
        
@receiver(post_save, sender=settings.AUTH_USER_MODEL)
def save_user_profile(sender, instance, **kwargs):
    if hasattr(instance, 'profile'):
        instance.profile.save()
    else:
        Profile.objects.create(user=instance, display_name=instance.username)
