import os
from pathlib import Path
import sys
from dotenv import load_dotenv
from datetime import timedelta


# Définir le répertoire de base du service utilisateur
BASE_DIR = Path(__file__).resolve().parent.parent

# Charger les variables d'environnement
load_dotenv(os.path.join(BASE_DIR, '.env'))

# Clé secrète - à sécuriser en production
# SECRET_KEY = 'django-insecure-^96ocy_do_=)*km4l9-m%n1hk&^b-ous4gxw8%09+f9dos010q'
# SECRET_KEY = 'akn1%#!+sh*gzpb#ek_30a=3qag!14&%rj1mz%!uaj3*a1-i*n'
SECRET_KEY = os.getenv("DJANGO_SECRET_KEY", "fallback-secret-key")
JWT_SECRET_KEY = os.getenv("JWT_SECRET_KEY", "my-default-unique-key")
# print(f"JWT_SECRET_KEY: {JWT_SECRET_KEY}")
# print("DJANGO_SECRET_KEY:", os.getenv("DJANGO_SECRET_KEY"))
INTERNAL_API_KEY = '0201d2b222e3d58c5540cb05238d1f85fe964440aa9f0277299ec8011f71d1b4'
# Mode Debug - Désactiver en production
DEBUG = os.getenv("DEBUG", "False").lower() in ("true", "1", "yes")

# Hôtes autorisés
ALLOWED_HOSTS = ['127.0.0.1', 'localhost', 'user_service']

# Applications installées
INSTALLED_APPS = [
    'django.contrib.admin',
    'django.contrib.auth',
    'django.contrib.contenttypes',
    'django.contrib.sessions',
    'django.contrib.messages',
    'django.contrib.staticfiles',
    'rest_framework',
    'rest_framework_simplejwt',
    'corsheaders',
    'user',  # App du service utilisateur
]

# Middleware
MIDDLEWARE = [
    'django.middleware.security.SecurityMiddleware',
    'django.contrib.sessions.middleware.SessionMiddleware',
    'corsheaders.middleware.CorsMiddleware',
    'django.middleware.common.CommonMiddleware',
    'django.middleware.csrf.CsrfViewMiddleware',
    'django.contrib.auth.middleware.AuthenticationMiddleware',
    'django.contrib.messages.middleware.MessageMiddleware',
    'django.middleware.clickjacking.XFrameOptionsMiddleware',
    'user.middleware.UpdateLastActivityMiddleware',  # Middleware spécifique à l'utilisateur
    'user.middleware.JWTValidationMiddleware',
]

# Configuration CORS
CORS_ALLOWED_ORIGINS = [
    "http://localhost:3000",
    "http://127.0.0.1:3000",
    "http://matchtracker-service:8000",  # Autoriser le microservice `matchtracker-service`
    "http://localhost:8000",  # Autoriser localhost pour les tests
]

REST_FRAMEWORK = {
    'DEFAULT_AUTHENTICATION_CLASSES': (
        'user.authentication.EnhancedJWTAuthentication',  # Authentification JWT pour l'API
        'rest_framework.authentication.SessionAuthentication',  # Authentification via sessions (pour l'interface API web)
    ),
    'DEFAULT_PERMISSION_CLASSES': [
        'rest_framework.permissions.IsAuthenticated',  # Requiert une authentification pour les endpoints protégés
    ],
    'DEFAULT_PARSER_CLASSES': (
        'rest_framework.parsers.JSONParser',  # Parser pour JSON (principalement utilisé)
        'rest_framework.parsers.FormParser',  # Supporte les formulaires
        'rest_framework.parsers.MultiPartParser',  # Supporte les fichiers
    ),
    'DEFAULT_RENDERER_CLASSES': (
        'rest_framework.renderers.JSONRenderer',  # Retourne JSON par défaut
        'rest_framework.renderers.BrowsableAPIRenderer',  # Interface web navigable (utile pour le développement)
    ),
}



from datetime import timedelta

SIMPLE_JWT = {
    'ACCESS_TOKEN_LIFETIME': timedelta(minutes=40),
    'REFRESH_TOKEN_LIFETIME': timedelta(days=1),
    'SIGNING_KEY': JWT_SECRET_KEY,  # Chargée depuis .env
    'ALGORITHM': 'HS256',
}

# Configuration des URL racines
ROOT_URLCONF = 'user_service.urls'

# Configuration des templates
TEMPLATES = [
    {
        'BACKEND': 'django.template.backends.django.DjangoTemplates',
        'DIRS': [os.path.join(BASE_DIR, 'templates')],
        'APP_DIRS': True,
        'OPTIONS': {
            'context_processors': [
                'django.template.context_processors.debug',
                'django.template.context_processors.request',
                'django.contrib.auth.context_processors.auth',
                'django.contrib.messages.context_processors.messages',
            ],
        },
    },
]

# Application WSGI
WSGI_APPLICATION = 'user_service.wsgi.application'

if 'test' in sys.argv: 
    DATABASES = {
        'default': {
            'ENGINE': 'django.db.backends.sqlite3',
            'NAME': ':memory:',
        }
    }
