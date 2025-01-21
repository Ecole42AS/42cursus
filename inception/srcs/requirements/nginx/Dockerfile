FROM debian:buster

# Installation de nginx et openssl en une seule commande pour réduire les couches
RUN apt-get update -y && \
    apt-get upgrade -y && \
    apt-get install -y nginx openssl

# Configuration SSL
RUN mkdir -p /etc/nginx/ssl && \
    openssl req -x509 -nodes -days 365 -newkey rsa:2048 \
    -keyout /etc/nginx/ssl/inception.key \
    -out /etc/nginx/ssl/inception.crt \
    -subj "/C=SW/ST=VS/L=Lausanne/O=42/OU=42/CN=cmansey.42.ch/emailAddress=cmansey@student.42lausanne.ch"

# Création des répertoires nécessaires et configuration des droits
RUN mkdir -p /var/run/nginx /var/www/wordpress && \
    chmod -R 755 /var/www/wordpress && \
    chown -R www-data:www-data /var/www/wordpress

# Copie du fichier de configuration et du script de démarrage
COPY conf/nginx.conf /etc/nginx/nginx.conf
COPY tools/docker-entrypoint.sh /usr/local/bin/docker-entrypoint.sh
RUN chmod +x /usr/local/bin/docker-entrypoint.sh

# Exposition du port 443 pour SSL
EXPOSE 443

ENTRYPOINT ["/usr/local/bin/docker-entrypoint.sh"]
