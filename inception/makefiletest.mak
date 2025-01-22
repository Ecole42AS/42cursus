# Variables de configuration
PATH_DOCKER_COMPOSE = srcs/docker-compose.yml
NAME = inception

# Détection de l'OS et définition des chemins des volumes
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
    DEFAULT_PATH_V_WORDPRESS = ~/data/wordpress
    DEFAULT_PATH_V_MARIADB = ~/data/mariadb
else ifeq ($(UNAME_S),Darwin)  # macOS
    DEFAULT_PATH_V_WORDPRESS = /Users/astutz/data/wordpress
    DEFAULT_PATH_V_MARIADB = /Users/astutz/data/mariadb
endif

PATH_V_WORDPRESS ?= $(DEFAULT_PATH_V_WORDPRESS)
PATH_V_MARIADB ?= $(DEFAULT_PATH_V_MARIADB)
PATH_TO_ENV_FILE ?= srcs/.env

# Définition des couleurs pour la sortie
GREEN=\033[0;32m
RED=\033[0;31m
NC=\033[0m # No Color

# Définition des conteneurs
NGINX_CONTAINER=nginx
WORDPRESS_CONTAINER=wordpress
MARIADB_CONTAINER=mariadb

# Cibles principales
all: check-env prepare down build run test-services

run:
	@echo "$(GREEN)Lancement des conteneurs...$(NC)"
	docker-compose -f ${PATH_DOCKER_COMPOSE} -p ${NAME} up

run-daemon:
	@echo "$(GREEN)Lancement des conteneurs en arrière-plan...$(NC)"
	docker-compose -f ${PATH_DOCKER_COMPOSE} -p ${NAME} up -d

down:
	@echo "$(RED)Arrêt des conteneurs...$(NC)"
	docker-compose -f ${PATH_DOCKER_COMPOSE} -p ${NAME} down

prepare:
	@if [ ! -f ${PATH_TO_ENV_FILE} ]; then \
		echo "$(RED)Erreur: .env introuvable à ${PATH_TO_ENV_FILE}$(NC)"; \
		exit 1; \
	fi
	@if [ ! -d ${PATH_V_WORDPRESS} ]; then \
		mkdir -p ${PATH_V_WORDPRESS}; \
	fi
	@if [ ! -d ${PATH_V_MARIADB} ]; then \
		mkdir -p ${PATH_V_MARIADB}; \
	fi

build:
	@echo "$(GREEN)Construction des images Docker...$(NC)"
	docker-compose -f ${PATH_DOCKER_COMPOSE} -p ${NAME} build

clean: down
	@echo "$(RED)Suppression des conteneurs et volumes...$(NC)"
	docker system prune -af --volumes

re: clean
	@echo "$(RED)Redémarrage des conteneurs...$(NC)"
	sleep 5
	docker-compose -f ${PATH_DOCKER_COMPOSE} -p ${NAME} up -d
	@echo "$(GREEN)Redémarrage terminé avec succès$(NC)"


# Vérification de l'environnement
check-env:
	@docker --version > /dev/null 2>&1 || (echo "$(RED)Docker non installé$(NC)"; exit 1)
	@docker-compose --version > /dev/null 2>&1 || (echo "$(RED)Docker Compose non installé$(NC)"; exit 1)
	@echo "$(GREEN)Environnement Docker OK$(NC)"

# Tests de vérification des services sans fichiers secrets
check-containers:
	@echo "$(GREEN)Vérification des conteneurs actifs:$(NC)"
	@docker ps --format "table {{.Names}}\t{{.Status}}"

test-nginx-wordpress:
	@docker exec $(NGINX_CONTAINER) curl -I wordpress:9000 > /dev/null 2>&1 && echo "$(GREEN)Connexion NGINX -> WordPress OK$(NC)" || echo "$(RED)Erreur connexion NGINX -> WordPress$(NC)"

test-wordpress-mariadb:
	@docker exec $(WORDPRESS_CONTAINER) mysql -hmariadb -u$$MYSQL_USER -p$$MYSQL_PASSWORD -e "SHOW DATABASES;" > /dev/null 2>&1 && echo "$(GREEN)Connexion WordPress -> MariaDB OK$(NC)" || echo "$(RED)Erreur connexion WordPress -> MariaDB$(NC)"

test-nginx-config:
	@docker exec $(NGINX_CONTAINER) nginx -t && echo "$(GREEN)Configuration NGINX OK$(NC)" || echo "$(RED)Erreur dans la configuration NGINX$(NC)"

check-nginx-port:
	@docker exec $(NGINX_CONTAINER) ss -tuln | grep ':443' > /dev/null 2>&1 && echo "$(GREEN)Port 443 ouvert sur NGINX$(NC)" || echo "$(RED)Port 443 non ouvert sur NGINX$(NC)"

check-wordpress-files:
	@docker exec $(WORDPRESS_CONTAINER) test -f /var/www/html/wp-config.php && echo "$(GREEN)wp-config.php présent$(NC)" || echo "$(RED)wp-config.php manquant$(NC)"

check-volumes:
	@docker volume inspect srcs_wordpress_data && echo "$(GREEN)Volume WordPress OK$(NC)" || echo "$(RED)Volume WordPress manquant$(NC)"
	@docker volume inspect srcs_mariadb_data && echo "$(GREEN)Volume MariaDB OK$(NC)" || echo "$(RED)Volume MariaDB manquant$(NC)"

test-web-access:
	@docker exec $(NGINX_CONTAINER) curl -k https://localhost > /dev/null 2>&1 && echo "$(GREEN)Site accessible$(NC)" || echo "$(RED)Site inaccessible$(NC)"

test-all: check-containers test-nginx-wordpress test-wordpress-mariadb check-nginx-port test-nginx-config check-wordpress-files test-web-access check-volumes

# Commande d'aide
help:
	@echo "$(GREEN)Commandes disponibles :$(NC)"
	@echo "  all                 - Construire et démarrer les conteneurs"
	@echo "  check-env           - Vérifier l'environnement"
	@echo "  test-all            - Exécuter tous les tests"
	@echo "  clean               - Nettoyer les conteneurs et volumes"
	@echo "  re                  - Recréer l'environnement"
	@echo "  logs-nginx          - Afficher les logs de NGINX"
	@echo "  stop                - Arrêter tous les conteneurs"

.PHONY: all clean re stop run run-daemon down build prepare check-env test-all help
