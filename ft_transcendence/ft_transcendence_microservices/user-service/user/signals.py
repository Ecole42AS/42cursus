from django.db.models.signals import post_save
from django.dispatch import receiver
from .models import Profile
from django.conf import settings
from django.db import transaction
import os
from django.db.models.signals import pre_save

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

@receiver(pre_save, sender=Profile)
def delete_old_avatar_on_update(sender, instance, **kwargs):
    if not instance.pk:
        return

    try:
        old_avatar = Profile.objects.get(pk=instance.pk).avatar
    except Profile.DoesNotExist:
        return

    if old_avatar and old_avatar != instance.avatar:
        def delete_old_file():
            if os.path.isfile(old_avatar.path): 
                os.remove(old_avatar.path)

        transaction.on_commit(delete_old_file)