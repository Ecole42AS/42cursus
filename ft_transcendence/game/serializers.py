from rest_framework import serializers
from .models import GameSession, Tournament, TournamentMatch
from user.models import Friendship
from django.contrib.auth import get_user_model
from django.db.models import Q

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
        ret = super().to_representation(instance) # VOIR CE QUE FAIT SUPER
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
    players = serializers.PrimaryKeyRelatedField(
        many=True,
        queryset=CustomUser.objects.none()  # Valeur par défaut vide
    )
    players_display_names = serializers.SerializerMethodField()
    all_players = serializers.SerializerMethodField()
    creator = serializers.HiddenField(default=serializers.CurrentUserDefault())

    class Meta:
        model = Tournament
        fields = ['id', 'name', 'creator', 'players', 'all_players', 'players_display_names', 'created_at']
        read_only_fields = ['id', 'created_at', 'all_players']

    # def __init__(self, *args, **kwargs):
    #     super().__init__(*args, **kwargs)
    #     request = self.context.get('request')
    #     if request and hasattr(request, 'user'):
    #         # Filtrer uniquement les amis de l'utilisateur connecté
    #         user = request.user
    #         friends_ids = Friendship.objects.filter(
    #             Q(from_user=user) | Q(to_user=user)
    #         ).values_list('to_user_id', 'from_user_id')

    #         # Obtenir la liste unique des amis
    #         friends_ids = set(id for ids in friends_ids for id in ids if id != user.id)

    #         # Appliquer le queryset filtré
    #         self.fields['players'].queryset = CustomUser.objects.filter(id__in=friends_ids)

    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)
        request = self.context.get('request')
        if request and hasattr(request, 'user'):
            user = request.user
            # Récupérer tous les amis
            friends_ids = Friendship.objects.filter(
                Q(from_user=user) | Q(to_user=user)
            ).values_list('to_user_id', 'from_user_id')

            friends_ids = set(id for ids in friends_ids for id in ids if id != user.id)
            self.fields['players'].queryset = CustomUser.objects.filter(id__in=friends_ids)

            # Ajoutez un print pour vérifier le queryset
            print("Queryset utilisé pour les joueurs :", self.fields['players'].queryset.query)


    def get_players_display_names(self, obj):
        return [player.profile.display_name for player in obj.players.all()]

    def get_all_players(self, obj):
        return [player.id for player in obj.players.all()]

    # def validate_players(self, players):
    #     user = self.context['request'].user
    #     friends_ids = Friendship.objects.filter(from_user=user).values_list('to_user_id', flat=True)
    #     invalid_players = [player for player in players if player.id not in friends_ids]
    #     if invalid_players:
    #         invalid_usernames = ', '.join([player.username for player in invalid_players])
    #         raise serializers.ValidationError(f"The following users are not your friends: {invalid_usernames}.")
    #     return players

    def validate_players(self, players):
        user = self.context['request'].user

        # Récupérer les IDs des amis
        friends_ids = Friendship.objects.filter(from_user=user).values_list('to_user_id', flat=True)

        # Print les IDs des amis
        print("IDs des amis de l'utilisateur connecté :", list(friends_ids))

        # Print les joueurs reçus
        print("Joueurs reçus :", [player.id for player in players])

        # Identifier les joueurs invalides
        invalid_players = [player for player in players if player.id not in friends_ids]
        
        # Print les joueurs invalides
        if invalid_players:
            print("Joueurs invalides :", [player.id for player in invalid_players])

        # Lever une exception si des joueurs ne sont pas amis
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