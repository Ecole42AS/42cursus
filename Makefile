# Makefile for Librairie Symfony + SQL Server


COMPOSE = docker compose
PHP     = $(COMPOSE) exec php

.PHONY: build up down restart install wait-sql db-create db-migrate cache-clear shell logs test

build:
	docker build -t php-sqlsrv:8.3.17 ~/docker-php-sqlsrv

up:
	$(COMPOSE) up -d

down:
	$(COMPOSE) down

restart: down up

install:
	$(PHP) composer install --no-interaction

wait-sql:
	@echo "⏳ Waiting for SQL Server to become available…"
	@until docker compose exec sqlserver /opt/mssql-tools/bin/sqlcmd -U SA -P "$(MSSQL_PASSWORD)" -Q "SELECT 1" > /dev/null 2>&1; do \
	  echo "Still waiting…"; sleep 5; \
	done

db-create:
	$(PHP) php bin/console doctrine:database:create --if-not-exists

db-migrate: wait-sql
	$(PHP) php bin/console doctrine:migrations:migrate --no-interaction

cache-clear:
	$(PHP) php bin/console cache:clear

shell:
	$(PHP) bash

logs:
	$(COMPOSE) logs -f php

test:
	$(PHP) php bin/phpunit
