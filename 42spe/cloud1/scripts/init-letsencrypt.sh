#!/bin/bash

# ===================================
# Script pour obtenir des certificats Let's Encrypt
# Usage: ./init-letsencrypt.sh votre-domaine.com votre@email.com
# ===================================

# Vérifier les arguments
if [ "$#" -ne 2 ]; then
    echo "Usage: $0 <domaine> <email>"
    echo "Exemple: $0 monprojet.duckdns.org admin@example.com"
    exit 1
fi

DOMAIN=$1
EMAIL=$2

echo "🔒 Initialisation Let's Encrypt pour $DOMAIN"
echo "================================================"
echo ""

# =============================
# Étape 1 : Mettre à jour nginx.conf avec le vrai domaine
# =============================
echo "📝 Étape 1 : Configuration du domaine dans nginx.conf"

# Remplacer server_name _ par le vrai domaine
sed -i "s/server_name _;/server_name $DOMAIN;/g" nginx/nginx.conf

# Remplacer example.com par le vrai domaine dans les chemins de certificats
sed -i "s/example.com/$DOMAIN/g" nginx/nginx.conf

echo "✅ nginx.conf mis à jour avec le domaine $DOMAIN"
echo ""

# =============================
# Étape 2 : Créer une config Nginx temporaire (sans SSL)
# =============================
echo "📝 Étape 2 : Création d'une config temporaire (HTTP uniquement)"

cat > nginx/nginx-temp.conf << EOF
# Configuration temporaire pour obtenir les certificats
server {
    listen 80;
    server_name $DOMAIN;
    
    # Challenge ACME pour Let's Encrypt
    location /.well-known/acme-challenge/ {
        root /var/www/certbot;
    }
    
    # Temporairement accessible en HTTP (le temps d'obtenir les certs)
    location / {
        proxy_pass http://wordpress:80;
        proxy_set_header Host \$host;
        proxy_set_header X-Real-IP \$remote_addr;
    }
}
EOF

# Remplacer temporairement la config Nginx
mv nginx/nginx.conf nginx/nginx-full.conf
mv nginx/nginx-temp.conf nginx/nginx.conf

echo "✅ Configuration temporaire créée"
echo ""

# =============================
# Étape 3 : Démarrer Nginx avec la config temporaire
# =============================
echo "🚀 Étape 3 : Démarrage de Nginx (HTTP uniquement)"

docker compose up -d nginx
sleep 5

echo "✅ Nginx démarré"
echo ""

# =============================
# Étape 4 : Obtenir les certificats avec Certbot
# =============================
echo "🔐 Étape 4 : Obtention des certificats Let's Encrypt"
echo "Cela peut prendre quelques secondes..."
echo ""

docker compose run --rm --entrypoint certbot certbot certonly \
    --webroot \
    --webroot-path=/var/www/certbot \
    --email $EMAIL \
    --agree-tos \
    --no-eff-email \
    --staging \
    -d $DOMAIN

# Vérifier si la commande a réussi
if [ $? -eq 0 ]; then
    echo ""
    echo "✅ Certificats obtenus avec succès !"
    echo ""
    
    # =============================
    # Étape 5 : Restaurer la config complète avec HTTPS
    # =============================
    echo "📝 Étape 5 : Restauration de la configuration HTTPS"
    
    mv nginx/nginx-full.conf nginx/nginx.conf
    
    echo "✅ Configuration HTTPS restaurée"
    echo ""
    
    # =============================
    # Étape 6 : Redémarrer Nginx avec HTTPS
    # =============================
    echo "🔄 Étape 6 : Redémarrage de Nginx avec HTTPS"
    
    docker compose restart nginx
    
    echo ""
    echo "================================================"
    echo "✅ HTTPS configuré avec succès !"
    echo ""
    echo "📌 Prochaines étapes :"
    echo "   1. Vérifier : https://$DOMAIN/"
    echo "   2. Vérifier : https://$DOMAIN/phpmyadmin"
    echo "   3. Le renouvellement automatique est configuré (tous les 12h)"
    echo ""
    echo "🔒 Vos certificats sont dans : /var/lib/docker/volumes/cloud1_certbot_certs"
    echo ""
else
    echo ""
    echo "❌ Erreur lors de l'obtention des certificats"
    echo ""
    echo "🔍 Vérifications :"
    echo "   1. Votre domaine $DOMAIN pointe-t-il vers cette IP ?"
    echo "   2. Le port 80 est-il ouvert sur votre pare-feu/Azure NSG ?"
    echo "   3. Nginx est-il bien accessible : curl http://$DOMAIN/.well-known/acme-challenge/test"
    echo ""
    echo "📋 Logs Certbot :"
    docker compose logs certbot
    echo ""
    
    # Restaurer la config quand même
    mv nginx/nginx-full.conf nginx/nginx.conf
    
    exit 1
fi
