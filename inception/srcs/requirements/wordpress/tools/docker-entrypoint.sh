php-fpm7.3 -v >/dev/null 2>&1

# Boucle verification mariadb
while ! mariadb -u $MARIADB_USER --password=$MARIADB_PASS -h mariadb -P 3306 --silent 2>/dev/null;
do
	sleep 8
	echo "Mariadb n'est pas encore pret"
done
	echo "MariaDB est prêt"

# Installation de Wordpress si necessaire
if [ -e /var/www/wordpress/wp-config.php ]
then
	echo "wp-config existe."
else
	echo "Installation de WP-CLI..."
	# Installation de wp-cli
	wget -q https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar
	chmod +x wp-cli.phar
	mv wp-cli.phar /usr/local/bin/wp

	# Installation de wordpress
	cd /var/www/wordpress
	wp core download --allow-root --quiet

	# Configuration de WP : connection a la base de donnees et creation des users
	wp config create --dbname=$MARIADB_DB_NAME --dbuser=$MARIADB_USER --dbpass=$MARIADB_PASS --dbhost=$WP_HOST --dbcharset="utf8" --dbcollate="utf8_general_ci" --allow-root --quiet
	wp core install --url=$DOMAIN_NAME --title=$WP_TITLE --admin_user=$WP_ADMIN_USER --admin_password=$WP_ADMIN_PASSWORD --admin_email=$WP_ADMIN_EMAIL --skip-email --allow-root --quiet
	wp user create $WP_USER $WP_USER_EMAIL --role=author --user_pass=$WP_USER_PASS --allow-root --quiet

	echo "WordPress installé avec succès."
fi

# Lancement de php-fpm
php-fpm7.3 -F
