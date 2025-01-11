from rest_framework import serializers
from .models import GameSession, Tournament, TournamentMatch
from .utils import get_friendship, get_user_data, get_user_profile, generate_elimination_matches
import logging

logger = logging.getLogger("matchtracker-service")

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

    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self._user_cache = {}

    def fetch_user_data(self, user_id, token):
        if user_id in self._user_cache:
            return self._user_cache[user_id]

        try:
            if not token:
                logger.warning(f"No token provided for fetching user_id {user_id}")
                self._user_cache[user_id] = 'Unknown'
                return 'Unknown'

            logger.debug(f"Fetching user data for user_id {user_id} with token {token}, endpoint={self.context.get('request').path}")
            user_data = get_user_data(user_id, token)
            if user_data:
                username = user_data.get('username', 'Unknown')
                self._user_cache[user_id] = username
                return username
            logger.warning(f"No data found for user_id {user_id}")
            self._user_cache[user_id] = 'Unknown'
            return 'Unknown'
        except Exception as e:
            logger.error(f"Error fetching user data for user_id {user_id}: {e}")
            self._user_cache[user_id] = 'Unknown'
            return 'Unknown'

    def get_player1(self, obj):
        if not obj.player1_id:
            return None
        token = self.context['request'].auth if self.context.get('request') else None
        return self.fetch_user_data(obj.player1_id, token)

    def get_player2(self, obj):
        if not obj.player2_id:
            return None
        token = self.context['request'].auth if self.context.get('request') else None
        return self.fetch_user_data(obj.player2_id, token)

    def get_winner(self, obj):
        if not obj.winner_id:
            return None
        token = self.context['request'].auth if self.context.get('request') else None
        return self.fetch_user_data(obj.winner_id, token) if obj.winner_id else None


# class TournamentSerializer(serializers.ModelSerializer):
#     players_display_names = serializers.SerializerMethodField()
#     all_players = serializers.ListField(
#         child=serializers.IntegerField(), write_only=True
#     )
#     creator_id = serializers.HiddenField(default=serializers.CurrentUserDefault())

#     class Meta:
#         model = Tournament
#         fields = [
#             'id', 'name', 'creator_id', 'players', 'all_players',
#             'players_display_names', 'created_at'
#         ]
#         read_only_fields = ['id', 'created_at', 'players_display_names']

#     def get_players_display_names(self, obj):
#         """
#         Récupère les noms des joueurs via le microservice utilisateur.
#         """
#         token = self.context['request'].auth
#         display_names = []
#         for player_id in obj.players:
#             try:
#                 user_profile = get_user_profile(player_id, token)
#                 display_names.append(user_profile.get('display_name', 'Unknown'))
#             except Exception as e:
#                 logger.warning(f"Erreur lors de la récupération du profil utilisateur pour ID {player_id}: {e}")
#                 display_names.append('Unknown')
#         return display_names

#     def validate_all_players(self, players):
#         user = self.context['request'].user
#         token = self.context['request'].auth

#         try:
#             # Journalisation du début de la validation
#             logger.debug(f"Validation des joueurs pour user_id={user.id} avec token={token}")

#             # Appel au microservice pour récupérer les amis
#             friends_data = get_friendship(user.id, token)
#             logger.debug(f"Amis récupérés pour user_id={user.id} : {friends_data}")

#             # Vérifiez si les données des amis sont valides
#             if not friends_data:
#                 raise serializers.ValidationError("Impossible de valider les amis. Service indisponible.")

#             if not isinstance(friends_data, list) or not all('id' in friend for friend in friends_data):
#                 logger.error(f"Structure inattendue des données des amis : {friends_data}")
#                 raise serializers.ValidationError("Données des amis invalides ou format inattendu.")

#             # Extraire les IDs des amis
#             friends_ids = {friend['id'] for friend in friends_data}
#             logger.debug(f"IDs des amis valides : {friends_ids}")

#             # Exclure l'utilisateur connecté de la validation
#             invalid_players = [player for player in players if player != user.id and player not in friends_ids]
#             logger.debug(f"Joueurs invalides détectés : {invalid_players}")

#             if invalid_players:
#                 raise serializers.ValidationError(
#                     f"Les utilisateurs suivants ne sont pas vos amis : {', '.join(map(str, invalid_players))}."
#                 )
            
#             return players

#         except serializers.ValidationError as ve:
#             # Journaliser et renvoyer les erreurs de validation
#             logger.error(f"Erreur de validation des amis : {ve}")
#             raise ve

