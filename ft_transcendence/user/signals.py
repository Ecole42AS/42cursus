# Les signaux dans Django permettent d'exécuter du code en réponse à des 
# événements spécifiques, comme la sauvegarde ou la suppression d'un objet.
# Dans ce cas, nous utilisons les signaux pour créer un profil utilisateur lorsque le user est créé et cela automatiquement.
from django.db.models.signals import post_save
from django.dispatch import receiver # Permet de recevoir des signaux
from .models import Profile
from django.conf import settings
from django.db import transaction
import os
from django.db.models.signals import pre_save

@receiver(post_save, sender=settings.AUTH_USER_MODEL)
def create_user_profile(sender, instance, created, **kwargs): # created est un booléen qui indique si l'instance a été créée ou mise à jour
    if created:
        Profile.objects.get_or_create(user=instance, defaults={'display_name': instance.username})
        
@receiver(post_save, sender=settings.AUTH_USER_MODEL)
def save_user_profile(sender, instance, **kwargs):
    if hasattr(instance, 'profile'):
        instance.profile.save()
    else:
        Profile.objects.create(user=instance, display_name=instance.username) # la méthode save() est appelée pour sauvegarder le profil utilisateur

@receiver(pre_save, sender=Profile)
def delete_old_avatar_on_update(sender, instance, **kwargs):
    if not instance.pk: # Si l'instance n'a pas de clé primaire, c'est une création et non une mise à jour
        return

    try:
        old_avatar = Profile.objects.get(pk=instance.pk).avatar # Récupère l'avatar actuel depuis la base de données
    except Profile.DoesNotExist:
        return

    if old_avatar and old_avatar != instance.avatar:
        def delete_old_file():
            if os.path.isfile(old_avatar.path):  # Vérifie si le fichier existe avant de le supprimer
                os.remove(old_avatar.path)

        transaction.on_commit(delete_old_file) # Supprime le fichier uniquement après que les modifications de la base de données ont été validées (commit).