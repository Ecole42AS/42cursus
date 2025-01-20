FROM mariadb:10.6

# Définition des variables d'environnement pour MariaDB
ENV MYSQL_DATABASE=wordpress
ENV MYSQL_USER=wordpress_user

# Utilisation des fichiers secrets pour les mots de passe
ENV MYSQL_ROOT_PASSWORD_FILE=/run/secrets/db_root_password
ENV MYSQL_PASSWORD_FILE=/run/secrets/db_password

# Copier le script SQL d'initialisation si besoin
COPY init.sql /docker-entrypoint-initdb.d/

# Exposer le port MySQL
EXPOSE 3306

# Lancer le serveur MariaDB
CMD ["docker-entrypoint.sh", "mysqld"]
