# Utiliser Alpine comme image de base
FROM alpine:3.17

# Ajouter l'utilisateur MySQL
RUN addgroup -S mysql && adduser -S mysql -G mysql

# Installation de MariaDB et outils nécessaires
RUN apk update && apk add --no-cache mariadb mariadb-client mariadb-server-utils bash && \
    mkdir -p /var/lib/mysql /docker-entrypoint-initdb.d && \
    chown -R mysql:mysql /var/lib/mysql /docker-entrypoint-initdb.d && \
    chmod 777 /var/lib/mysql /docker-entrypoint-initdb.d

# Copier le script SQL d'initialisation
COPY init.sql /docker-entrypoint-initdb.d/

# Exposer le port MySQL
EXPOSE 3306

# Passer en tant qu'utilisateur MySQL
USER mysql

# Commande de démarrage de MariaDB
CMD ["mysqld", "--datadir=/var/lib/mysql", "--console"]