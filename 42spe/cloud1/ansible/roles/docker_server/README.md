# Rôle Ansible : docker_server

## 📝 Description

Ce rôle Ansible installe et configure Docker Engine sur Ubuntu 20.04 de manière automatisée et idempotente.

## 🎯 Fonctionnalités

- Installation de Docker Engine (version latest stable)
- Installation de docker compose (plugin v2)
- Configuration du service Docker (démarrage automatique)
- Ajout de l'utilisateur au groupe docker
- Vérification fonctionnelle de l'installation

## 📋 Prérequis

- Système d'exploitation : Ubuntu 20.04 LTS
- Privilèges sudo sur le serveur cible
- Connexion SSH configurée
- Python 3.8+ sur le serveur cible

## 🚀 Utilisation

### Dans un playbook

```yaml
- name: Installation Docker
  hosts: wordpress_servers
  roles:
    - docker_server
```

### Variables disponibles

Aucune variable n'est requise. Le rôle utilise les valeurs par défaut optimales.

## 📦 Packages installés

- `docker-ce` : Docker Community Edition
- `docker-ce-cli` : Interface en ligne de commande Docker
- `containerd.io` : Runtime de conteneurs
- `docker-buildx-plugin` : Plugin pour builds multi-architectures
- `docker-compose-plugin` : Plugin docker compose v2

## ✅ Tests de validation

Le rôle effectue automatiquement les tests suivants :

1. Vérification de la version Docker
2. Vérification de la version docker compose
3. Test fonctionnel avec `hello-world`

## 🔄 Idempotence

Ce rôle est idempotent :
- Première exécution : ~10 changements (installation)
- Exécutions suivantes : ~2 changements (caches APT uniquement)

## 🏗️ Structure

```
docker_server/
└── tasks/
    └── main.yml    # Tâches principales (11 étapes)
```

## 📚 Modules Ansible utilisés

- `apt` - Gestion des packages
- `file` - Gestion des fichiers/dossiers
- `shell` - Exécution de commandes shell
- `service` - Gestion des services systemd
- `user` - Gestion des utilisateurs
- `command` - Exécution de commandes simples
- `debug` - Affichage de messages

## 🔧 Étapes d'installation

1. Mise à jour du cache APT
2. Installation des prérequis
3. Ajout de la clé GPG Docker
4. Ajout du dépôt officiel Docker
5. Installation de Docker Engine
6. Démarrage du service Docker
7. Ajout de l'utilisateur au groupe docker
8. Vérifications