# Documentation d'Utilisation des Endpoints de l'API

Cette documentation décrit comment utiliser les différents endpoints de l’API pour gérer les utilisateurs, les relations d’amitié et les sessions de jeu. Les endpoints nécessitant une authentification demandent l’inclusion d’un token JWT dans le header de vos requêtes :

```http
Authorization: Bearer <VOTRE_JWT_TOKEN>
```

---

## 1. Endpoints d’Authentification

### Obtenir un token

- **URL :** `/api/token/`
- **Méthode :** POST
- **Usage :** Envoyez vos identifiants pour obtenir un token d’accès et un token de rafraîchissement.
- **Exemple de requête :**
  ```bash
  curl -X POST http://your-domain.com/api/token/ \
       -H "Content-Type: application/json" \
       -d '{
         "username": "johndoe",
         "password": "password123"
       }'
  ```

### Rafraîchir un token

- **URL :** `/api/token/refresh/`
- **Méthode :** POST
- **Usage :** Envoyez votre token de rafraîchissement pour obtenir un nouveau token d’accès.

### Déconnexion (Blacklist d’un token)

- **URL :** `/api/token/logout/`
- **Méthode :** POST
- **Usage :** Invalidez un token (pour déconnecter l’utilisateur).

---

## 2. Endpoints Utilisateur

Ces endpoints sont accessibles sous le préfixe `/api/user/`.

### Enregistrement d’un utilisateur

- **URL :** `/api/user/register/`
- **Méthode :** POST
- **Usage :** Créez un nouveau compte utilisateur en fournissant les informations suivantes : `username`, `email`, `password`, `display_name` (et optionnellement `avatar`).
- **Exemple de requête :**
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

### Récupération et Mise à Jour du Profil

- **URL :** `/api/user/profile/`
- **Méthodes :** GET et PUT
- **Usage :**
  - **GET :** Récupère le profil de l’utilisateur authentifié.
  - **PUT :** Met à jour les informations de votre profil.
- **Exemple (GET) :**
  ```bash
  curl -X GET http://your-domain.com/api/user/profile/ \
       -H "Authorization: Bearer <VOTRE_JWT_TOKEN>"
  ```

### Récupération des Détails d’un Utilisateur

- **URL :** `/api/user/<int:user_id>/`
- **Méthode :** GET
- **Usage :** Obtenez les informations d’un utilisateur spécifique par son ID.
- **Exemple :**
  ```bash
  curl -X GET http://your-domain.com/api/user/2/
  ```

### Récupération du Profil d’un Utilisateur Spécifique

- **URL :** `/api/user/profile/<int:user_id>/`
- **Méthode :** GET
- **Usage :** Obtenez le profil détaillé d’un utilisateur en particulier (authentification requise).
- **Exemple :**
  ```bash
  curl -X GET http://your-domain.com/api/user/profile/2/ \
       -H "Authorization: Bearer <VOTRE_JWT_TOKEN>"
  ```

### Gestion des Relations d’Amitié

#### Liste des Amis

- **URL :** `/api/user/friends/`
- **Méthode :** GET
- **Usage :** Retourne la liste des amis de l’utilisateur authentifié.
- **Exemple :**
  ```bash
  curl -X GET http://your-domain.com/api/user/friends/ \
       -H "Authorization: Bearer <VOTRE_JWT_TOKEN>"
  ```

#### Ajouter un Ami

- **URL :** `/api/user/add_friend/<int:user_id>/`
- **Méthode :** POST
- **Usage :** Ajoutez un utilisateur en tant qu’ami (vous ne pouvez pas vous ajouter vous-même et vous ne pouvez pas ajouter un ami déjà existant).
- **Exemple :**
  ```bash
  curl -X POST http://your-domain.com/api/user/add_friend/3/ \
       -H "Authorization: Bearer <VOTRE_JWT_TOKEN>"
  ```

#### Vérifier le Statut d’Amitié

- **URL :** `/api/user/friendship-status/<int:user1_id>/<int:user2_id>/`
- **Méthode :** GET
- **Usage :** Vérifiez si deux utilisateurs (identifiés par `user1_id` et `user2_id`) sont amis.
- **Exemple :**
  ```bash
  curl -X GET http://your-domain.com/api/user/friendship-status/1/3/
  ```
- **Réponse attendue :**
  ```json
  {
    "is_friend": true
  }
  ```

### Recherche d’Utilisateurs

- **URL :** `/api/user/search/`
- **Méthode :** GET
- **Usage :** Recherchez des utilisateurs dont le `username` contient une chaîne donnée.  
- **Paramètre Query :** `q` (exemple : `/api/user/search/?q=doe`)
- **Exemple :**
  ```bash
  curl -X GET "http://your-domain.com/api/user/search/?q=john" \
       -H "Authorization: Bearer <VOTRE_JWT_TOKEN>"
  ```

### Validation d’un Token

- **URL :** `/api/user/validate/`
- **Méthode :** GET
- **Usage :** Valide votre token JWT et retourne les informations associées à votre compte.
- **Exemple :**
  ```bash
  curl -X GET http://your-domain.com/api/user/validate/ \
       -H "Authorization: Bearer <VOTRE_JWT_TOKEN>"
  ```
- **Réponse attendue :**
  ```json
  {
    "user_id": 1,
    "username": "johndoe"
  }
  ```

### Test de Session Redis

