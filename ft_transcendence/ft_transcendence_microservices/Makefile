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


clean:
	docker compose down -v --remove-orphans

fclean: clean

	docker compose rm -f

	docker rmi ft_transcendence_microservices-user_service ft_transcendence_microservices-matchtracker_service


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

createsuperuser_user_with_credentials:
	docker compose run --rm user_service python manage.py shell -c "exec('''from django.contrib.auth import get_user_model\nUser = get_user_model()\nif not User.objects.filter(username=\"alex\").exists():\n    User.objects.create_superuser(\"alex\", \"alexandre.stutz@hotmail.com\", \"deplanta1\")\n''')"

createsuperuser_matchtracker_with_credentials:
	docker compose run --rm matchtracker_service python manage.py shell -c "exec('''from django.contrib.auth import get_user_model\nUser = get_user_model()\nif not User.objects.filter(username=\"alex\").exists():\n    User.objects.create_superuser(\"alex\", \"alexandre.stutz@hotmail.com\", \"deplanta1\")\n''')"

createsuperuser_all: createsuperuser_user createsuperuser_matchtracker

create_superuser_all_with_credentials: createsuperuser_user_with_credentials createsuperuser_matchtracker_with_credentials

.PHONY: all build up down restart logs logs_all_since logs_all_from_now ps clean fclean re migrate createsuperuser_user createsuperuser_matchtracker createsuperuser_all
