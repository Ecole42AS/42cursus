from rest_framework import serializers
from .models import GameSession, Tournament, TournamentMatch
from django.contrib.auth import get_user_model
from .utils import get_friendship

CustomUser = get_user_model()

class FriendshipSerializer(serializers.Serializer):
    """
    Sérialiseur pour formater les données d'amitié récupérées depuis user-service.
    """
    user = serializers.IntegerField()
    friend = serializers.IntegerField()
    created_at = serializers.DateTimeField()



class GameSerializer(serializers.ModelSerializer):
    player1 = serializers.HiddenField(default=serializers.CurrentUserDefault())
    player2 = serializers.PrimaryKeyRelatedField(queryset=CustomUser.objects.all())
    winner = serializers.CharField(source='winner.username', read_only=True)
    is_active = serializers.BooleanField(required=False)

    class Meta:
        model = GameSession
        fields = ['id', 'player1', 'player2', 'score_player1', 'score_player2', 'winner', 'is_active', 'created_at', 'ended_at']

    def to_representation(self, instance):
        data = super().to_representation(instance)
        data['player1'] = instance.player1.username
        data['player2'] = instance.player2.username
        data['score_player1'] = instance.score_player1
        data['score_player2'] = instance.score_player2
        data['is_active'] = instance.is_active
        if instance.winner:
            data['winner'] = instance.winner.username
        else:
            data['winner'] = None
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
        """
        Valide que tous les joueurs sont des amis de l'utilisateur actuel.
        """
        user = self.context['request'].user
        friends_data = get_friendship(user.id)  # Appel à l'API du microservice user
        if not friends_data:
            raise serializers.ValidationError("Impossible de valider les amis. Service indisponible.")

        friends_ids = {friend['friend'] for friend in friends_data}
        invalid_players = [player for player in players if player.id not in friends_ids]

        if invalid_players:
            invalid_usernames = ', '.join([player.username for player in invalid_players])
            raise serializers.ValidationError(f"Les utilisateurs suivants ne sont pas vos amis : {invalid_usernames}.")
        return players

    def validate(self, data):
        players = data.get('players', [])
        if len(players) < 2:
            raise serializers.ValidationError("Vous devez sélectionner au moins deux amis pour créer un tournoi.")
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