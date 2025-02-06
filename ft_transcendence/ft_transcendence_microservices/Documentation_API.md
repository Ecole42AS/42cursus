# Documentation API

Cette documentation décrit les endpoints de l’API ainsi que le formatage des données grâce aux serializers. L’API est organisée en plusieurs sections, notamment la gestion des utilisateurs, des relations amicales et des sessions de jeu (tournois, matchs, etc.). Certaines routes sont protégées et nécessitent un token JWT.

> **Note :** Pour les endpoints nécessitant une authentification, incluez dans vos requêtes un header :
> ```http
> Authorization: Bearer <VOTRE_JWT_TOKEN>
> ```

---

## Table des matières

- [Authentification](#authentification)
- [Endpoints Utilisateur](#endpoints-utilisateur)
  - [Enregistrement](#enregistrement)
  - [Profil de l’utilisateur](#profil-de-lutilisateur)
  - [Détails d’un utilisateur](#détails-dun-utilisateur)
  - [Liste d’amis et gestion des amitiés](#liste-damis-et-gestion-des-amitiés)
  - [Recherche d’utilisateurs](#recherche-dutilisateurs)
  - [Validation de token](#validation-de-token)
  - [Test de session Redis](#test-de-session-redis)
- [Endpoints Jeu](#endpoints-jeu)
  - [Endpoints via Routeur (ViewSets)](#endpoints-via-routeur-viewsets)
  - [Historique des matchs](#historique-des-matchs)
  - [Création d’une session de jeu](#création-dune-session-de-jeu)
  - [Mise à jour du score d’un jeu](#mise-à-jour-du-score-dun-jeu)
  - [Endpoints de tests supplémentaires](#endpoints-de-tests-supplémentaires)
- [Endpoints d’authentification JWT](#endpoints-dauthentification-jwt)
- [Administration et Fichiers Statics](#administration-et-fichiers-statics)
- [Serializers](#serializers)
- [Exemples de requêtes](#exemples-de-requêtes)

---

## Authentification

L’API utilise des tokens JWT pour sécuriser l’accès aux endpoints protégés.

- **Obtenir un token :**  
  **URL :** `/api/token/`  
  **Méthode :** POST  
  **Description :** Permet d’obtenir un couple (access, refresh) de tokens via `TokenObtainPairView`.  
  **Exemple de requête :**
  ```bash
  curl -X POST http://your-domain.com/api/token/ \
       -H "Content-Type: application/json" \
       -d '{
         "username": "johndoe",
         "password": "password123"
       }'
  ```

- **Rafraîchir un token :**  
  **URL :** `/api/token/refresh/`  
  **Méthode :** POST  

- **Déconnexion / Blacklist d’un token :**  
  **URL :** `/api/token/logout/`  
  **Méthode :** POST

---

## Endpoints Utilisateur

Ces endpoints sont accessibles sous le préfixe `/api/user/`.

### Enregistrement

- **URL :** `/api/user/register/`  
- **Méthode :** POST  
- **Description :** Crée un nouveau compte utilisateur.  
- **Corps de la requête :**  
  JSON ou form-data contenant les informations de l’utilisateur (par exemple, `username`, `email`, `password`, ainsi que `display_name` et éventuellement `avatar`).
- **Réponse :** Données utilisateur et statut HTTP 201 en cas de succès.

### Profil de l’utilisateur

- **URL :** `/api/user/profile/`  
- **Méthodes :** GET, PUT  
- **Description :**  
  - **GET :** Récupère le profil de l’utilisateur authentifié.  
  - **PUT :** Met à jour le profil de l’utilisateur authentifié.
- **Authentification :** Requise (JWT).

### Détails d’un utilisateur

- **URL :** `/api/user/<int:user_id>/`  
- **Méthode :** GET  
- **Description :** Récupère les informations d’un utilisateur spécifique par son ID.  
- **Authentification :** Optionnelle.

### Profil détaillé

- **URL :** `/api/user/profile/<int:user_id>/`  
- **Méthode :** GET  
- **Description :** Récupère les informations de profil d’un utilisateur spécifique.  
- **Authentification :** Requise (JWT).

### Liste d’amis et gestion des amitiés

#### Liste des amis

- **URL :** `/api/user/friends/`  
- **Méthode :** GET  
- **Description :** Retourne la liste des amis de l’utilisateur authentifié.
  
#### Ajouter un ami

- **URL :** `/api/user/add_friend/<int:user_id>/`  
- **Méthode :** POST  
- **Description :** Permet à l’utilisateur authentifié d’ajouter un autre utilisateur en tant qu’ami.  
- **Réponses possibles :**  
  - **201 Created :** Ami ajouté avec succès.  
  - **400 Bad Request :** Si l’utilisateur tente de s’ajouter lui-même ou s’il est déjà ami.

#### Statut d’amitié

- **URL :** `/api/user/friendship-status/<int:user1_id>/<int:user2_id>/`  
- **Méthode :** GET  
- **Description :** Vérifie si les deux utilisateurs (user1 et user2) sont amis.  
- **Réponse :**
  ```json
  {
    "is_friend": true
  }
  ```

### Recherche d’utilisateurs

- **URL :** `/api/user/search/`  
- **Méthode :** GET  
- **Description :** Recherche des utilisateurs dont le nom d’utilisateur contient la chaîne spécifiée dans le paramètre `q`.  
- **Paramètre Query :**  
  - `q` : chaîne de recherche.
- **Authentification :** Requise (JWT).

### Validation de token

- **URL :** `/api/user/validate/`  
- **Méthode :** GET  
- **Description :** Valide un token JWT et retourne les informations de l’utilisateur correspondant.
- **Réponse :**
  ```json
  {
    "user_id": 1,
    "username": "johndoe"
  }
  ```

### Test de session Redis

- **URL :** `/api/user/test-redis-session/`  
- **Méthode :** GET  
- **Description :** Vérifie le stockage de session via Redis et retourne la valeur de la clé `unique_key`.
- **Réponse :**
  ```text
  Session unique_key is: my-default-unique-key
  ```

---

## Endpoints Jeu

Ces endpoints sont principalement gérés via des ViewSets et quelques endpoints additionnels.

### Endpoints via Routeur (ViewSets)

- **Games :** `/games/`  
  Permet les opérations CRUD sur les sessions de jeu via le `GameViewSet`.

- **Tournaments :** `/tournaments/`  
  Gestion des tournois via le `TournamentViewSet`.

- **Tournament Matches :** `/tournament-matches/`  
  Gestion des matchs de tournoi via le `TournamentMatchViewSet`.

### Historique des matchs

- **URL :** `/match-history/`  
- **Méthode :** GET  
- **Description :** Retourne l’historique des matchs terminés de l’utilisateur authentifié.

### Création d’une session de jeu

- **URL :** `/create-game/<int:user_id>/`  
- **Méthode :** POST  
- **Description :** Crée une nouvelle session de jeu entre l’utilisateur authentifié et un autre utilisateur identifié par `user_id`.
- **Authentification :** Requise (JWT).
- **Réponses possibles :**  
  - **201 Created :** Session créée avec succès.  
  - **400 Bad Request :** Si un match actif existe déjà ou si l’utilisateur essaie de jouer contre lui-même.

### Mise à jour du score d’un jeu

- **URL :** `/update-game-score/<int:game_id>/`  
- **Méthode :** POST  
- **Description :** Met à jour le score d’une session de jeu.  
- **Authentification :**  
  L’accès est contrôlé via un JWT de service (vérification du header `Authorization` de type Bearer).
- **Corps de la requête :**
  ```json
  {
    "score_player1": 10,
    "score_player2": 8
  }
  ```
- **Réponse :** Confirmation de la mise à jour ou message d’erreur.

### Endpoints de tests supplémentaires

- **Log Test :**  
  **URL :** `/log-test/`  
  **Méthode :** GET  
  **Description :** Génère plusieurs logs (DEBUG, INFO, WARNING, ERROR, CRITICAL) pour tester le logging.
- **Test User :**  
  **URL :** `/test-user/`  
  **Méthode :** GET  
  **Description :** Vérifie l’authentification et retourne un message de confirmation.
- **Test Games :**  
  **URL :** `/test-games/`  
  **Méthode :** GET  
  **Description :** Retourne le nombre de parties de l’utilisateur authentifié.
- **Test Games Query :**  
  **URL :** `/test-games-query/`  
  **Méthode :** GET  
  **Description :** Similaire à `/test-games/` avec des logs détaillés.
- **Test Games No Permissions :**  
  **URL :** `/test-games-no-permissions/`  
  **Méthode :** GET  
  **Description :** Endpoint de test sans vérification stricte des permissions.
- **Test Redis Session (Jeu) :**  
  **URL :** `/test-redis-session/`  
  **Méthode :** GET  
  **Description :** Vérifie la gestion de la session via Redis (similaire à l’endpoint utilisateur).

---

## Endpoints d’authentification JWT (URL principale)

- **Obtenir un token :**  
  **URL :** `/api/token/`  
  **Méthode :** POST  
  **Description :** Obtenir un token d’accès et un token de rafraîchissement via `TokenObtainPairView`.

- **Rafraîchir le token :**  
  **URL :** `/api/token/refresh/`  
  **Méthode :** POST

- **Déconnexion :**  
  **URL :** `/api/token/logout/`  
  **Méthode :** POST

---

## Administration et Fichiers Statics

- **Interface d’administration :**  
  **URL :** `/admin/`  
  **Méthode :** GET  
  **Description :** Interface d’administration de Django (accessible aux administrateurs).

- **Fichiers médias :**  
  En mode DEBUG, les fichiers médias sont servis via l’URL définie par `settings.MEDIA_URL`.

---

## Serializers

Les serializers définissent la manière dont les données des modèles sont converties en formats JSON pour les réponses de l’API et validées lors des requêtes entrantes. Voici un aperçu des principaux serializers utilisés :

### FriendshipSerializer

- **Utilité :**  
  Formate les données d’amitié provenant du service utilisateur.
- **Champs :**  
  - `user` : Identifiant de l’utilisateur.
  - `friend` : Identifiant de l’ami.
  - `created_at` : Date de création de l’amitié.

### GameSerializer

- **Utilité :**  
  Sérialise les données de la session de jeu (GameSession).
- **Champs principaux :**  
  - `id`, `score_player1`, `score_player2`, `is_active`, `created_at`, `start_time`, `ended_at`
  - **Champs calculés :**  
    - `player1`, `player2` et `winner` sont obtenus via des méthodes personnalisées qui récupèrent les données utilisateur à l’aide d’un cache interne et d’un appel à la fonction `get_user_data`.
- **Remarque :**  
  Le serializer utilise la méthode `fetch_user_data` pour interroger un microservice (ou une fonction utilitaire) afin d’obtenir les informations (comme le nom d’utilisateur) et les mettre en cache pour optimiser les performances.

### TournamentSerializer

- **Utilité :**  
  Gère la sérialisation des tournois.
- **Champs :**  
  - `id`, `name`, `creator_id`, `players`, `created_at`
  - `all_players` : Liste d’IDs des joueurs à ajouter (champ en écriture uniquement).
  - `players_display_names` : Noms affichés des joueurs, obtenus via une méthode qui interroge le microservice utilisateur.
- **Validations personnalisées :**  
  - Vérifie que tous les joueurs (autres que l’utilisateur connecté) figurent parmi les amis de l’utilisateur.
  - S’assure que le nombre total de joueurs (incluant l’utilisateur connecté) est pair et respecte le minimum requis pour un tournoi (au moins 4 joueurs).

### TournamentMatchSerializer

- **Utilité :**  
  Sérialise les données d’un match de tournoi.
- **Champs :**  
  Utilise tous les champs du modèle TournamentMatch (`fields = '__all__'`).

### ProfileSerializer

- **Utilité :**  
  Sérialise les données du profil d’un utilisateur.
- **Champs :**  
  - `display_name`, `avatar`, `wins`, `losses`
- **Remarque :**  
  Les champs `wins` et `losses` sont en lecture seule. La méthode `update` gère la validation pour s’assurer que le `display_name` est unique.

### UserSerializer

- **Utilité :**  
  Sérialise et gère la création/mise à jour des utilisateurs (CustomUser).
- **Champs :**  
  - `id`, `username`, `password`, `email`, `display_name`, `avatar`
- **Spécificités :**  
  - `display_name` et `avatar` sont des champs écriture pour la création d’un profil.
  - La validation du `display_name` s’assure qu’aucun profil existant ne possède déjà ce nom.
  - La méthode `create` gère la création d’un utilisateur et la mise à jour associée du profil (affectation du `display_name` et de l’avatar).
  - La méthode `update` permet de mettre à jour les informations de l’utilisateur et son profil.

### PublicUserSerializer

- **Utilité :**  
  Fournit une version en lecture seule des données utilisateur à des fins publiques.
- **Champs :**  
  - `id`, `username`, `display_name` et `avatar` (ces deux derniers sont obtenus à partir du profil).

---

## Exemples de requêtes

### Exemple – Enregistrement d’un utilisateur

```bash
curl -X POST http://your-domain.com/api/user/register/ \
     -H "Content-Type: application/json" \
     -d '{
       "username": "johndoe",
       "email": "john@example.com",
       "password": "password123",
       "display_name": "John Doe"
     }'
```

### Exemple – Authentification et obtention d’un token

```bash
curl -X POST http://your-domain.com/api/token/ \
     -H "Content-Type: application/json" \
     -d '{
       "username": "johndoe",
       "password": "password123"
     }'
```

Utilisez ensuite le token dans vos requêtes avec :

```http
Authorization: Bearer <VOTRE_JWT_TOKEN>
```

---

Cette documentation fournit une vue d’ensemble complète de vos endpoints et explique comment les serializers transforment et valident les données échangées. N’hésitez pas à l’enrichir en ajoutant des exemples de réponses ou des précisions sur les codes d’erreur spécifiques selon vos besoins.