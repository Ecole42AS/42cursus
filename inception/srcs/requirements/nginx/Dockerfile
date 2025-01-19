# Utiliser Alpine comme base légère
FROM alpine:3.17

# Installer NGINX, OpenSSL et Curl puis nettoyer le cache
RUN apk add --no-cache nginx openssl curl && \
    rm -rf /var/cache/apk/*

# Ajouter un utilisateur non root pour exécuter NGINX
RUN addgroup -S nginx || true && adduser -S nginx -G nginx || true
# Créer un dossier pour les certificats SSL et en générer un auto-signé sécurisé
RUN mkdir -p /etc/nginx/ssl && \
    openssl req -x509 -nodes -days 365 \
    -subj "/C=US/ST=State/L=City/O=Company/CN=localhost" \
    -newkey rsa:4096 -keyout /etc/nginx/ssl/nginx.key \
    -out /etc/nginx/ssl/nginx.crt

# Copier la configuration NGINX avec les bonnes permissions
COPY --chown=nginx:nginx conf/nginx.conf /etc/nginx/nginx.conf

# Définir les volumes pour la persistance
VOLUME ["/etc/nginx/ssl", "/var/log/nginx"]

# Ouvrir le port 443 pour HTTPS
EXPOSE 443

# Passer à l'utilisateur non root
USER nginx

# Lancer NGINX
CMD ["nginx", "-g", "daemon off;"]
