.PHONY: all build up down restart logs ps clean migrate createsuperuser re

all: build up

re: clean all

build:
	docker compose build

up: migrate
	docker compose up -d

down:
	docker compose down

restart:
	docker compose restart

logs:
	docker compose logs -f

ps:
	docker compose ps

clean:
	docker compose down -v

# Applique les migrations dans le service user_service
migrate:
	docker compose run --rm user_service python manage.py makemigrations
	docker compose run --rm user_service python manage.py migrate

# Crée un superutilisateur pour Django
createsuperuser:
	docker compose run --rm user_service python manage.py createsuperuser