else:
#     DATABASES = {
#         'default': {
#             'ENGINE': 'django.db.backends.postgresql',
#             'NAME': 'user_service_db',
#             'USER': 'shared_db_user',
#             'PASSWORD': 'deplanta1',
#             'HOST': 'localhost',
#             'PORT': '5432',
#         }
#    }
    DATABASES = {
        'default': {
            'ENGINE': 'django.db.backends.postgresql',
            'NAME': os.getenv('POSTGRES_DB', 'user_service_db'),
            'USER': os.getenv('POSTGRES_USER', 'shared_db_user'),
            'PASSWORD': os.getenv('POSTGRES_PASSWORD', 'deplanta1'),
            'HOST': os.getenv('POSTGRES_HOST', 'postgres'),
            'PORT': os.getenv('POSTGRES_PORT', '5432'),
        }
    }

# filepath:  /home/alex/Ecole42/42cursus/ft_transcendence/ft_transcendence_microservices/user-service/user_service/settings.py
SESSION_ENGINE = "django.contrib.sessions.backends.db"  # Sessions dans la base de données
# SESSION_ENGINE = "django.contrib.sessions.backends.cache"
# SESSION_CACHE_ALIAS = "default"

# CACHES = {
#     "default": {
#         "BACKEND": "django_redis.cache.RedisCache",
#         "LOCATION": "redis://127.0.0.1:6379/1",  # Adresse de votre serveur Redis
#         "OPTIONS": {
#             "CLIENT_CLASS": "django_redis.client.DefaultClient",
#         }
#     }
# }

SESSION_COOKIE_DOMAIN = "localhost"
SESSION_COOKIE_NAME = "sessionid"  # Nom du cookie de session
SESSION_COOKIE_SAMESITE = "Lax"  # Permet les sous-domaines
SESSION_COOKIE_SECURE = False  # Doit être True en production si HTTPS est utilisé
# SESSION_ENGINE = "django.contrib.sessions.backends.cache"  # Redis pour stocker les sessions
SESSION_ENGINE = "django.contrib.sessions.backends.db"  # Sessions dans la base de données
SESSION_CACHE_ALIAS = "default"  # Utilisation de la configuration cache 'default'



# Modèle utilisateur personnalisé
AUTH_USER_MODEL = 'user.CustomUser'

# Validation des mots de passe
AUTH_PASSWORD_VALIDATORS = [
    {
        'NAME': 'django.contrib.auth.password_validation.UserAttributeSimilarityValidator',
    },
    {
        'NAME': 'django.contrib.auth.password_validation.MinimumLengthValidator',
    },
    {
        'NAME': 'django.contrib.auth.password_validation.CommonPasswordValidator',
    },
    {
        'NAME': 'django.contrib.auth.password_validation.NumericPasswordValidator',
    },
]

# Localisation
LANGUAGE_CODE = 'en-us'
TIME_ZONE = 'Europe/Zurich'
USE_I18N = True
USE_TZ = True

# Configuration des fichiers statiques
STATIC_URL = 'static/'

# Configuration des médias
MEDIA_URL = '/media/'
MEDIA_ROOT = os.path.join(BASE_DIR, 'media')


DEFAULT_AUTO_FIELD = 'django.db.models.BigAutoField'


if 'test' in sys.argv:
    import tempfile
    from django.core.files.storage import FileSystemStorage

    class TemporaryTestStorage(FileSystemStorage):
        def __init__(self, *args, **kwargs):
            super().__init__(location=tempfile.mkdtemp(), *args, **kwargs)

    DEFAULT_FILE_STORAGE = 'user_service.settings.TemporaryTestStorage'

# Configuration du logging
LOGGING = {
    'version': 1,
    'disable_existing_loggers': False,
    'formatters': {
        'verbose': {
            'format': '{levelname} {asctime} {module} {message}',
            'style': '{',
        },
        'simple': {
            'format': '{levelname} {message}',
            'style': '{',
        },
    },
    'handlers': {
        'file': {
            'level': 'DEBUG',
            'class': 'logging.FileHandler',
            'filename': os.path.join(BASE_DIR, 'logs/debug.log'),  # Assurez-vous que le dossier existe
            'formatter': 'verbose',
        },
    },
    'loggers': {
        'django': {
            'handlers': ['file'],
            'level': 'DEBUG',
            'propagate': True,
        },
        'django.request': {
            'handlers': ['file'],
            'level': 'ERROR',
            'propagate': False,
        },
        'django.db.backends': {
            'handlers': ['file'],
            'level': 'ERROR', 
            'propagate': False,
        },
        'matchtracker-service': {
            'handlers': ['file'],
            'level': 'DEBUG', 
           'propagate': True,
        },
        'urllib3': {
            'handlers': ['file'],
            'level': 'DEBUG',
            'propagate': False,
        },
        'requests': {
            'handlers': ['file'],
            'level': 'DEBUG',
            'propagate': False,
        },
        'rest_framework': {
            'handlers': ['file'],
            'level': 'DEBUG',
            'propagate': True,
        },

    },
}