- **URL :** `/api/user/test-redis-session/`
- **Méthode :** GET
- **Usage :** Permet de vérifier que la session utilisateur est correctement stockée dans Redis.
- **Exemple :**
  ```bash
  curl -X GET http://your-domain.com/api/user/test-redis-session/
  ```
- **Réponse attendue :**
  ```
  Session unique_key is: my-default-unique-key
  ```

---

## 3. Endpoints Jeu

Ces endpoints gèrent la partie "jeu" de l’API, incluant les sessions de jeu, les tournois et les matchs.

### Endpoints via Routeur (ViewSets)

#### Games

- **URL :** `/games/`
- **Méthodes :** GET, POST, PUT, DELETE
- **Usage :** Gérer les sessions de jeu (création, modification, suppression, récupération).
- **Exemple (récupérer la liste des jeux pour l’utilisateur authentifié) :**
  ```bash
  curl -X GET http://your-domain.com/games/ \
       -H "Authorization: Bearer <VOTRE_JWT_TOKEN>"
  ```

#### Tournaments

- **URL :** `/tournaments/`
- **Méthodes :** GET, POST, PUT, DELETE
- **Usage :** Gérer les tournois.
- **Exemple (création d’un tournoi) :**
  ```bash
  curl -X POST http://your-domain.com/tournaments/ \
       -H "Content-Type: application/json" \
       -H "Authorization: Bearer <VOTRE_JWT_TOKEN>" \
       -d '{
         "name": "Tournoi Amical",
         "all_players": [1, 3, 4, 5]
       }'
  ```

#### Tournament Matches

- **URL :** `/tournament-matches/`
- **Méthodes :** GET, POST, PUT, DELETE
- **Usage :** Gérer les matchs dans un tournoi.

### Historique des Matchs

- **URL :** `/match-history/`
- **Méthode :** GET
- **Usage :** Récupérer l’historique des matchs terminés pour l’utilisateur authentifié.
- **Exemple :**
  ```bash
  curl -X GET http://your-domain.com/match-history/ \
       -H "Authorization: Bearer <VOTRE_JWT_TOKEN>"
  ```

### Création d’une Session de Jeu

- **URL :** `/create-game/<int:user_id>/`
- **Méthode :** POST
- **Usage :** Créer une session de jeu entre l’utilisateur authentifié et un autre utilisateur (identifié par `user_id`).
- **Exemple :**
  ```bash
  curl -X POST http://your-domain.com/create-game/3/ \
       -H "Authorization: Bearer <VOTRE_JWT_TOKEN>" \
       -H "Content-Type: application/json" \
       -d '{}'
  ```

### Mise à Jour du Score d’un Jeu

- **URL :** `/update-game-score/<int:game_id>/`
- **Méthode :** POST
- **Usage :** Mettre à jour les scores d’une session de jeu.  
  **Remarque :** Ce endpoint est protégé par un JWT de service.
- **Exemple :**
  ```bash
  curl -X POST http://your-domain.com/update-game-score/5/ \
       -H "Content-Type: application/json" \
       -H "Authorization: Bearer <VOTRE_JWT_TOKEN>" \
       -d '{
         "score_player1": 10,
         "score_player2": 8
       }'
  ```

### Endpoints de Tests Supplémentaires

#### Log Test

- **URL :** `/log-test/`
- **Méthode :** GET
- **Usage :** Générer des logs de différents niveaux pour vérifier la configuration du logging.

#### Test User

- **URL :** `/test-user/`
- **Méthode :** GET
- **Usage :** Vérifier l’authentification et obtenir un message de confirmation.
  
#### Test Games

- **URL :** `/test-games/`
- **Méthode :** GET
- **Usage :** Récupérer le nombre de parties associées à l’utilisateur authentifié.

#### Test Games Query

- **URL :** `/test-games-query/`
- **Méthode :** GET
- **Usage :** Comme `/test-games/` avec des logs détaillés.

#### Test Games No Permissions

- **URL :** `/test-games-no-permissions/`
- **Méthode :** GET
- **Usage :** Endpoint de test sans vérification stricte des permissions.

#### Test Redis Session (Jeu)

- **URL :** `/test-redis-session/`
- **Méthode :** GET
- **Usage :** Vérifier la gestion de la session via Redis pour la partie jeu.

---

## 4. Exemples d'Utilisation

### Exemple – Authentification et obtention d’un token

```bash
curl -X POST http://your-domain.com/api/token/ \
     -H "Content-Type: application/json" \
     -d '{
       "username": "johndoe",
       "password": "password123"
     }'
```

Utilisez ensuite le token obtenu dans vos autres requêtes, par exemple :

```bash
curl -X GET http://your-domain.com/api/user/profile/ \
     -H "Authorization: Bearer <VOTRE_JWT_TOKEN>"
```

### Exemple – Création d’une Session de Jeu

```bash
curl -X POST http://your-domain.com/create-game/3/ \
     -H "Content-Type: application/json" \
     -H "Authorization: Bearer <VOTRE_JWT_TOKEN>" \
     -d '{}'
```

### Exemple – Mise à Jour du Score d’un Jeu

```bash
curl -X POST http://your-domain.com/update-game-score/5/ \
     -H "Content-Type: application/json" \
     -H "Authorization: Bearer <VOTRE_JWT_TOKEN>" \
     -d '{
       "score_player1": 10,
       "score_player2": 8
     }'
```