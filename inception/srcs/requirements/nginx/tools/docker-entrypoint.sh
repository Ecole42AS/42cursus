#!/bin/sh
echo "NGINX en cours d'initialisation..."
nginx -g 'daemon off;'

#demmarage du serveur en mode foreground carte le container s'arrete si le processus principal s'arrete