#         except Exception as e:
#             # Capturer toute autre exception et la journaliser
#             logger.error(f"Erreur inattendue lors de la validation des amis : {e}")
#             raise serializers.ValidationError(f"Erreur lors de la validation des amis : {e}")


#     def validate(self, data):
#         """
#         Validation globale des données.
#         """
#         players = data.get('all_players', [])
#         if len(players) < 2:
#             raise serializers.ValidationError("Vous devez sélectionner au moins deux amis pour créer un tournoi.")
#         return data

#     def create(self, validated_data):
#         """
#         Crée un tournoi avec les données validées.
#         """
#         players = validated_data.pop('all_players', [])
#         user = self.context['request'].user

#         # Créez le tournoi
#         tournament = Tournament.objects.create(creator_id=user.id, **validated_data)
#         tournament.players = players  # Ajoutez les joueurs au tournoi
#         tournament.save()

#         return tournament


#     def update(self, instance, validated_data):
#         """
#         Met à jour un tournoi existant.
#         """
#         players = validated_data.pop('all_players', None)
#         if players is not None:
#             instance.players = players
#         return super().update(instance, validated_data)


class TournamentSerializer(serializers.ModelSerializer):
    players_display_names = serializers.SerializerMethodField()
    all_players = serializers.ListField(
        child=serializers.IntegerField(), write_only=True
    )

    class Meta:
        model = Tournament
        fields = [
            'id', 'name', 'creator_id', 'players', 'all_players',
            'players_display_names', 'created_at'
        ]
        read_only_fields = ['id', 'created_at', 'players_display_names', 'creator_id']

    def get_players_display_names(self, obj):
        """
        Récupère les noms des joueurs via le microservice utilisateur.
        """
        token = self.context['request'].auth
        display_names = []
        for player_id in obj.players:
            try:
                user_profile = get_user_profile(player_id, token)
                display_names.append(user_profile.get('display_name', 'Unknown'))
            except Exception as e:
                logger.warning(f"Erreur lors de la récupération du profil utilisateur pour ID {player_id}: {e}")
                display_names.append('Unknown')
        return display_names

class TournamentSerializer(serializers.ModelSerializer):
    players_display_names = serializers.SerializerMethodField()
    all_players = serializers.ListField(
        child=serializers.IntegerField(), write_only=True
    )

    class Meta:
        model = Tournament
        fields = [
            'id', 'name', 'creator_id', 'players', 'all_players',
            'players_display_names',  'created_at'
        ]
        read_only_fields = ['id', 'created_at', 'players_display_names', 'creator_id']

    def get_players_display_names(self, obj):
        """
        Récupère les noms des joueurs via le microservice utilisateur.
        """
        token = self.context['request'].auth
        display_names = []
        for player_id in obj.players:
            try:
                user_profile = get_user_profile(player_id, token)
                display_names.append(user_profile.get('display_name', 'Unknown'))
            except Exception as e:
                logger.warning(f"Erreur lors de la récupération du profil utilisateur pour ID {player_id}: {e}")
                display_names.append('Unknown')
        return display_names

    def validate_all_players(self, players):
        """
        Valide que les joueurs sont tous des amis valides et inclut l'utilisateur connecté automatiquement.
        """
        user = self.context['request'].user
        token = self.context['request'].auth

        try:
            logger.debug(f"Validation des joueurs pour user_id={user.id} avec token={token}")
            friends_data = get_friendship(user.id, token)
            logger.debug(f"Amis récupérés pour user_id={user.id} : {friends_data}")

            if not friends_data:
                raise serializers.ValidationError("Impossible de valider les amis. Service indisponible.")

            if not isinstance(friends_data, list) or not all('id' in friend for friend in friends_data):
                logger.error(f"Structure inattendue des données des amis : {friends_data}")
                raise serializers.ValidationError("Données des amis invalides ou format inattendu.")

            friends_ids = {friend['id'] for friend in friends_data}
            logger.debug(f"IDs des amis valides : {friends_ids}")

            invalid_players = [player for player in players if player != user.id and player not in friends_ids]
            logger.debug(f"Joueurs invalides détectés : {invalid_players}")

            if invalid_players:
                raise serializers.ValidationError(
                    f"Les utilisateurs suivants ne sont pas vos amis : {', '.join(map(str, invalid_players))}."
                )

            # Ajouter automatiquement l'utilisateur connecté s'il n'est pas déjà dans la liste
            if user.id not in players:
                players.append(user.id)

            return players

        except Exception as e:
            logger.error(f"Erreur inattendue lors de la validation des amis : {e}")
            raise serializers.ValidationError(f"Erreur lors de la validation des amis : {e}")

    def validate(self, data):
        """
        Validation globale des données.
        """
        players = data.get('all_players', [])
        user = self.context['request'].user

        if user.id not in players:
            players.append(user.id)

        if len(players) % 2 != 0:
            raise serializers.ValidationError("Le nombre de joueurs doit être pair pour créer un tournoi, sachant que vous êtes inclus.")

        if len(players) < 4:
            raise serializers.ValidationError("Un tournoi nécessite au moins 4 joueurs, vous inclus.")
        return data

    def create(self, validated_data):
        """
        Crée un tournoi avec les données validées.
        """
        players = validated_data.pop('all_players', [])
        user = self.context['request'].user

        # Ajouter l'utilisateur connecté à la liste des joueurs s'il n'est pas déjà inclus
        if user.id not in players:
            players.append(user.id)

        players = list(set(players))


        # Créez le tournoi
        try:
        # Créez le tournoi
            tournament = Tournament.objects.create(
                creator_id=user.id,
                name=validated_data['name'],
                players=players
            )
            logger.info(f"Tournoi '{tournament.name}' créé avec succès par l'utilisateur ID {user.id}")

            # Générer les matchs pour le tournoi
            try:
                generate_elimination_matches(tournament)
                logger.info(f"Les matchs pour le tournoi '{tournament.name}' ont été générés avec succès.")
            except ValueError as e:
                logger.error(f"Erreur lors de la génération des matchs : {e}")
                raise serializers.ValidationError(f"Erreur lors de la génération des matchs : {e}")

            return tournament

        except Exception as e:
            logger.error(f"Erreur lors de la création du tournoi : {e}")
            raise serializers.ValidationError(f"Erreur inattendue lors de la création du tournoi : {e}")


    def update(self, instance, validated_data):
        """
        Met à jour un tournoi existant.
        """
        players = validated_data.pop('all_players', None)
        if players is not None:
            instance.players = list(set(players))
        return super().update(instance, validated_data)


