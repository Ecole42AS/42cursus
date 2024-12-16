from rest_framework import serializers
from .models import GameSession, Tournament, TournamentMatch
from .utils import get_friendship, get_user_data, get_user_profile

class FriendshipSerializer(serializers.Serializer):
    """
    Sérialiseur pour formater les données d'amitié récupérées depuis user-service.
    """
    user = serializers.IntegerField()
    friend = serializers.IntegerField()
    created_at = serializers.DateTimeField()



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

        # Récupérez les données des utilisateurs via le microservice
        player1_data = get_user_data(instance.player1_id)
        player2_data = get_user_data(instance.player2_id)

        data['player1'] = player1_data['username'] if player1_data else "Unknown"
        data['player2'] = player2_data['username'] if player2_data else "Unknown"
        data['winner'] = (
            get_user_data(instance.winner_id)['username']
            if instance.winner_id else None
        )
        return data

class TournamentSerializer(serializers.ModelSerializer):
    players_display_names = serializers.SerializerMethodField()
    all_players = serializers.ListField(
        child=serializers.IntegerField(), write_only=True
    )
    creator = serializers.HiddenField(default=serializers.CurrentUserDefault())

    class Meta:
        model = Tournament
        fields = [
            'id', 'name', 'creator', 'players', 'all_players',
            'players_display_names', 'created_at'
        ]
        read_only_fields = ['id', 'created_at', 'players_display_names']

    def get_players_display_names(self, obj):
        """
        Récupère les noms des joueurs via le microservice utilisateur.
        """
        return [
            get_user_profile(player_id)['display_name']
            for player_id in obj.players
        ]

    def validate_all_players(self, players):
        """
        Valide que tous les joueurs sont des amis de l'utilisateur actuel.
        """
        user = self.context['request'].user
        friends_data = get_friendship(user.id)  # Appel à l'API du microservice utilisateur

        if not friends_data:
            raise serializers.ValidationError("Impossible de valider les amis. Service indisponible.")

        friends_ids = {friend['friend'] for friend in friends_data}
        invalid_players = [player for player in players if player not in friends_ids]

        if invalid_players:
            raise serializers.ValidationError(
                f"Les utilisateurs suivants ne sont pas vos amis : {', '.join(map(str, invalid_players))}."
            )
        return players

    def validate(self, data):
        players = data.get('all_players', [])
        if len(players) < 2:
            raise serializers.ValidationError("Vous devez sélectionner au moins deux amis pour créer un tournoi.")
        return data

    def create(self, validated_data):
        players = validated_data.pop('all_players', [])
        creator = validated_data.pop('creator')

        # Créez le tournoi
        tournament = Tournament.objects.create(creator=creator, **validated_data)
        tournament.players = players
        return tournament

    def update(self, instance, validated_data):
        players = validated_data.pop('all_players', None)
        if players is not None:
            instance.players = players
        return super().update(instance, validated_data)



class TournamentMatchSerializer(serializers.ModelSerializer):
    class Meta:
        model = TournamentMatch
        fields = '__all__'