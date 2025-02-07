from pathlib import Path
import os
import sys
from dotenv import load_dotenv
import logging

logger = logging.getLogger("matchtracker-service")


BASE_DIR = Path(__file__).resolve().parent.parent

load_dotenv(os.path.join(BASE_DIR, ".env"))
# USER_SERVICE_URL = "http://localhost:8080/api/user"
# USER_SERVICE_URL = "http://user_service:8000/api/user"
USER_SERVICE_URL = os.getenv("USER_SERVICE_URL", "http://localhost:8080/api/user")
BASE_USER_SERVICE_URL = os.getenv("BASE_USER_SERVICE_URL", "http://localhost:8080")
SERVICE_USERNAME = os.getenv("SERVICE_USERNAME", "default_user")
SERVICE_PASSWORD = os.getenv("SERVICE_PASSWORD", "default_password")

# SECRET_KEY = 'django-insecure-4uhyw(pjk&*i^ir70!^@xd!skh9$^#$mm^lt+3kc-07#_bqvn&'
SECRET_KEY = os.getenv("DJANGO_SECRET_KEY", "fallback-secret-key")
JWT_SECRET_KEY = os.getenv("JWT_SECRET_KEY", "my-default-unique-key")
INTERNAL_API_KEY = '0201d2b222e3d58c5540cb05238d1f85fe964440aa9f0277299ec8011f71d1b4'
# DEBUG = True
DEBUG = os.getenv("DEBUG", "False").lower() in ("true", "1", "yes")
ALLOWED_HOSTS = ['localhost', '127.0.0.1', 'matchtracker_service', '172.19.0.4', '172.19.0.3']
#allow all hosts
# ALLOWED_HOSTS = ['*']
# CORS_ALLOW_HEADERS = [
#     'content-type',
#     'authorization',
#     'x-requested-with',
# ]


INSTALLED_APPS = [
    'django.contrib.auth',
    'django.contrib.contenttypes',
    'django.contrib.sessions',
    'django.contrib.messages',
    'django.contrib.staticfiles',
    'rest_framework',
    'rest_framework_simplejwt',
    'corsheaders',
    'channels',
    'game',
]


MIDDLEWARE = [
    'django.middleware.security.SecurityMiddleware',
    'django.contrib.sessions.middleware.SessionMiddleware',
    'corsheaders.middleware.CorsMiddleware',
    # 'django.middleware.common.CommonMiddleware',
    'django.middleware.csrf.CsrfViewMiddleware',
    'django.contrib.auth.middleware.AuthenticationMiddleware',
    'django.contrib.messages.middleware.MessageMiddleware',
    'django.middleware.clickjacking.XFrameOptionsMiddleware',
    'game.middleware.JWTMiddleware',
]

# allow all origins
# CORS_ALLOW_ALL_ORIGINS = True

CORS_ALLOWED_ORIGINS = [
    "http://localhost:3000",
    "http://localhost:8000",
    "http://127.0.0.1:3000",
    "http://127.0.0.1:8000",
    "http://matchtracker-service:8000",
]

REST_FRAMEWORK = {
    'DEFAULT_AUTHENTICATION_CLASSES': (
        # 'rest_framework_simplejwt.authentication.JWTAuthentication',
        'game.authentication.JWTAuthentication',
    ),
    'DEFAULT_PERMISSION_CLASSES': [
        'rest_framework.permissions.IsAuthenticated',  # Requiert JWT pour accéder aux endpoints protégés
    ],
    'EXCEPTION_HANDLER': 'rest_framework.views.exception_handler',
    'DEFAULT_RENDERER_CLASSES': (
        'rest_framework.renderers.JSONRenderer',
    ),
}

from datetime import timedelta

SIMPLE_JWT = {
    'ACCESS_TOKEN_LIFETIME': timedelta(minutes=40),
    'REFRESH_TOKEN_LIFETIME': timedelta(days=1),
    'SIGNING_KEY': os.getenv("JWT_SECRET_KEY", "a33d83c0f3be73db53d15b0a71c3e12b521b03ca0d300767b79722cd1c11940d"),
    'ALGORITHM': 'HS256',
}

logger.debug(f"Clé JWT utilisée pour la validation : {SIMPLE_JWT['SIGNING_KEY']}")  # Ajout ici



ROOT_URLCONF = 'matchtracker_service.urls'

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

ASGI_APPLICATION = "matchtracker_service.asgi.application"
WSGI_APPLICATION = 'matchtracker_service.wsgi.application'

if 'test' in sys.argv:
    DATABASES = {
        'default': {
            'ENGINE': 'django.db.backends.sqlite3',
            'NAME': ':memory:',
        }
    }