# class TournamentSerializer(serializers.ModelSerializer):
#     players_display_names = serializers.SerializerMethodField()
#     all_players = serializers.ListField(
#         child=serializers.IntegerField(), write_only=True
#     )
#     creator = serializers.HiddenField(default=serializers.CurrentUserDefault())

#     class Meta:
#         model = Tournament
#         fields = [
#             'id', 'name', 'creator', 'players', 'all_players',
#             'players_display_names', 'created_at'
#         ]
#         read_only_fields = ['id', 'created_at', 'players_display_names']

#     def get_players_display_names(self, obj):
#         """
#         Récupère les noms des joueurs via le microservice utilisateur.
#         """
#         return [
#             get_user_profile(player_id)['display_name']
#             for player_id in obj.players
#         ]

#     def validate_all_players(self, players):
#         """
#         Valide que tous les joueurs sont des amis de l'utilisateur actuel.
#         """
#         user = self.context['request'].user
#         friends_data = get_friendship(user.id)  # Appel à l'API du microservice utilisateur

#         if not friends_data:
#             raise serializers.ValidationError("Impossible de valider les amis. Service indisponible.")

#         friends_ids = {friend['friend'] for friend in friends_data}
#         invalid_players = [player for player in players if player not in friends_ids]

#         if invalid_players:
#             raise serializers.ValidationError(
#                 f"Les utilisateurs suivants ne sont pas vos amis : {', '.join(map(str, invalid_players))}."
#             )
#         return players

#     def validate(self, data):
#         players = data.get('all_players', [])
#         if len(players) < 2:
#             raise serializers.ValidationError("Vous devez sélectionner au moins deux amis pour créer un tournoi.")
#         return data

#     def create(self, validated_data):
#         players = validated_data.pop('all_players', [])
#         creator = validated_data.pop('creator')

#         # Créez le tournoi
#         tournament = Tournament.objects.create(creator=creator, **validated_data)
#         tournament.players = players
#         return tournament

#     def update(self, instance, validated_data):
#         players = validated_data.pop('all_players', None)
#         if players is not None:
#             instance.players = players
#         return super().update(instance, validated_data)



class TournamentMatchSerializer(serializers.ModelSerializer):
    class Meta:
        model = TournamentMatch
        fields = '__all__'