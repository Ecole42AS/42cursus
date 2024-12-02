from rest_framework import serializers
from .models import GameSession, Tournament, TournamentMatch

class GameSerializer(serializers.ModelSerializer):
    class Meta: # classe Meta pour définir les champs à sérialiser
        model = GameSession
        fields = '__all__'

class TournamentSerializer(serializers.ModelSerializer):
    class Meta:
        model = Tournament
        fields = '__all__'

class TournamentMatchSerializer(serializers.ModelSerializer):
    class Meta:
        model = TournamentMatch
        fields = '__all__'