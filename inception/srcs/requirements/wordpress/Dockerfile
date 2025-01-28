FROM debian:buster

# Update and install necessary packages
RUN apt update -y && apt upgrade -y \
    && apt-get install -y wget curl php7.3 php-fpm php-mysql mariadb-client ca-certificates --no-install-recommends \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

# Install WP-CLI
RUN curl -O https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar \
    && chmod +x wp-cli.phar \
    && mv wp-cli.phar /usr/local/bin/wp

# Create required directories
RUN mkdir -p /var/www/wordpress /run/php

# Set permissions for the WordPress directory
RUN chown -R www-data:www-data /var/www \
    && chmod -R 755 /var/www

# Copy PHP configuration and the entrypoint script
COPY conf/www.conf /etc/php/7.3/fpm/pool.d/www.conf
COPY tools/docker-entrypoint.sh /usr/local/bin/docker-entrypoint.sh
RUN chmod +x /usr/local/bin/docker-entrypoint.sh

# Expose port 9000 for PHP-FPM
EXPOSE 9000

# Set the entrypoint
ENTRYPOINT ["sh", "/usr/local/bin/docker-entrypoint.sh"]
