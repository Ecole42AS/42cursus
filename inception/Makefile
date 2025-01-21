PATH_DOCKER_COMPOSE = srcs/docker-compose.yml
DOCKER_COMPOSE_FILE = srcs/docker-compose.yml
NAME = inception

# Détection de l'OS et définition des chemins
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
    DEFAULT_PATH_V_WORDPRESS = ~/data/wordpress
    DEFAULT_PATH_V_MARIADB = ~/data/mariadb
else ifeq ($(UNAME_S),Darwin)  # macOS
    DEFAULT_PATH_V_WORDPRESS = /Users/cmansey/data/wordpress
    DEFAULT_PATH_V_MARIADB = /Users/cmansey/data/mariadb
endif

PATH_V_WORDPRESS ?= $(DEFAULT_PATH_V_WORDPRESS)
PATH_V_MARIADB ?= $(DEFAULT_PATH_V_MARIADB)
PATH_TO_ENV_FILE ?= srcs/.env

all : prepare down build run

run:
	docker-compose -f ${PATH_DOCKER_COMPOSE} -p ${NAME} up

run-daemon:
	docker-compose -f ${PATH_DOCKER_COMPOSE} -p ${NAME} up -d

down:
	docker-compose -f ${PATH_DOCKER_COMPOSE} -p ${NAME} down

stop:
	docker-compose -f ${PATH_DOCKER_COMPOSE} -p ${NAME} stop

prepare:
	if [ ! -f ${PATH_TO_ENV_FILE} ]; then \
		echo "Error: .env file not found at ${PATH_TO_ENV_FILE}"; \
		exit 1; \
	fi
	if [ ! -d ${PATH_V_WORDPRESS} ]; then \
		mkdir -p ${PATH_V_WORDPRESS}; \
	fi
	if [ ! -d ${PATH_V_MARIADB} ]; then \
		mkdir -p ${PATH_V_MARIADB}; \
	fi

build:
	docker-compose -f ${PATH_DOCKER_COMPOSE} -p ${NAME} build

clean: down
	docker system prune -a

fclean: down
	docker system prune -a --volumes
	docker volume rm $$(docker volume ls -q)
	sudo rm -rf ~/data

re: fclean all

delete-volumes :
	docker system prune -a --volumes
	docker volume rm $$(docker volume ls -q)

stop-services:
ifeq ($(IS_LINUX),true)
	sudo systemctl stop apache2 || true
	sudo systemctl stop nginx || true
	sudo systemctl stop mariadb || true
	sudo systemctl stop mysql || true
	else
	sudo service nginx stop
	sudo service mariadb stop
	sudo service apache2 stop
	sudo service mysql stop
endif

.PHONY: all clean fclean re status stop run run-daemon down build prepare delete-volumes
