# Définition des couleurs
GREEN = \033[1;92m
RED = \033[1;91m
NC = \033[0m # Réinitialisation des couleurs

# Variables
PATH_DOCKER_COMPOSE = srcs/docker-compose.yml
NAME = inception

    DEFAULT_PATH_V_WORDPRESS = ~/data/wordpress
    DEFAULT_PATH_V_MARIADB = ~/data/mariadb

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
	@sudo rm -rf $(PATH_V_WORDPRESS) $(PATH_V_MARIADB)
	@echo "Full cleanup done."

re: fclean all

delete-volumes:
	@docker system prune -a --volumes --force
	@docker volume rm $$(docker volume ls -q) || true
	@echo "All volumes deleted."

reload:
	@$(DOCKER_COMPOSE_CMD) down && $(DOCKER_COMPOSE_CMD) up -d
	@echo "Configuration reloaded."

test:
	@echo "Running project tests..."

	# Vérification des conteneurs en cours d'exécution
	@docker ps --format "table {{.Names}}\t{{.Status}}" | grep nginx && echo "$(GREEN)NGINX is running$(NC)" || (echo "$(RED)NGINX is not running!$(NC)" && exit 1)
	@docker ps --format "table {{.Names}}\t{{.Status}}" | grep mariadb && echo "$(GREEN)MariaDB is running$(NC)" || (echo "$(RED)MariaDB is not running!$(NC)" && exit 1)
	@docker ps --format "table {{.Names}}\t{{.Status}}" | grep wordpress && echo "$(GREEN)WordPress is running$(NC)" || (echo "$(RED)WordPress is not running!$(NC)" && exit 1)


	# Vérification du redémarrage automatique des conteneurs
	@docker inspect --format '{{.HostConfig.RestartPolicy.Name}}' nginx | grep "on-failure" && echo "$(GREEN)NGINX restart policy is correct$(NC)" || (echo "$(RED)NGINX restart policy is incorrect$(NC)" && exit 1)
	@docker inspect --format '{{.HostConfig.RestartPolicy.Name}}' mariadb | grep "unless-stopped" && echo "$(GREEN)MariaDB restart policy is correct$(NC)" || (echo "$(RED)MariaDB restart policy is incorrect$(NC)" && exit 1)
	@docker inspect --format '{{.HostConfig.RestartPolicy.Name}}' wordpress | grep "on-failure" && echo "$(GREEN)WordPress restart policy is correct$(NC)" || (echo "$(RED)WordPress restart policy is incorrect$(NC)" && exit 1)


	# Vérification des permissions des fichiers sensibles
	@docker exec wordpress sh -c '[ "$$(stat -c %a /var/www/wordpress/wp-config.php)" = "600" ] && echo "$(GREEN)wp-config.php is secured$(NC)" || (echo "$(RED)wp-config.php is accessible$(NC)" && exit 1)'



	# Test de connexion MariaDB
	@docker exec mariadb sh -c 'mysqladmin ping -h127.0.0.1 -uroot -p"$$MARIADB_ROOT_PASSWORD"' && echo "$(GREEN)MariaDB connection successful$(NC)" || (echo "$(RED)MariaDB connection failed$(NC)" && exit 1)

	# Vérification de l'installation de WordPress
	@docker exec wordpress sh -c "wp core is-installed --allow-root --path=/var/www/wordpress" && echo "$(GREEN)WordPress is correctly installed$(NC)" || (echo "$(RED)WordPress installation failed$(NC)" && exit 1)

	# Vérification de la présence du fichier de configuration de WordPress
	@docker exec wordpress sh -c "[ -f /var/www/wordpress/wp-config.php ]" && echo "$(GREEN)WordPress configuration file exists$(NC)" || (echo "$(RED)WordPress config file missing$(NC)" && exit 1)

	# Vérification des volumes persistants
	@docker volume ls | grep "wordpress" && echo "$(GREEN)WordPress volume exists$(NC)" || (echo "$(RED)WordPress volume is missing$(NC)" && exit 1)
	@docker volume ls | grep "mariadb" && echo "$(GREEN)MariaDB volume exists$(NC)" || (echo "$(RED)MariaDB volume is missing$(NC)" && exit 1)

	# Vérification de la taille des volumes
	@docker exec wordpress sh -c "du -sh /var/www/wordpress/wp-content | awk '\$$1 != \"0\" {print \"$(GREEN)WordPress content exists$(NC)\"} END {if (\$$1 == \"0\") print \"$(RED)WordPress content is empty$(NC)\"; exit (\$$1 == \"0\")} '"


	# Vérification des tables WordPress dans MariaDB
	@docker exec mariadb sh -c 'mysql -u root -p"$$MARIADB_ROOT_PASSWORD" -e "USE db_wordpress; SHOW TABLES;"' | grep "wp_posts" && echo "$(GREEN)WordPress database configured correctly$(NC)" || (echo "$(RED)WordPress database configuration error$(NC)" && exit 1)

	# Vérification de l'existence de l'utilisateur WordPress
	@docker exec wordpress sh -c "wp user list --allow-root --path=/var/www/wordpress" | grep "$(WP_ADMIN_USER)" && echo "$(GREEN)WordPress admin user exists$(NC)" || (echo "$(RED)WordPress admin user is missing$(NC)" && exit 1)

	# Vérification du réseau Docker
	@docker network inspect inception_inception | grep "nginx" && echo "$(GREEN)NGINX is connected to the network$(NC)" || (echo "$(RED)NGINX is not connected to the network$(NC)" && exit 1)
	@docker network inspect inception_inception | grep "mariadb" && echo "$(GREEN)MariaDB is connected to the network$(NC)" || (echo "$(RED)MariaDB is not connected to the network$(NC)" && exit 1)
	@docker network inspect inception_inception | grep "wordpress" && echo "$(GREEN)WordPress is connected to the network$(NC)" || (echo "$(RED)WordPress is not connected to the network$(NC)" && exit 1)

	# Vérification des permissions des fichiers WordPress
	@docker exec wordpress sh -c "ls -ld /var/www/wordpress/wp-content" | grep "drwxr-xr-x" && echo "$(GREEN)WordPress file permissions are correct$(NC)" || (echo "$(RED)WordPress file permissions are incorrect$(NC)" && exit 1)

	# Vérification des logs NGINX
	@docker logs nginx 2>&1 | grep "error" && (echo "$(RED)NGINX errors detected$(NC)" && exit 1) || echo "$(GREEN)No critical NGINX errors$(NC)"

	# Vérification des variables d'environnement dans WordPress
	@docker exec wordpress printenv | grep "WP_ADMIN_USER" && echo "$(GREEN)Environment variables are correctly loaded$(NC)" || (echo "$(RED)Environment variables are not loaded$(NC)" && exit 1)

	# Test de configuration NGINX
	@docker exec nginx nginx -t && echo "$(GREEN)NGINX configuration is valid$(NC)" || (echo "$(RED)NGINX configuration error$(NC)" && exit 1)

	# Vérification du certificat TLS et de l'accès au site
	@DOMAIN_NAME=astutz.42.fr; curl -k -L -o /dev/null -s -w "%{http_code}" https://$$DOMAIN_NAME | grep "200" && echo "$(GREEN)TLS configuration is correct$(NC)" || (echo "$(RED)TLS configuration failed$(NC)" && exit 1)

	# Vérification de l'accès à une page spécifique de WordPress (ex: Hello World post)
	@DOMAIN_NAME=astutz.42.fr; curl -k -L -o /dev/null -s -w "%{http_code}" "https://$$DOMAIN_NAME/?p=1" | grep "200" && echo "$(GREEN)WordPress page is accessible$(NC)" || (echo "$(RED)WordPress page access failed$(NC)" && exit 1)

	# Vérification de la création d'un post via WP-CLI
	@docker exec wordpress wp post create --post_title='Test Post' --post_content='This is a test.' --post_status=publish --allow-root --path=/var/www/wordpress && echo "$(GREEN)WordPress post creation successful$(NC)" || (echo "$(RED)WordPress post creation failed$(NC)" && exit 1)

	@echo "$(GREEN)All tests passed successfully.$(NC)"

# Arrêt des services locaux pour éviter des conflits avec Docker
stop-services:
	@sudo systemctl stop apache2 || true
	@sudo systemctl stop nginx || true
	@sudo systemctl stop mariadb || true
	@sudo systemctl stop mysql || true
	@echo "Local services stopped."

# Déclaration des cibles non liées à des fichiers
.PHONY: all clean fclean re prepare build run down stop logs status reload delete-volumes stop-services test