else:
    # DATABASES = {
    #     'default': {
    #         'ENGINE': 'django.db.backends.postgresql',
    #         'NAME': 'matchtracker_service_db',
    #         'USER': 'shared_db_user',
    #         'PASSWORD': 'deplanta1',
    #         'HOST': 'localhost',
    #         'PORT': '5432',
    #     }
    # }
    DATABASES = {
        'default': {
            'ENGINE': 'django.db.backends.postgresql',
            'NAME': os.getenv('POSTGRES_DB', 'matchtracker_service_db'),
            'USER': os.getenv('POSTGRES_USER', 'shared_db_user'),
            'PASSWORD': os.getenv('POSTGRES_PASSWORD', 'deplanta1'),
            'HOST': os.getenv('POSTGRES_HOST', 'postgres'),
            'PORT': os.getenv('POSTGRES_PORT', '5432'),
        }
    }
    # DATABASES = {
    #     'default': {
    #         'ENGINE': 'django.db.backends.postgresql',
    #         'NAME': 'matchtracker_service_db',
    #         'USER': 'shared_db_user',
    #         'PASSWORD': 'deplanta1',
    #         'HOST': 'postgres',  # Remplacez localhost par le nom du service PostgreSQL dans Docker
    #         'PORT': '5432',
    #     }
    # }


AUTH_PASSWORD_VALIDATORS = [
    {'NAME': 'django.contrib.auth.password_validation.UserAttributeSimilarityValidator',},
    {'NAME': 'django.contrib.auth.password_validation.MinimumLengthValidator',},
    {'NAME': 'django.contrib.auth.password_validation.CommonPasswordValidator',},
    {'NAME': 'django.contrib.auth.password_validation.NumericPasswordValidator',},
]

LANGUAGE_CODE = 'en-us'
TIME_ZONE = 'Europe/Zurich'
USE_I18N = True
USE_TZ = True

STATIC_URL = 'static/'

DEFAULT_AUTO_FIELD = 'django.db.models.BigAutoField'

if 'test' in sys.argv:
    import tempfile
    from django.core.files.storage import FileSystemStorage

    class TemporaryTestStorage(FileSystemStorage):
        def __init__(self, *args, **kwargs):
            super().__init__(location=tempfile.mkdtemp(), *args, **kwargs)

    DEFAULT_FILE_STORAGE = 'matchtracker_service.settings.TemporaryTestStorage'


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
            'level': 'DEBUG',  # Niveau minimum des logs
            'class': 'logging.FileHandler',
            'filename': os.path.join(BASE_DIR, 'logs/debug.log'),  # Chemin du fichier de log
            'formatter': 'verbose',
        },
    },
    'loggers': {
        # Logger principal pour Django
        'django': {
            'handlers': ['file'],
            'level': 'INFO',  # Réduire le niveau global des logs Django
            'propagate': True,
        },
        # Logger pour les erreurs HTTP de Django
        'django.request': {
            'handlers': ['file'],
            'level': 'ERROR',
            'propagate': False,
        },
        # Logger pour les requêtes à la base de données
        'django.db.backends': {
            'handlers': ['file'],
            'level': 'ERROR',
            'propagate': False,
        },
        # Logger personnalisé pour `Matchtracker`
        'matchtracker-service': {
            'handlers': ['file'],
            'level': 'DEBUG',  # Capturer tous les détails
            'propagate': True,
        },
        # Ajoutez une entrée spécifique pour vos logs websocket, si vous souhaitez les isoler
        'matchtracker-service.websocket': {
            'handlers': ['file'],
            'level': 'DEBUG',
            'propagate': False,  # Vous pouvez le mettre à True si vous voulez que ces logs remontent au logger racine
        },
        # Logger pour les bibliothèques réseau (comme `urllib3`)
        'urllib3': {
            'handlers': ['file'],
            'level': 'INFO',  # Réduire les logs réseau
            'propagate': False,
        },
        # Logger pour la bibliothèque `requests`
        'requests': {
            'handlers': ['file'],
            'level': 'INFO',
            'propagate': False,
        },
        # Logger pour Django REST Framework
        'rest_framework': {
            'handlers': ['file'],
            'level': 'INFO',  # Réduire les logs REST Framework
            'propagate': True,
        },
        # Logger pour `django.utils.autoreload` (masquer les messages DEBUG inutiles)
        'django.utils.autoreload': {
            'handlers': ['file'],
            'level': 'WARNING',  # Ignorer les logs DEBUG
            'propagate': False,
        },
        'utils': {
            'handlers': ['file'],
            'level': 'DEBUG',  # Capturer tous les détails
            'propagate': False,  # Éviter de transmettre les logs aux loggers parents
        },
        '': {  # Logger racine
            'handlers': ['file'],
            'level': 'DEBUG',  # Capturer tous les logs par défaut
            'propagate': True,
        },
    },
}



CHANNEL_LAYERS = {
    'default': {
        'BACKEND': 'channels_redis.core.RedisChannelLayer',
        'CONFIG': {
            "hosts": [("127.0.0.1", 6379)],
        },
    },
}

# filepath: /home/alex/Ecole42/42cursus/ft_transcendence/ft_transcendence_microservices/matchtracker-service/matchtracker_service/settings.py
SESSION_ENGINE = "django.contrib.sessions.backends.db"
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
