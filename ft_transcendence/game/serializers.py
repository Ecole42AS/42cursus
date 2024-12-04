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
    # Champ personnalisé pour afficher les display_names des joueurs
    players_display_names = serializers.SerializerMethodField()

    class Meta:
        model = Tournament
        fields = ['id', 'name', 'players', 'players_display_names', 'created_at']  # Inclure les champs nécessaires

    def get_players_display_names(self, obj):
        # Récupérer les display_names des joueurs dans le tournoi
        return [player.profile.display_name for player in obj.players.all()]

    def update(self, instance, validated_data):
        players = validated_data.pop('players', None)
        if players:
            instance.players.set(players)  # Remplace les joueurs existants
        instance.save()
        return instance
    
    # validation pour s'assurer que les joueurs que l'ont peut ajouté au tournoi sont des amis de l'utilisateur
    # def validate_players(self, players):
    #     user_friends = self.context['request'].user.friends.all()
    #     for player in players:
    #         if player not in user_friends:
    #             raise serializers.ValidationError(f"{player.profile.display_name} is not your friend.")
    #     return players

    def validate_players(self, players):
        user = self.context['request'].user
        friends_ids = Friendship.objects.filter(from_user=user).values_list('to_user_id', flat=True)
        for player in players:
            if player.id not in friends_ids:
                raise serializers.ValidationError(f"{player.username} is not your friend.")
        return players

    def validate(self, data):
        if 'players' in data and len(data['players']) < 2:
            raise serializers.ValidationError("You must select at least two friends to create a tournament.")
        return data

class TournamentMatchSerializer(serializers.ModelSerializer):
    class Meta:
        model = TournamentMatch
        fields = '__all__'