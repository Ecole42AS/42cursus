from rest_framework import serializers
from .models import Profile
from django.contrib.auth.models import User
from django.db import IntegrityError
import logging

logger = logging.getLogger(__name__)


class ProfileSerializer(serializers.ModelSerializer):
    # Serializer pour les profils utilisateurs (public)
    avatar = serializers.ImageField(required=False)

    class Meta: # définit des comportements spécifiques pour une table de DB (ici Profile)
        model = Profile
        fields = ['display_name', 'avatar', 'wins', 'losses']
        read_only_fields = ['wins', 'losses']

class UserSerializer(serializers.ModelSerializer):
    # Serializer pour les utilisateurs (privé)
    profile = ProfileSerializer()

    class Meta:
        model = User
        fields = ['id', 'username', 'password', 'email', 'profile']
        extra_kwargs = {'password': {'write_only': True}}

    def validate(self, data):
        profile_data = data.get('profile', {})
        display_name = profile_data.get('display_name')
        if not display_name:
            raise serializers.ValidationError({'display_name': 'Ce champ est requis.'})
        if Profile.objects.filter(display_name=display_name).exists():
            raise serializers.ValidationError({'display_name': 'Ce nom d\'affichage est déjà utilisé.'})
        return data

    def create(self, validated_data):
        # Création d'un utilisateur avec un profil
        profile_data = validated_data.pop('profile', {})
        avatar = profile_data.pop('avatar', None)  # Avatar optionnel
        password = validated_data.pop('password')  # Extrait le mot de passe brut
        logger.info(f"Avatar received: {avatar}")

        user = User.objects.create(**validated_data)  # Crée l'utilisateur sans mot de passe
        user.set_password(password)  # Hashage du mot de passe
        user.save()  # Sauvegarde dans la base de données

        # try:
        #     # Création du profil
        #     profile = Profile.objects.create(user=user, **profile_data)
        # except IntegrityError as e:
        #     # Supprime l'utilisateur si la création du profil échoue
        #     user.delete()
        #     raise serializers.ValidationError({'profile': 'Impossible de créer le profil : {}'.format(str(e))})

        # profile = Profile.objects.create(user=user, **profile_data)
        profile, created = Profile.objects.update_or_create(
            user=user,
            defaults={**profile_data, 'avatar': avatar}
        )
        logger.info(f"Profile: {profile}")

        if avatar:
            profile.avatar = avatar
            profile.save()
            logger.info(f"Avatar updated for profile: {profile.avatar}")


        return user

    def update(self, instance, validated_data):
        # Extraction des données validées du profil
        profile_data = validated_data.pop('profile', {})
        avatar = profile_data.pop('avatar', None) # None si l'avatar n'est pas fourni
        email = validated_data.get('email')

        if email:
            if User.objects.filter(email=email).exclude(pk=instance.user.pk).exists():
                raise serializers.ValidationError({"email": "Cet email est déjà utilisé."})
            instance.user.email = email
            instance.user.save()

        # if email and User.objects.filter(email=email).exclude(pk=instance.pk).exists():
        #     raise serializers.ValidationError({"email": "Cet email est déjà utilisé."})
        # if email:
        #     instance.email = email
        #     instance.save()

        # Mise à jour du profil
        profile = instance.profile  # Récupération du profil lié à l'utilisateur
        for attr, value in profile_data.items():
            setattr(profile, attr, value)  # Mise à jour des champs du profil

        if avatar:  # Mise à jour séparée de l'avatar
            profile.avatar = avatar

        profile.save()  # Sauvegarde des modifications du profil


        return instance
