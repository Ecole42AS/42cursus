-- Supprimer la base si elle existe pour redémarrer proprement
DROP DATABASE IF EXISTS wordpress;

-- Recréer la base de données WordPress avec les bons paramètres
CREATE DATABASE wordpress CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci;

-- Supprimer l'utilisateur WordPress pour éviter les conflits
DROP USER IF EXISTS 'wordpress_user'@'%';

-- Créer l'utilisateur avec un mot de passe sécurisé
CREATE USER 'wordpress_user'@'%' IDENTIFIED BY 'secure_wp_password';

-- Accorder tous les privilèges nécessaires à WordPress
GRANT ALL PRIVILEGES ON wordpress.* TO 'wordpress_user'@'%' WITH GRANT OPTION;

-- Appliquer les changements
FLUSH PRIVILEGES;
