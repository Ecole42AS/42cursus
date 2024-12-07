from rest_framework import serializers
from .models import GameSession, Tournament, TournamentMatch
from user.models import Friendship
from django.contrib.auth import get_user_model

CustomUser = get_user_model()

class GameSerializer(serializers.ModelSerializer):
    player1 = serializers.HiddenField(default=serializers.CurrentUserDefault()) # Le joueur 1 est l'utilisateur connecté (hiddenfield pour ne pas être modifié)
    player2 = serializers.PrimaryKeyRelatedField(queryset=CustomUser.objects.all())
    winner = serializers.CharField(source='winner.username', read_only=True)
    is_active = serializers.BooleanField(required=False)

    class Meta:
        model = GameSession
        fields = ['id', 'player1', 'player2', 'score_player1', 'score_player2', 'winner', 'is_active', 'created_at', 'ended_at']

    def to_representation(self, instance): # Surcharge de la méthode to_representation pour afficher les noms des joueurs au lieu des ids
        ret = super().to_representation(instance)
        ret['player1'] = instance.player1.username
        ret['player2'] = instance.player2.username
        ret['score_player1'] = instance.score_player1
        ret['score_player2'] = instance.score_player2
        ret['is_active'] = instance.is_active
        if instance.winner:
            ret['winner'] = instance.winner.username
        else:
            ret['winner'] = None
        return ret

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
        # Ajouter le créateur aux joueurs
        tournament.players.add(creator, *players)
        return tournament
    
    def update(self, instance, validated_data):
        players = validated_data.pop('players', None)
        if players is not None:
            # Inclure le créateur dans les joueurs
            instance.players.set([instance.creator] + list(players))
        return super().update(instance, validated_data)



class TournamentMatchSerializer(serializers.ModelSerializer):
    class Meta:
        model = TournamentMatch
        fields = '__all__'