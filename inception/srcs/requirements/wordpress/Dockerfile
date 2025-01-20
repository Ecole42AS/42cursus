FROM wordpress:5.8-php8.1-fpm

# Installer les extensions PHP nécessaires
RUN docker-php-ext-install mysqli

# Mettre à jour le système et installer les paquets nécessaires en une seule commande
RUN apt-get update && apt-get install -y --no-install-recommends \
    default-mysql-client \
    vim \
    curl \
    procps \
    iproute2 \
    && rm -rf /var/lib/apt/lists/*

# Exposer le port 9000 pour PHP-FPM
EXPOSE 9000

# Lancer PHP-FPM en tant que processus principal
CMD ["php-fpm"]
