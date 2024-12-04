from rest_framework import serializers
from .models import GameSession, Tournament, TournamentMatch
from user.models import Friendship

class GameSerializer(serializers.ModelSerializer):
    player1 = serializers.CharField(source='player1.username', read_only=True)
    player2 = serializers.CharField(source='player2.username', read_only=True)
    winner = serializers.CharField(source='winner.username', read_only=True)

    class Meta: # classe Meta pour définir les champs à sérialiser
        model = GameSession
        fields = ['id', 'player1', 'player2', 'score_player1', 'score_player2', 'winner', 'created_at', 'ended_at']

class TournamentSerializer(serializers.ModelSerializer):
    players_display_names = serializers.SerializerMethodField()
    creator = serializers.HiddenField(default=serializers.CurrentUserDefault())

    class Meta:
        model = Tournament
        fields = ['id', 'name', 'creator', 'players', 'players_display_names', 'created_at']
        read_only_fields = ['id', 'created_at']

    def get_players_display_names(self, obj):
        return [player.profile.display_name for player in obj.players.all()]

    def validate_players(self, players):
        user = self.context['request'].user
        friends_ids = Friendship.objects.filter(from_user=user).values_list('to_user_id', flat=True)
        for player in players:
            if player.id not in friends_ids:
                raise serializers.ValidationError(f"{player.username} is not your friend.")
        return players

    def create(self, validated_data):
        players = validated_data.pop('players', [])
        creator = validated_data.pop('creator')

        # Vérifier que les joueurs sont des amis (déjà fait dans validate_players)
        # total_players inclut le créateur
        total_players = len(players) + 1
        if total_players < 2:
            raise serializers.ValidationError("A tournament must have at least two players.")

        tournament = Tournament.objects.create(creator=creator, **validated_data)
        tournament.players.add(creator, *players)
        return tournament

class TournamentMatchSerializer(serializers.ModelSerializer):
    class Meta:
        model = TournamentMatch
        fields = '__all__'