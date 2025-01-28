#!/bin/bash

# Vérification de la version PHP
if ! php-fpm7.3 -v >/dev/null 2>&1; then
    echo "PHP-FPM 7.3 n'est pas installé ou accessible."
    exit 1
fi

# Attente de la disponibilité de MariaDB
echo "Attente de la disponibilité de MariaDB..."
while ! mysqladmin ping -h mariadb -u"$MARIADB_USER" -p"$MARIADB_PASS" --silent; do
    sleep 8
    echo "MariaDB n'est pas encore prêt..."
done
echo "MariaDB est prêt."

# Installation de WordPress si nécessaire
if [ -e /var/www/wordpress/wp-config.php ]; then
    echo "wp-config.php existe déjà. Installation de WordPress non nécessaire."
else
    echo "Installation de WP-CLI..."
    # Vérification et installation de WP-CLI si non présent
    if ! command -v wp >/dev/null 2>&1; then
        wget -q https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar
        chmod +x wp-cli.phar
        mv wp-cli.phar /usr/local/bin/wp
    fi

    # Téléchargement et configuration de WordPress
    echo "Téléchargement et configuration de WordPress..."
    cd /var/www/wordpress || exit
    wp core download --allow-root --quiet

    wp config create \
        --dbname="$MARIADB_DB_NAME" \
        --dbuser="$MARIADB_USER" \
        --dbpass="$MARIADB_PASS" \
        --dbhost="$WP_HOST" \
        --dbcharset="utf8" \
        --dbcollate="utf8_general_ci" \
        --allow-root --quiet

    wp core install \
        --url="$DOMAIN_NAME" \
        --title="$WP_TITLE" \
        --admin_user="$WP_ADMIN_USER" \
        --admin_password="$WP_ADMIN_PASSWORD" \
        --admin_email="$WP_ADMIN_EMAIL" \
        --skip-email \
        --allow-root --quiet

    # Sécurisation du fichier wp-config.php
    echo "Sécurisation de wp-config.php..."
    chmod 600 /var/www/wordpress/wp-config.php
    chown www-data:www-data /var/www/wordpress/wp-config.php

    # Création de l'administrateur WordPress
    if ! wp user get "$WP_ADMIN_USER" --allow-root --path=/var/www/wordpress > /dev/null 2>&1; then
        wp user create "$WP_ADMIN_USER" "$WP_ADMIN_EMAIL" \
            --role=administrator \
            --user_pass="$WP_ADMIN_PASSWORD" \
            --allow-root --path=/var/www/wordpress --quiet
        echo "Utilisateur administrateur $WP_ADMIN_USER créé avec succès."
    else
        echo "L'utilisateur administrateur $WP_ADMIN_USER existe déjà."
    fi

    # Création d'un utilisateur auteur WordPress
    if ! wp user get "$WP_AUTHOR_USER" --allow-root --path=/var/www/wordpress > /dev/null 2>&1; then
        wp user create "$WP_AUTHOR_USER" "$WP_AUTHOR_EMAIL" \
            --role=author \
            --user_pass="$WP_AUTHOR_PASSWORD" \
            --allow-root --path=/var/www/wordpress --quiet
        echo "Utilisateur auteur $WP_AUTHOR_USER créé avec succès."
    else
        echo "L'utilisateur auteur $WP_AUTHOR_USER existe déjà."
    fi

    echo "WordPress installé avec succès."
fi

# Lancement de php-fpm
echo "Démarrage de PHP-FPM..."
php-fpm7.3 -F
