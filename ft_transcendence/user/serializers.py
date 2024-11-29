from rest_framework import serializers
from .models import Profile
from django.contrib.auth.models import User


class ProfileSerializer(serializers.ModelSerializer):
    # Sérialiseur pour les profils utilisateurs (public)
    avatar = serializers.ImageField(required=False)

    class Meta:
        model = Profile
        fields = ['display_name', 'avatar', 'wins', 'losses']
        read_only_fields = ['wins', 'losses']


class UserSerializer(serializers.ModelSerializer):
    # Sérialiseur pour les utilisateurs (privé)
    profile = ProfileSerializer()

    class Meta:
        model = User
        fields = ['id', 'username', 'password', 'email', 'profile']
        extra_kwargs = {'password': {'write_only': True}}

    def validate(self, data):
        profile_data = data.get('profile', {})
        display_name = profile_data.get('display_name')
        if not display_name:
            raise serializers.ValidationError({'profile': {'display_name': 'Ce champ est requis.'}})
        if Profile.objects.filter(display_name=display_name).exists():
            raise serializers.ValidationError({'profile': {'display_name': 'Ce nom d\'affichage est déjà utilisé.'}})
        return data

    def create(self, validated_data):
        # Création d'un utilisateur avec un profil
        profile_data = validated_data.pop('profile', {})
        avatar = profile_data.pop('avatar', None)  # Avatar optionnel
        password = validated_data.pop('password')  # Extrait le mot de passe brut

        # Création de l'utilisateur
        user = User.objects.create(**validated_data)
        user.set_password(password)
        user.save()

        # Création du profil utilisateur
        profile, created = Profile.objects.get_or_create(user=user, defaults=profile_data)
        if avatar:
            profile.avatar = avatar
            profile.save()

        return user

    def update(self, instance, validated_data):
        # Extraction des données validées du profil
        profile_data = validated_data.pop('profile', {})
        avatar = profile_data.pop('avatar', None)  # None si l'avatar n'est pas fourni
        email = validated_data.get('email')

        # Mise à jour des informations utilisateur
        instance.username = validated_data.get('username', instance.username)
        if email:
            if User.objects.filter(email=email).exclude(pk=instance.pk).exists():
                raise serializers.ValidationError({"email": "Cet email est déjà utilisé."})
            instance.email = email
        if 'password' in validated_data:
            instance.set_password(validated_data['password'])
        instance.save()

        # Mise à jour du profil utilisateur
        profile = instance.profile
        for attr, value in profile_data.items():
            setattr(profile, attr, value)
        if avatar:
            profile.avatar = avatar
        profile.save()

        return instance
