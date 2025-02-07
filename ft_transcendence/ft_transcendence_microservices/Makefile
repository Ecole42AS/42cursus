.PHONY: all build up down restart logs logs_all_since logs_all_from_now ps clean fclean re migrate createsuperuser_user createsuperuser_matchtracker createsuperuser_all

all: build up

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

logs_all_since:
	@echo "Affichage des nouveaux logs pour tous les conteneurs..."
	@for container in $(shell docker ps --format '{{.Names}}'); do \
		echo "Tailing logs for $$container"; \
		docker logs --since "2025-02-07T16:48:00" $$container & \
	done; \
	wait

logs_all_from_now:
	@echo "Affichage des nouveaux logs pour tous les conteneurs..."
	@for container in $(shell docker ps --format '{{.Names}}'); do \
		echo "Tailing logs for $$container"; \
		docker logs --tail 0 -f $$container & \
	done; \
	wait

ps:
	docker compose ps

# Clean: arrête et supprime les conteneurs et les volumes associés au projet.
clean:
	docker compose down -v --remove-orphans

# fclean: effectue un clean complet et supprime également les images du projet.
fclean: clean
	# Supprimez les conteneurs arrêtés (si nécessaire)
	docker compose rm -f
	# Supprimez les images du projet (adapté à vos images)
	docker rmi ft_transcendence_microservices-user_service ft_transcendence_microservices-matchtracker_service

# Re: Clean complet suivi de build et up.
re: fclean all

migrate:
	docker compose run --rm user_service python manage.py makemigrations
	docker compose run --rm user_service python manage.py migrate
	docker compose run --rm matchtracker_service python manage.py makemigrations
	docker compose run --rm matchtracker_service python manage.py migrate

createsuperuser_user:
	docker compose run --rm user_service python manage.py createsuperuser

createsuperuser_matchtracker:
	docker compose run --rm matchtracker_service python manage.py createsuperuser

createsuperuser_all: createsuperuser_user createsuperuser_matchtracker
