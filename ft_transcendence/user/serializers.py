from rest_framework import serializers
from .models import Profile
from django.contrib.auth.models import User


class ProfileSerializer(serializers.ModelSerializer):
    class Meta:
        model = Profile
        fields = ['display_name', 'avatar', 'wins', 'losses']
        read_only_fields = ['wins', 'losses']

    def update(self, instance, validated_data):
        display_name = validated_data.get('display_name', instance.display_name)

        # Validation de l'unicité du nom d'affichage
        if Profile.objects.filter(display_name=display_name).exclude(pk=instance.pk).exists():
            raise serializers.ValidationError({'display_name': 'Ce nom d\'affichage est déjà utilisé.'})

        for attr, value in validated_data.items():
            setattr(instance, attr, value)
        instance.save()
        return instance


class UserSerializer(serializers.ModelSerializer):
    display_name = serializers.CharField(write_only=True, required=True)
    avatar = serializers.ImageField(write_only=True, required=False)

    class Meta:
        model = User
        fields = ['id', 'username', 'password', 'email', 'display_name', 'avatar']
        extra_kwargs = {'password': {'write_only': True}}

    def create(self, validated_data):
        display_name = validated_data.pop('display_name')
        avatar = validated_data.pop('avatar', None)
        password = validated_data.pop('password')

        # Création de l'utilisateur
        user = User.objects.create_user(password=password, **validated_data)

        # Mettre à jour le profil créé automatiquement par le signal
        profile = user.profile
        profile.display_name = display_name
        if avatar:
            profile.avatar = avatar
        profile.save()

        return user

    def update(self, instance, validated_data):
        profile_data = validated_data.pop('profile', {})
        avatar = profile_data.pop('avatar', None)  # None si l'avatar est absent

        instance.username = validated_data.get('username', instance.username)
        email = validated_data.get('email', instance.email)

        if email and User.objects.filter(email=email).exclude(pk=instance.pk).exists():
            raise serializers.ValidationError({"email": "Cet email est déjà utilisé."})

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
    
    def validate_display_name(self, value):
        if Profile.objects.filter(display_name=value).exists():
            raise serializers.ValidationError('Ce nom d\'affichage est déjà utilisé.')
        return value

