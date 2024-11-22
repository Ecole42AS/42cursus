from rest_framework import serializers
from django.contrib.auth.models import User

class UserSerializer(serializers.ModelSerializer):
    password = serializers.CharField(write_only=True) # champ non exposé via l'API

    class Meta: # définit des comportements spécifiques pour une table de DB (ici User)
        model = User
        fields = ['id', 'username', 'email', 'password'] # champs exposés via l'API (MDP défini comme write_only)

    def create(self, validated_data):
        user = User.objects.create_user( #gère le hashage du mot de passe et la validation des données
            username=validated_data['username'],
            email=validated_data.get('email', ''),
            password=validated_data['password']
        )
        return user

class UserProfileSerializer(serializers.ModelSerializer): # Serializer pour les profils utilisateurs (public)
    class Meta:
        model = User
        fields = ['id', 'username', 'email']