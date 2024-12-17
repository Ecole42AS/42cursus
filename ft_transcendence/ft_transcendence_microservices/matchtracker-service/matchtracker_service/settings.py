from pathlib import Path
import os
import sys
from dotenv import load_dotenv


BASE_DIR = Path(__file__).resolve().parent.parent
USER_SERVICE_URL = "http://user-service:8080/api/user"

# SECRET_KEY = 'django-insecure-4uhyw(pjk&*i^ir70!^@xd!skh9$^#$mm^lt+3kc-07#_bqvn&'
SECRET_KEY = os.getenv("DJANGO_SECRET_KEY", "fallback-secret-key")
JWT_SECRET_KEY = os.getenv("JWT_SECRET_KEY", "my-default-unique-key")
print(f"JWT_SECRET_KEY: {JWT_SECRET_KEY}")
INTERNAL_API_KEY = '0201d2b222e3d58c5540cb05238d1f85fe964440aa9f0277299ec8011f71d1b4'
DEBUG = True
ALLOWED_HOSTS = ['localhost', '127.0.0.1', 'matchtracker_service']

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
    'django.middleware.common.CommonMiddleware',
    'django.middleware.csrf.CsrfViewMiddleware',
    'django.contrib.auth.middleware.AuthenticationMiddleware',
    'django.contrib.messages.middleware.MessageMiddleware',
    'django.middleware.clickjacking.XFrameOptionsMiddleware',
]

CORS_ALLOWED_ORIGINS = [
    "http://localhost:3000",
    "http://localhost:8000",
    "http://127.0.0.1:3000",
    "http://127.0.0.1:8000",

]

REST_FRAMEWORK = {
    'DEFAULT_AUTHENTICATION_CLASSES': (
        # 'rest_framework_simplejwt.authentication.JWTAuthentication',
        'game.authentication.JWTAuthentication',
    ),
    'DEFAULT_PERMISSION_CLASSES': [
        'rest_framework.permissions.IsAuthenticated',  # Requiert JWT pour accéder aux endpoints protégés
    ],
}

from datetime import timedelta

SIMPLE_JWT = {
    'SIGNING_KEY': os.getenv("JWT_SECRET_KEY", "a33d83c0f3be73db53d15b0a71c3e12b521b03ca0d300767b79722cd1c11940d"),
    'ALGORITHM': 'HS256',
}


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
    DATABASES = {
        'default': {
            'ENGINE': 'django.db.backends.postgresql',
            'NAME': 'matchtracker_service_db',
            'USER': 'shared_db_user',
            'PASSWORD': 'deplanta1',
            'HOST': 'localhost',
            'PORT': '5432',
        }
    }

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
            'level': 'DEBUG',
            'class': 'logging.FileHandler',
            'filename': os.path.join(BASE_DIR, 'logs/debug.log'),
            'formatter': 'verbose',
        },
    },
    'loggers': {
        'django': {
            'handlers': ['file'],
            'level': 'INFO',
            'propagate': True,
        },
        'matchtracker-service': {  # Votre logger personnalisé
            'handlers': ['file'],
            'level': 'DEBUG',
            'propagate': False,
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
SESSION_ENGINE = "django.contrib.sessions.backends.cache"
SESSION_CACHE_ALIAS = "default"

CACHES = {
    "default": {
        "BACKEND": "django_redis.cache.RedisCache",
        "LOCATION": "redis://127.0.0.1:6379/1",  # Adresse de votre serveur Redis
        "OPTIONS": {
            "CLIENT_CLASS": "django_redis.client.DefaultClient",
        }
    }
}

SESSION_COOKIE_DOMAIN = "localhost"
SESSION_COOKIE_NAME = "sessionid"  # Nom du cookie de session
SESSION_COOKIE_SAMESITE = "Lax"  # Permet les sous-domaines
SESSION_COOKIE_SECURE = False  # Doit être True en production si HTTPS est utilisé
SESSION_ENGINE = "django.contrib.sessions.backends.cache"  # Redis pour stocker les sessions
SESSION_CACHE_ALIAS = "default"  # Utilisation de la configuration cache 'default'
