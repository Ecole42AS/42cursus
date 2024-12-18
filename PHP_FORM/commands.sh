#!/bin/bash

# Lancer un serveur local PHP
php -S localhost:8000 -t .

# Connexion à MySQL
mysql -u root -p

# Charger un fichier SQL dans MySQL
mysql -u root -p < commands.sql

# Lister les bases de données dans MySQL
echo "SHOW DATABASES;" | mysql -u root -p

# Démarrer MySQL via le service (Linux/MacOS)
sudo service mysql start

# Arrêter MySQL
sudo service mysql stop

# Vérifier le statut de MySQL
sudo service mysql status
