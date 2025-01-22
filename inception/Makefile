# Variables
PATH_DOCKER_COMPOSE = srcs/docker-compose.yml
NAME = inception

# Détection de l'OS et définition des chemins pour les volumes
OS := $(shell uname -s | tr '[:upper:]' '[:lower:]')
ifeq ($(OS),linux)
    DEFAULT_PATH_V_WORDPRESS = ~/data/wordpress
    DEFAULT_PATH_V_MARIADB = ~/data/mariadb
else ifeq ($(OS),darwin)
    DEFAULT_PATH_V_WORDPRESS = /Users/$(USER)/data/wordpress
    DEFAULT_PATH_V_MARIADB = /Users/$(USER)/data/mariadb
endif

# Variables utilisateur (modifiables via la ligne de commande)
PATH_V_WORDPRESS ?= $(DEFAULT_PATH_V_WORDPRESS)
PATH_V_MARIADB ?= $(DEFAULT_PATH_V_MARIADB)
PATH_TO_ENV_FILE ?= srcs/.env
DOCKER_COMPOSE_CMD = docker-compose -f ${PATH_DOCKER_COMPOSE} -p ${NAME}

# Cibles principales
all: prepare down build run

run:
	@$(DOCKER_COMPOSE_CMD) up -d
	@echo "Project is running."

run-daemon:
	@$(DOCKER_COMPOSE_CMD) up -d
	@echo "Running in daemon mode."

down:
	@$(DOCKER_COMPOSE_CMD) down
	@echo "Containers stopped."

stop:
	@$(DOCKER_COMPOSE_CMD) stop
	@echo "Containers stopped without removing them."

build:
	@$(DOCKER_COMPOSE_CMD) build
	@echo "Build completed."

status:
	@$(DOCKER_COMPOSE_CMD) ps
	@echo "Containers status displayed."

logs:
	@$(DOCKER_COMPOSE_CMD) logs -f

# Préparation des volumes et fichiers requis
prepare:
	@test -f $(PATH_TO_ENV_FILE) || (echo "Error: .env file not found at $(PATH_TO_ENV_FILE)"; exit 1)
	@mkdir -p $(PATH_V_WORDPRESS) $(PATH_V_MARIADB)
	@echo "Preparation complete."

# Nettoyage
clean: down
	@docker system prune -a --force
	@echo "Cleanup done."

fclean: down
	@docker system prune -a --volumes --force
	@docker volume rm $$(docker volume ls -q) || true
	@rm -rf $(PATH_V_WORDPRESS) $(PATH_V_MARIADB)
	@echo "Full cleanup done."

re: fclean all

delete-volumes:
	@docker system prune -a --volumes --force
	@docker volume rm $$(docker volume ls -q) || true
	@echo "All volumes deleted."

reload:
	@$(DOCKER_COMPOSE_CMD) down && $(DOCKER_COMPOSE_CMD) up -d
	@echo "Configuration reloaded."

# Tests pour vérifier la conformité du projet
test:
	@echo "Running project tests..."
	# Vérification des conteneurs en cours d'exécution
	@docker ps --format "table {{.Names}}\t{{.Status}}" | grep $(NAME)_nginx && echo "NGINX is running" || (echo "NGINX is not running!" && exit 1)
	@docker ps --format "table {{.Names}}\t{{.Status}}" | grep $(NAME)_mariadb && echo "MariaDB is running" || (echo "MariaDB is not running!" && exit 1)
	@docker ps --format "table {{.Names}}\t{{.Status}}" | grep $(NAME)_wordpress && echo "WordPress is running" || (echo "WordPress is not running!" && exit 1)
	# Test de connexion MariaDB
	@docker exec $(NAME)_mariadb mysqladmin --host=localhost --user=root --password=$$(cat srcs/secrets/db_root_password.txt) ping && echo "MariaDB connection successful" || (echo "MariaDB connection failed" && exit 1)
	# Vérification de l'installation de WordPress
	@docker exec $(NAME)_wordpress wp core is-installed --allow-root && echo "WordPress is correctly installed" || (echo "WordPress installation failed" && exit 1)
	# Test de configuration NGINX
	@docker exec $(NAME)_nginx nginx -t && echo "NGINX configuration is valid" || (echo "NGINX configuration error" && exit 1)
	# Vérification du certificat TLS
	@curl -v --insecure https://login.42.fr 2>&1 | grep "TLS" && echo "TLS configuration is correct" || (echo "TLS configuration failed" && exit 1)
	@echo "All tests passed successfully."

# Arrêt des services locaux pour éviter des conflits avec Docker
stop-services:
ifeq ($(OS),linux)
	@sudo systemctl stop apache2 || true
	@sudo systemctl stop nginx || true
	@sudo systemctl stop mariadb || true
	@sudo systemctl stop mysql || true
else
	@sudo service apache2 stop || true
	@sudo service nginx stop || true
	@sudo service mariadb stop || true
	@sudo service mysql stop || true
endif
	@echo "Local services stopped."

# Déclaration des cibles non liées à des fichiers
.PHONY: all clean fclean re prepare build run down stop logs status reload delete-volumes stop-services test
