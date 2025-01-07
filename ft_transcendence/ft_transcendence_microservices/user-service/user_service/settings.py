import os
from pathlib import Path
import sys
from dotenv import load_dotenv
from datetime import timedelta



BASE_DIR = Path(__file__).resolve().parent.parent


load_dotenv(os.path.join(BASE_DIR, '.env'))




SECRET_KEY = os.getenv("DJANGO_SECRET_KEY", "fallback-secret-key")
JWT_SECRET_KEY = os.getenv("JWT_SECRET_KEY", "my-default-unique-key")
print(f"JWT_SECRET_KEY: {JWT_SECRET_KEY}")

INTERNAL_API_KEY = '0201d2b222e3d58c5540cb05238d1f85fe964440aa9f0277299ec8011f71d1b4'

DEBUG = os.getenv("DEBUG", "False").lower() in ("true", "1", "yes")


ALLOWED_HOSTS = ['127.0.0.1', 'localhost', 'user_service', '172.19.0.4', '172.19.0.3']










INSTALLED_APPS = [
    'django.contrib.admin',
    'django.contrib.auth',
    'django.contrib.contenttypes',
    'django.contrib.sessions',
    'django.contrib.messages',
    'django.contrib.staticfiles',
    'rest_framework',
    'rest_framework_simplejwt',
    'rest_framework_simplejwt.token_blacklist',
    'corsheaders',
    'user',  
]




MIDDLEWARE = [
    'django.middleware.security.SecurityMiddleware',
    'django.contrib.sessions.middleware.SessionMiddleware',
    'corsheaders.middleware.CorsMiddleware',
    
    'django.middleware.csrf.CsrfViewMiddleware',
    'django.contrib.auth.middleware.AuthenticationMiddleware',
    'django.contrib.messages.middleware.MessageMiddleware',
    'django.middleware.clickjacking.XFrameOptionsMiddleware',
    'user.middleware.UpdateLastActivityMiddleware',  
    'user.middleware.JWTValidationMiddleware',
]
MIDDLEWARE.insert(0, 'user.middleware.LogRequestMiddleware')


CORS_ALLOWED_ORIGINS = [
    "http://localhost:3000",
    "http://127.0.0.1:3000",
    "http://matchtracker-service:8000",  
    "http://localhost:8000",  
]

REST_FRAMEWORK = {
    'DEFAULT_AUTHENTICATION_CLASSES': (
        'user.authentication.EnhancedJWTAuthentication',  
        'rest_framework.authentication.SessionAuthentication',  
    ),
    'DEFAULT_PERMISSION_CLASSES': [
        'rest_framework.permissions.IsAuthenticated',  
    ],
    'DEFAULT_PARSER_CLASSES': (
        'rest_framework.parsers.JSONParser',  
        'rest_framework.parsers.FormParser',  
        'rest_framework.parsers.MultiPartParser',  
    ),
    'DEFAULT_RENDERER_CLASSES': (
        'rest_framework.renderers.JSONRenderer',  
        'rest_framework.renderers.BrowsableAPIRenderer',  
    ),
}



from datetime import timedelta

SIMPLE_JWT = {
    'ACCESS_TOKEN_LIFETIME': timedelta(minutes=40),
    'REFRESH_TOKEN_LIFETIME': timedelta(days=1),
    'SIGNING_KEY': os.getenv("JWT_SECRET_KEY", "a33d83c0f3be73db53d15b0a71c3e12b521b03ca0d300767b79722cd1c11940d"),
    'ALGORITHM': 'HS256',
    'BLACKLIST_AFTER_ROTATION': True,  

}


ROOT_URLCONF = 'user_service.urls'


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
            'NAME': os.getenv('POSTGRES_DB', 'user_service_db'),
            'USER': os.getenv('POSTGRES_USER', 'shared_db_user'),
            'PASSWORD': os.getenv('POSTGRES_PASSWORD', 'deplanta1'),
            'HOST': os.getenv('POSTGRES_HOST', 'postgres'),
            'PORT': os.getenv('POSTGRES_PORT', '5432'),
        }
    }


SESSION_ENGINE = "django.contrib.sessions.backends.db"  













SESSION_COOKIE_DOMAIN = "localhost"
SESSION_COOKIE_NAME = "sessionid"  
SESSION_COOKIE_SAMESITE = "Lax"  
SESSION_COOKIE_SECURE = False  

SESSION_ENGINE = "django.contrib.sessions.backends.db"  
SESSION_CACHE_ALIAS = "default"  




AUTH_USER_MODEL = 'user.CustomUser'


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


LANGUAGE_CODE = 'en-us'
TIME_ZONE = 'Europe/Zurich'
USE_I18N = True
USE_TZ = True


STATIC_URL = 'static/'


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

