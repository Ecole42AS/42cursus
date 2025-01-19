# Définition des couleurs pour la sortie
GREEN=\033[0;32m
RED=\033[0;31m
NC=\033[0m # No Color

# Définition des conteneurs
NGINX_CONTAINER=nginx_container
WORDPRESS_CONTAINER=wordpress_container
MARIADB_CONTAINER=mariadb_container

all:
	@echo "$(GREEN)Starting all containers...$(NC)"
	docker-compose up --build -d

check-containers:
	@echo "$(GREEN)Checking running containers:$(NC)"
	@docker ps --format "table {{.Names}}\t{{.Status}}"

logs-nginx:
	docker logs $(NGINX_CONTAINER) --tail=50

logs-wordpress:
	docker logs $(WORDPRESS_CONTAINER) --tail=50

logs-mariadb:
	docker logs $(MARIADB_CONTAINER) --tail=50

test-nginx-wordpress:
	@echo "$(GREEN)Testing NGINX to WordPress connection:$(NC)"
	@docker exec $(NGINX_CONTAINER) curl -I wordpress:9000 || echo "$(RED)WordPress non accessible depuis NGINX$(NC)"

test-wordpress-mariadb:
	docker exec $(WORDPRESS_CONTAINER) mysql -hmariadb -u$$(cat secrets/db_user.txt) -p$$(cat secrets/db_password.txt) -e "SHOW TABLES;" || echo "$(RED)MariaDB non accessible depuis WordPress$(NC)"

test-nginx-config:
	docker exec $(NGINX_CONTAINER) nginx -t || echo "$(RED)Erreur dans la configuration NGINX$(NC)"

check-nginx-port:
	docker exec $(NGINX_CONTAINER) ss -tuln | grep ':443' || echo "$(RED)Port 443 non ouvert sur NGINX$(NC)"

check-wordpress-files:
	docker exec $(WORDPRESS_CONTAINER) test -f /var/www/html/wp-config.php && echo "$(GREEN)wp-config.php trouvé$(NC)" || echo "$(RED)wp-config.php manquant$(NC)"

check-nginx-certificates:
	docker exec $(NGINX_CONTAINER) test -f /etc/nginx/ssl/nginx.crt && echo "$(GREEN)Certificat SSL trouvé$(NC)" || echo "$(RED)Certificat SSL manquant$(NC)"

check-mariadb:
	docker exec $(MARIADB_CONTAINER) mysql -uroot -p$$(cat secrets/db_root_password.txt) -e "SHOW DATABASES;" | grep wordpress || echo "$(RED)Base de données WordPress non trouvée$(NC)"

check-volumes:
	docker volume inspect srcs_wordpress_data && echo "$(GREEN)Volume WordPress OK$(NC)" || echo "$(RED)Volume WordPress manquant$(NC)"
	docker volume inspect srcs_mariadb_data && echo "$(GREEN)Volume MariaDB OK$(NC)" || echo "$(RED)Volume MariaDB manquant$(NC)"

test-web-access:
	docker exec $(NGINX_CONTAINER) curl -k https://localhost || echo "$(RED)Le site web WordPress n'est pas accessible$(NC)"

clean:
	@echo "$(RED)Stopping and removing containers and volumes...$(NC)"
	docker-compose down -v
	docker system prune -af --volumes

clean-all:
	@echo "$(RED)Removing all containers, images, and volumes...$(NC)"
	docker-compose down -v --rmi all --remove-orphans
	docker system prune -af --volumes

clean-images:
	@echo "$(RED)Removing all Docker images...$(NC)"
	docker rmi -f $$(docker images -q)

clean-containers:
	@echo "$(RED)Removing all stopped containers...$(NC)"
	docker rm -f $$(docker ps -aq)

restart:
	@echo "$(RED)Restarting all containers...$(NC)"
	docker-compose down
	@echo "Attente de 5 secondes avant de redémarrer..."
	sleep 5
	docker-compose up --build -d

stop:
	@echo "$(RED)Stopping all containers...$(NC)"
	docker-compose down

test-all: check-containers test-nginx-wordpress test-wordpress-mariadb check-nginx-port test-nginx-config check-mariadb check-wordpress-files test-web-access check-volumes

help:
	@echo "$(GREEN)Usage: make [target]$(NC)"
	@echo "$(GREEN)Targets:$(NC)"
	@echo "  all                 - Build and start all containers"
	@echo "  check-containers    - List running containers"
	@echo "  logs-nginx          - Show the last logs of NGINX"
	@echo "  logs-wordpress      - Show the last logs of WordPress"
	@echo "  logs-mariadb        - Show the last logs of MariaDB"
	@echo "  test-all            - Run all tests"
	@echo "  restart             - Restart all containers"
	@echo "  clean               - Stop and remove all containers and volumes"
	@echo "  clean-all           - Remove containers, images, and volumes"
	@echo "  clean-images        - Remove all Docker images"
	@echo "  clean-containers    - Remove all stopped containers"
	@echo "  stop                - Stop all running containers"
