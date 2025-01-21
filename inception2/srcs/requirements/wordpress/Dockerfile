FROM alpine:3.17

# Installer PHP, extensions et autres dépendances nécessaires
RUN apk update && apk add --no-cache \
    php81 \
    php81-fpm \
    php81-mysqli \
    php81-curl \
    php81-opcache \
    php81-gd \
    php81-mbstring \
    php81-xml \
    php81-zip \
    curl \
    wget \
    unzip \
    && rm -rf /var/cache/apk/*

# Télécharger et installer WordPress
WORKDIR /var/www/html
RUN curl -o wordpress.tar.gz https://wordpress.org/latest.tar.gz \
    && tar -xzf wordpress.tar.gz --strip-components=1 \
    && rm wordpress.tar.gz

# Copier le fichier de configuration personnalisé si nécessaire
COPY conf/wp-config.php /var/www/html/wp-config.php

# Exposer le port pour PHP-FPM
EXPOSE 9000

# Démarrer PHP-FPM
CMD ["php-fpm81", "-F"]
