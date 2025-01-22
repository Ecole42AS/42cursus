php-fpm7.3 -v >/dev/null 2>&1

# Boucle verification mariadb
while ! mariadb -u $MARIADB_USER --password=$MARIADB_PASS -h mariadb -P 3306 --silent 2>/dev/null;
do
	sleep 8
	echo "Mariadb n'est pas encore pret"
done
echo "MariaDB est prêt"

# Installation de WordPress si nécessaire
if [ -e /var/www/wordpress/wp-config.php ]
then
	echo "wp-config existe."
else
	echo "Installation de WP-CLI..."
	# Installation de wp-cli
	wget -q https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar
	chmod +x wp-cli.phar
	mv wp-cli.phar /usr/local/bin/wp

	# Installation de WordPress
	cd /var/www/wordpress
	wp core download --allow-root --quiet

	# Configuration de WP : connexion à la base de données et création des utilisateurs
	wp config create --dbname=$MARIADB_DB_NAME --dbuser=$MARIADB_USER --dbpass=$MARIADB_PASS --dbhost=$WP_HOST --dbcharset="utf8" --dbcollate="utf8_general_ci" --allow-root --quiet
	wp core install --url=$DOMAIN_NAME --title=$WP_TITLE --admin_user=$WP_ADMIN_USER --admin_password=$WP_ADMIN_PASSWORD --admin_email=$WP_ADMIN_EMAIL --skip-email --allow-root --quiet

	# Création de l'administrateur
	if wp user get "$WP_ADMIN_USER" --allow-root --path=/var/www/wordpress > /dev/null 2>&1; then
		echo "L'utilisateur administrateur $WP_ADMIN_USER existe déjà."
	else
		wp user create "$WP_ADMIN_USER" "$WP_ADMIN_EMAIL" --role=administrator --user_pass="$WP_ADMIN_PASSWORD" --allow-root --path=/var/www/wordpress --quiet
		echo "Utilisateur administrateur $WP_ADMIN_USER créé avec succès."
	fi

	# Création d'un utilisateur auteur distinct
	if wp user get "$WP_AUTHOR_USER" --allow-root --path=/var/www/wordpress > /dev/null 2>&1; then
		echo "L'utilisateur auteur $WP_AUTHOR_USER existe déjà."
	else
		wp user create "$WP_AUTHOR_USER" "$WP_AUTHOR_EMAIL" --role=author --user_pass="$WP_AUTHOR_PASSWORD" --allow-root --path=/var/www/wordpress --quiet
		echo "Utilisateur auteur $WP_AUTHOR_USER créé avec succès."
	fi

	echo "WordPress installé avec succès."
fi

# Lancement de php-fpm
php-fpm7.3 -F
