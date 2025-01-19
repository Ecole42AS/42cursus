FROM wordpress:5.8-php8.1-fpm

RUN docker-php-ext-install mysqli
RUN apt-get update && apt-get install -y default-mysql-client
RUN apt-get update && apt-get install -y vim
RUN apt-get update && apt-get install -y curl
RUN apt-get update && apt-get install -y procps
RUN apt-get update && apt-get install -y iproute2

EXPOSE 9000
CMD ["php-fpm"]

