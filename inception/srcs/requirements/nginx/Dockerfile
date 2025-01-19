# Utiliser Alpine comme base légère
FROM alpine:3.17

# Installer NGINX et OpenSSL
RUN apk add --no-cache nginx openssl
RUN apk add --no-cache curl

# Créer un dossier pour les certificats SSL et en générer un auto-signé
RUN mkdir -p /etc/nginx/ssl && \
    openssl req -x509 -nodes -days 365 \
    -subj "/CN=localhost" \
    -newkey rsa:2048 -keyout /etc/nginx/ssl/nginx.key \
    -out /etc/nginx/ssl/nginx.crt

# Copier la configuration NGINX
COPY conf/nginx.conf /etc/nginx/nginx.conf

# Ouvrir le port 443 pour HTTPS
EXPOSE 443

# Lancer NGINX
CMD ["nginx", "-g", "daemon off;"]

