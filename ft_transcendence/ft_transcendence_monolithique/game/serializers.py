from rest_framework import serializers
from .models import GameSession, Tournament, TournamentMatch
from user.models import Friendship
from django.contrib.auth import get_user_model
from utils import get_user_data

CustomUser = get_user_model()
























class GameSerializer(serializers.ModelSerializer):
    player1 = serializers.HiddenField(default=serializers.CurrentUserDefault())
    player2 = serializers.IntegerField()
    winner = serializers.IntegerField(read_only=True)
    is_active = serializers.BooleanField(required=False)

    class Meta:
        model = GameSession
        fields = ['id', 'player1', 'player2', 'score_player1', 'score_player2', 'winner', 'is_active', 'created_at', 'ended_at']

    def to_representation(self, instance):
        """
        Représentation des données avec des informations utilisateur récupérées dynamiquement.
        """
        data = super().to_representation(instance)

        
        token = self.context['request'].auth

        
        player1_data = get_user_data(instance.player1_id, token)
        player2_data = get_user_data(instance.player2_id, token)

        data['player1'] = player1_data['username'] if player1_data else "Unknown"
        data['player2'] = player2_data['username'] if player2_data else "Unknown"
        data['winner'] = (
            get_user_data(instance.winner_id, token)['username']
            if instance.winner_id else None
        )
        return data


class TournamentSerializer(serializers.ModelSerializer):
    players_display_names = serializers.SerializerMethodField()
    all_players = serializers.SerializerMethodField()
    creator = serializers.HiddenField(default=serializers.CurrentUserDefault())

    class Meta:
        model = Tournament
        fields = ['id', 'name', 'creator', 'players', 'all_players', 'players_display_names', 'created_at']
        read_only_fields = ['id', 'created_at', 'all_players']

    def get_players_display_names(self, obj):
        return [player.profile.display_name for player in obj.players.all()]

    def get_all_players(self, obj):
        return [player.id for player in obj.players.all()]

    def validate_players(self, players):
        user = self.context['request'].user
        friends_ids = Friendship.objects.filter(from_user=user).values_list('to_user_id', flat=True)
        invalid_players = [player for player in players if player.id not in friends_ids]
        if invalid_players:
            invalid_usernames = ', '.join([player.username for player in invalid_players])
            raise serializers.ValidationError(f"The following users are not your friends: {invalid_usernames}.")
        return players

    def validate(self, data):
        players = data.get('players', [])
        if len(players) < 2:
            raise serializers.ValidationError("You must select at least two friends to create a tournament.")
        return data

    def create(self, validated_data):
        players = validated_data.pop('players', [])
        creator = validated_data.pop('creator')

        tournament = Tournament.objects.create(creator=creator, **validated_data)
        tournament.players.add(creator, *players)
        return tournament
    
    def update(self, instance, validated_data):
        players = validated_data.pop('players', None)
        if players is not None:
            instance.players.set([instance.creator] + list(players))
        return super().update(instance, validated_data)



class TournamentMatchSerializer(serializers.ModelSerializer):
    class Meta:
        model = TournamentMatch
        fields = '__all__'