from rest_framework import serializers
from .models import Profile
from django.contrib.auth.models import User

class ProfileSerializer(serializers.ModelSerializer):
    # Serializer pour les profils utilisateurs (public)
    email = serializers.EmailField(source='user.email', required=True)
    avatar = serializers.ImageField(required=False)

    class Meta: # définit des comportements spécifiques pour une table de DB (ici Profile)
        model = Profile
        fields = ['display_name', 'email', 'avatar', 'wins', 'losses']
        read_only_fields = ['wins', 'losses']
   
    def validate_email(self, value): # self est une instance de la classe ProfileSerializer
        if User.objects.filter(email=value).exclude(id=self.instance.user.id).exists(): # vérifie si l'email est déjà utilisé par un autre utilisateur
            raise serializers.ValidationError("Cet email est déjà utilisé.")
        return value

class UserSerializer(serializers.ModelSerializer):
    # Serializer pour les utilisateurs (privé)
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
        # Création d'un utilisateur avec un profil
        profile_data = validated_data.pop('profile', {})
        password = validated_data.pop('password')  # Extrait le mot de passe brut
        user = User.objects.create(**validated_data)  # Crée l'utilisateur sans mot de passe
        user.set_password(password)  # Hashage du mot de passe
        user.save()  # Sauvegarde dans la base de données
        Profile.objects.get_or_create(user=user, defaults=profile_data)
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

        # # Mise à jour ou création du profil
        # profile, created = Profile.objects.update_or_create(
        #     user=instance,  # Critère de recherche
        #     defaults=profile_data  # Données à mettre à jour ou à utiliser pour la création
        # )

        # Mise à jour du profil
        profile = instance.profile  # Récupération du profil lié à l'utilisateur
        for attr, value in profile_data.items():
            setattr(profile, attr, value)  # Mise à jour des champs du profil

        if avatar:  # Mise à jour séparée de l'avatar
            profile.avatar = avatar

        profile.save()  # Sauvegarde des modifications du profil


        return instance
