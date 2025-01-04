FROM python:3.10.12-slim

# Définir le répertoire de travail
WORKDIR /usr/src/app

# Installer les dépendances système nécessaires
RUN apt-get update && apt-get install -y \
    curl \
    iputils-ping \
    --no-install-recommends && \
    rm -rf /var/lib/apt/lists/*

# Copier le fichier requirements.txt et installer les dépendances Python
COPY requirements.txt .
RUN pip install --upgrade pip
RUN pip install --no-cache-dir -r requirements.txt

# Copier le reste des fichiers de l'application
COPY . .

# Définir la variable d'environnement pour que Python n'utilise pas de tampon
ENV PYTHONUNBUFFERED 1

# Commande par défaut pour exécuter l'application
CMD ["python", "manage.py", "runserver", "0.0.0.0:8000"]
