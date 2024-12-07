from rest_framework import serializers
from .models import Profile, CustomUser

class ProfileSerializer(serializers.ModelSerializer):
    class Meta: # Meta est une classe interne à ProfileSerializer qui permet de définir des options supplémentaires
        model = Profile
        fields = ['display_name', 'avatar', 'wins', 'losses']
        read_only_fields = ['wins', 'losses']

    def update(self, instance, validated_data):
        display_name = validated_data.get('display_name', instance.display_name) # Récupère le nom d'affichage modifié ou le nom d'affichage actuel

        if Profile.objects.filter(display_name=display_name).exclude(pk=instance.pk).exists():
            raise serializers.ValidationError({'display_name': 'user with this display name already exists.'})

        for attr, value in validated_data.items():
            setattr(instance, attr, value)
        instance.save()
        return instance

class UserSerializer(serializers.ModelSerializer):
    display_name = serializers.CharField(write_only=True, required=True)
    avatar = serializers.ImageField(write_only=True, required=False)

    class Meta:
        model = CustomUser
        fields = ['id', 'username', 'password', 'email', 'display_name', 'avatar']
        extra_kwargs = {'password': {'write_only': True}} # Le mot de passe ne sera pas renvoyé dans la réponse

    def validate_display_name(self, value): # méthode appelée automatiquement lors de la validation des données (nomenclature validate_<champ>)
        if Profile.objects.filter(display_name=value).exists():
            raise serializers.ValidationError('user with this display name already exists.')
        return value

    def create(self, validated_data): #surcharge de la méthode create pour créer un utilisateur et son profil associé
        display_name = validated_data.pop('display_name')
        avatar = validated_data.pop('avatar', None)
        password = validated_data.pop('password')

        user = CustomUser.objects.create_user(password=password, **validated_data) #crate_user est une méthode de AbstractUser qui hash le mot de passe (prend la variable python pour la mettre dans la base de données)

        profile = user.profile
        profile.display_name = display_name
        if avatar:
            profile.avatar = avatar
        profile.save()

        return user

    def update(self, instance, validated_data):
        profile_data = validated_data.pop('profile', {})
        avatar = profile_data.pop('avatar', None)

        instance.username = validated_data.get('username', instance.username)
        instance.email = validated_data.get('email', instance.email)

        if 'password' in validated_data:
            instance.set_password(validated_data['password'])

        instance.save()

        # Mise à jour du profil utilisateur
        profile = instance.profile
        for attr, value in profile_data.items(): # profile_data est un dictionnaire contenant les données du profil (nomenclature <relation>_data, par défaut prend le nom du modèle en minuscule)
            setattr(profile, attr, value)
        if avatar:
            profile.avatar = avatar
        profile.save()

        return instance

# Serializer pour les utilisateurs publics (voir si besoin par le front-end)
class PublicUserSerializer(serializers.ModelSerializer):
    display_name = serializers.CharField(source='profile.display_name', read_only=True)
    avatar = serializers.ImageField(source='profile.avatar', read_only=True)

    class Meta:
        model = CustomUser
        fields = ['id', 'username', 'display_name', 'avatar']
