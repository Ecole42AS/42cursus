from rest_framework import serializers
from .models import GameSession, Tournament, TournamentMatch
from .utils import get_friendship, get_user_data, get_user_profile
import logging

logger = logging.getLogger(__name__)

class FriendshipSerializer(serializers.Serializer):
    """
    Sérialiseur pour formater les données d'amitié récupérées depuis user-service.
    """
    user = serializers.IntegerField()
    friend = serializers.IntegerField()
    created_at = serializers.DateTimeField()



class GameSerializer(serializers.ModelSerializer):
    player1 = serializers.SerializerMethodField()
    player2 = serializers.SerializerMethodField()
    winner = serializers.SerializerMethodField()

    class Meta:
        model = GameSession
        fields = ['id', 'player1', 'player2', 'score_player1', 'score_player2', 'winner', 'is_active', 'created_at', 'ended_at']

    def fetch_user_data(self, user_id, token):
        try:
            if not token:
                logger.warning(f"No token provided for fetching user_id {user_id}")
                return 'Unknown'

            logger.debug(f"Fetching user data for user_id {user_id} with token {token}")
            user_data = get_user_data(user_id, token)
            if user_data:
                logger.info(f"User data retrieved for user_id {user_id}: {user_data}")
                return user_data.get('username', 'Unknown')
            logger.warning(f"No data found for user_id {user_id}")
            return 'Unknown'
        except Exception as e:
            logger.error(f"Error fetching user data for user_id {user_id}: {e}")
            return 'Unknown'


    def get_player1(self, obj):
        token = self.context['request'].auth if self.context.get('request') else None
        return self.fetch_user_data(obj.player1_id, token)

    def get_player2(self, obj):
        token = self.context['request'].auth if self.context.get('request') else None
        return self.fetch_user_data(obj.player2_id, token)

    def get_winner(self, obj):
        token = self.context['request'].auth if self.context.get('request') else None
        return self.fetch_user_data(obj.winner_id, token) if obj.winner_id else None

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