from rest_framework import serializers
from .models import Profile
from django.contrib.auth.models import User

class ProfileSerializer(serializers.ModelSerializer): # Serializer pour les profils utilisateurs (public)

    class Meta: # définit des comportements spécifiques pour une table de DB (ici Profile)
        model = Profile
        fields = ['display_name', 'avatar', 'wins', 'losses']
        read_only_fields = ['wins', 'losses']

class UserSerializer(serializers.ModelSerializer): # Serializer pour les utilisateurs (privé)
    profile = ProfileSerializer()

    class Meta:
        model = User
        fields = ['id', 'username', 'email', 'profile', 'password']
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
        profile_data = validated_data.pop('profile', {})
        password = validated_data.pop('password')  # Extrait le mot de passe brut
        user = User.objects.create(**validated_data)  # Crée l'utilisateur sans mot de passe
        user.set_password(password)  # Hashage du mot de passe
        user.save()  # Sauvegarde dans la base de données
        # Profile.objects.update_or_create(user=user, defaults=profile_data)
        Profile.objects.create(user=user, **profile_data)
        return user

    def update(self, instance, validated_data):
        profile_data = validated_data.pop('profile', {})
        instance.email = validated_data.get('email', instance.email)
        instance.save()
        # Profile.objects.update_or_create(user=instance, defaults=profile_data)
        
        # Mise à jour ou création du profil associé
        profile = instance.profile
        for attr, value in profile_data.items():
            setattr(profile, attr, value)  # Mise à jour des attributs du profil
        profile.save()  # Sauvegarde dans la base de données

        return instance