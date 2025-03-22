# Makefile for Librairie Symfony + SQL Server

COMPOSE = docker compose
PHP     = $(COMPOSE) exec php

.PHONY: build up down restart install db-create db-migrate cache-clear shell logs test

build:
	docker build -t php-sqlsrv:8.3.17 ~/docker-php-sqlsrv

up:
	$(COMPOSE) up -d

down:
	$(COMPOSE) down

restart: down up

install:
	$(PHP) composer install --no-interaction

db-create:
	$(PHP) php bin/console doctrine:database:create --if-not-exists

db-migrate:
	$(PHP) php bin/console doctrine:migrations:migrate --no-interaction

cache-clear:
	$(PHP) php bin/console cache:clear

shell:
	$(PHP) bash

logs:
	$(COMPOSE) logs -f php

test:
	$(PHP) php bin/phpunit
