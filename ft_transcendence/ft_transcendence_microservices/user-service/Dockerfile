# FROM python:3.10.12-slim

# WORKDIR /usr/src/app

# COPY requirements.txt .
# RUN pip install --upgrade pip
# RUN pip install --no-cache-dir -r requirements.txt

# COPY . .

# ENV PYTHONUNBUFFERED 1

# CMD ["python", "manage.py", "runserver", "0.0.0.0:8080"]
FROM python:3.10.12-slim

# Définir le répertoire de travail
WORKDIR /usr/src/app

# Installer les dépendances système minimales, incluant curl
RUN apt-get update && apt-get install -y --no-install-recommends \
    curl && \
    rm -rf /var/lib/apt/lists/*

# Installer pip et mettre à jour
RUN pip install --upgrade pip && \
    rm -rf /root/.cache/pip

# Copier requirements.txt et installer les dépendances Python
COPY requirements.txt .
RUN pip install --no-cache-dir -r requirements.txt

# Copier le reste des fichiers de l'application
COPY . .

# Configurer une variable d'environnement pour éviter le buffering
ENV PYTHONUNBUFFERED 1

# Documenter le port exposé
EXPOSE 8080

# Définir la commande de démarrage
CMD ["python", "manage.py", "runserver", "0.0.0.0:8080"]
