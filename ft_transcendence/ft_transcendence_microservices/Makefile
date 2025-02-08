.PHONY: all build up down restart logs logs_all_since logs_all_from_now ps clean fclean re migrate createsuperuser_user createsuperuser_matchtracker createsuperuser_all psql_matchtracker psql_user

# La cible "all" effectue une construction puis démarre les conteneurs.
all: build up

# Construction des images Docker
build:
	docker compose build

# Pour le service user_service : on filtre uniquement les conteneurs running
USER_CMD := $(if $(shell docker compose ps --filter status=running -q user_service),docker compose exec user_service,docker compose run --rm user_service)

# Pour matchtracker_service de même
MATCHTRACKER_CMD := $(if $(shell docker compose ps --filter status=running -q matchtracker_service),docker compose exec matchtracker_service,docker compose run --rm matchtracker_service)

migrate:
	@echo "Migrating user_service..."
	$(USER_CMD) python manage.py makemigrations
	$(USER_CMD) python manage.py migrate
	@echo "Migrating matchtracker_service..."
	$(MATCHTRACKER_CMD) python manage.py makemigrations game
	$(MATCHTRACKER_CMD) python manage.py migrate

# La cible "up" lance les conteneurs en arrière-plan après avoir migré
up: migrate
	docker compose up -d

# Arrête et supprime les conteneurs
down:
	docker compose down

# Redémarre tous les conteneurs
restart:
	docker compose restart

# Affiche les logs en continu pour tous les conteneurs
logs:
	docker compose logs -f

# Affiche les logs depuis une date/heure donnée pour tous les conteneurs
logs_all_since:
	@echo "Affichage des nouveaux logs pour tous les conteneurs depuis 2025-02-07T16:48:00..."
	@for container in $(shell docker ps --format '{{.Names}}'); do \
		echo "Tailing logs for $$container"; \
		docker logs --since "2025-02-07T16:48:00" $$container & \
	done; \
	wait

# Affiche les logs en temps réel (uniquement les nouveaux messages)
logs_all_from_now:
	@echo "Affichage en temps réel des nouveaux logs pour tous les conteneurs..."
	@for container in $(shell docker ps --format '{{.Names}}'); do \
		echo "Tailing logs for $$container"; \
		docker logs --tail 0 -f $$container & \
	done; \
	wait

# Affiche l'état des conteneurs
ps:
	docker compose ps

# Arrête et supprime les conteneurs et les volumes associés
clean:
	docker compose down -v --remove-orphans

# Clean complet : supprime également les images créées
fclean: clean
	# Supprimez les conteneurs arrêtés (si nécessaire)
	docker compose rm -f
	# Supprimez les images du projet (ajustez selon vos images)
	docker rmi ft_transcendence_microservices-user_service ft_transcendence_microservices-matchtracker_service

# Re : Clean complet suivi d'une reconstruction et d'un démarrage
re: fclean all

# Cibles pour créer un superuser via l'interface interactive
createsuperuser_user:
	docker compose run --rm user_service python manage.py createsuperuser

createsuperuser_matchtracker:
	docker compose run --rm matchtracker_service python manage.py createsuperuser

createsuperuser_all: createsuperuser_user createsuperuser_matchtracker

# Cibles pour créer automatiquement un superuser avec des identifiants prédéfinis
createsuperuser_user_with_credentials:
	docker compose run --rm user_service python manage.py shell -c "exec('''from django.contrib.auth import get_user_model\nUser = get_user_model()\nif not User.objects.filter(username=\"alex\").exists():\n    User.objects.create_superuser(\"alex\", \"alexandre.stutz@hotmail.com\", \"deplanta1\")\n''')"

createsuperuser_matchtracker_with_credentials:
	docker compose run --rm matchtracker_service python manage.py shell -c "exec('''from django.contrib.auth import get_user_model\nUser = get_user_model()\nif not User.objects.filter(username=\"alex\").exists():\n    User.objects.create_superuser(\"alex\", \"alexandre.stutz@hotmail.com\", \"deplanta1\")\n''')"

create_superuser_all_with_credentials: createsuperuser_user_with_credentials createsuperuser_matchtracker_with_credentials

# Ouvre un shell psql sur la base de données du service matchtracker
psql_matchtracker:
	docker compose exec postgres_matchtracker psql -U shared_db_user matchtracker_service_db

# Ouvre un shell psql sur la base de données du service user
psql_user:
	docker compose exec postgres_user psql -U shared_db_user user_service_db
