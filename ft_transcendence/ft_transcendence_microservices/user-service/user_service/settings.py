import os
from pathlib import Path
import sys

# Définir le répertoire de base du service utilisateur
BASE_DIR = Path(__file__).resolve().parent.parent

# Clé secrète - à sécuriser en production
# SECRET_KEY = 'django-insecure-^96ocy_do_=)*km4l9-m%n1hk&^b-ous4gxw8%09+f9dos010q'
# SECRET_KEY = 'akn1%#!+sh*gzpb#ek_30a=3qag!14&%rj1mz%!uaj3*a1-i*n'
SECRET_KEY = '4uhyw(pjk&*i^ir70!^@xd!skh9$^#$mm^lt+3kc-07#_bqvn&'

# SECRET_KEY = os.getenv("DJANGO_SECRET_KEY", "fallback-secret-key")
INTERNAL_API_KEY = '0201d2b222e3d58c5540cb05238d1f85fe964440aa9f0277299ec8011f71d1b4'
# Mode Debug - Désactiver en production
DEBUG = True

# Hôtes autorisés
ALLOWED_HOSTS = ['127.0.0.1', 'localhost']
CSRF_TRUSTED_ORIGINS = ["http://127.0.0.1:8080", "http://localhost:8080", "http://localhost:8000", "http://127.0.0.1:8000"]

CSRF_COOKIE_DOMAIN = "localhost"
CSRF_COOKIE_SAMESITE = "Lax"

# Applications installées
INSTALLED_APPS = [
    'django.contrib.admin',
    'django.contrib.auth',
    'django.contrib.contenttypes',
    'django.contrib.sessions',
    'django.contrib.messages',
    'django.contrib.staticfiles',

    'rest_framework',
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
]

# Configuration CORS
CORS_ALLOWED_ORIGINS = [
    "http://localhost:3000",
    "http://127.0.0.1:3000",
    "http://127.0.0.1:8080",
    "http://localhost:8000",
    "http://localhost:8080"  # Autoriser localhost pour les tests
]
CORS_ALLOW_CREDENTIALS = True


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
    DATABASES = {
        'default': {
            'ENGINE': 'django.db.backends.postgresql',
            'NAME': 'user_service_db',
            'USER': 'shared_db_user',
            'PASSWORD': 'deplanta1',
            'HOST': 'localhost',
            'PORT': '5432',
        }
   }

SESSION_ENGINE = "django.contrib.sessions.backends.cache"
SESSION_CACHE_ALIAS = "default"

CACHES = {
    "default": {
        "BACKEND": "django_redis.cache.RedisCache",
        "LOCATION": "redis://127.0.0.1:6379/0",
        "OPTIONS": {
            "CLIENT_CLASS": "django_redis.client.DefaultClient",
            "KEY_PREFIX": "session",  # Assure-toi que le préfixe est vide
        }
    }
}

SESSION_COOKIE_DOMAIN = "localhost"  # Domaine identique
SESSION_COOKIE_NAME = "sessionid"    # Nom du cookie de session
SESSION_COOKIE_SAMESITE = "Lax"      # Pour sous-domaines
SESSION_COOKIE_SECURE = False        # HTTPS seulement en production


REST_FRAMEWORK = {
    'DEFAULT_AUTHENTICATION_CLASSES': [
        'rest_framework.authentication.SessionAuthentication',
    ],
    'DEFAULT_PERMISSION_CLASSES': [
        'rest_framework.permissions.IsAuthenticated',
    ],
}

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
        'session_debug': {
            'format': '{levelname} {asctime} {module} [SESSION] {message}',
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
        'session_file': {
            'level': 'DEBUG',
            'class': 'logging.FileHandler',
            'filename': os.path.join(BASE_DIR, 'logs/session_debug.log'),
            'formatter': 'session_debug',
        },
        'console': {
            'level': 'DEBUG',
            'class': 'logging.StreamHandler',
            'formatter': 'verbose',
        },
    },
    'loggers': {
        'django': {
            'handlers': ['file', 'console'],
            'level': 'INFO',
            'propagate': True,
        },
        'django.request': {
            'handlers': ['file', 'console'],
            'level': 'ERROR',
            'propagate': False,
        },
        'django.db.backends': {
            'handlers': ['file'],
            'level': 'ERROR',
            'propagate': False,
        },
        'session_debug': {  # Nouveau logger pour les sessions
            'handlers': ['session_file', 'console'],
            'level': 'DEBUG',
            'propagate': False,
        },
    },
}

