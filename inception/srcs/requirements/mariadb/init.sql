-- Création de la base de données WordPress si elle n'existe pas
CREATE DATABASE IF NOT EXISTS wordpress;

-- Création de l'utilisateur WordPress s'il n'existe pas
CREATE USER IF NOT EXISTS 'wordpress_user'@'%' IDENTIFIED BY 'wordpress_password';

-- Accorder tous les privilèges à l'utilisateur WordPress sur la base de données
GRANT ALL PRIVILEGES ON wordpress.* TO 'wordpress_user'@'%';

-- Appliquer les changements
FLUSH PRIVILEGES;
