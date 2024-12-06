"""
Django settings for ft_transcendence project.

Generated by 'django-admin startproject' using Django 5.1.3.

For more information on this file, see
https://docs.djangoproject.com/en/5.1/topics/settings/

For the full list of settings and their values, see
https://docs.djangoproject.com/en/5.1/ref/settings/
"""

import os
import sys
from pathlib import Path

# Base Directory
# ------------------------------------------------------------------------------
BASE_DIR = Path(__file__).resolve().parent.parent


# Security Settings
# ------------------------------------------------------------------------------
SECRET_KEY = 'django-insecure-^96ocy_do_=)*km4l9-m%n1hk&^b-ous4gxw8%09+f9dos010q'
DEBUG = True
ALLOWED_HOSTS = ['127.0.0.1', 'localhost']


# Installed Applications
# ------------------------------------------------------------------------------
INSTALLED_APPS = [
    # Default Django apps
    'django.contrib.admin',
    'django.contrib.auth',
    'django.contrib.contenttypes',
    'django.contrib.sessions',
    'django.contrib.messages',
    'django.contrib.staticfiles',

    # Third-party apps
    'rest_framework',
    'corsheaders',

    # Local apps
    'user',
    'game',
]


# Middleware
# ------------------------------------------------------------------------------
MIDDLEWARE = [
    'django.middleware.security.SecurityMiddleware',
    'django.contrib.sessions.middleware.SessionMiddleware',
    'corsheaders.middleware.CorsMiddleware',
    'django.middleware.common.CommonMiddleware',
    'django.middleware.csrf.CsrfViewMiddleware',
    'django.contrib.auth.middleware.AuthenticationMiddleware',
    'django.contrib.messages.middleware.MessageMiddleware',
    'django.middleware.clickjacking.XFrameOptionsMiddleware',
    'user.middleware.UpdateLastActivityMiddleware',
]


# CORS Configuration
# ------------------------------------------------------------------------------
CORS_ALLOWED_ORIGINS = [
    "http://localhost:3000",
    "http://127.0.0.1:3000",
]


# URL Configuration
# ------------------------------------------------------------------------------
ROOT_URLCONF = 'ft_transcendence.urls'


# Templates
# ------------------------------------------------------------------------------
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


# WSGI Application
# ------------------------------------------------------------------------------
WSGI_APPLICATION = 'ft_transcendence.wsgi.application'


# Database
# ------------------------------------------------------------------------------
if 'test' in sys.argv:  # Use SQLite for tests
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
            'NAME': 'mydb',
            'USER': 'alex',
            'PASSWORD': 'deplanta1',
            'HOST': 'localhost',
            'PORT': '5432',
        }
    }


# Authentication Settings
# ------------------------------------------------------------------------------
AUTH_USER_MODEL = 'user.CustomUser'


# Password Validation
# ------------------------------------------------------------------------------
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


# Internationalization
# ------------------------------------------------------------------------------
LANGUAGE_CODE = 'en-us'
TIME_ZONE = 'Europe/Zurich'
USE_I18N = True # internationalisation (traduction, format de date, etc.)
USE_TZ = True # convertit dans le fuseau horaire UTC local


# Static and Media Files
# ------------------------------------------------------------------------------
STATIC_URL = 'static/'

MEDIA_URL = '/media/'
MEDIA_ROOT = os.path.join(BASE_DIR, 'media')


# Default Primary Key Field Type
# ------------------------------------------------------------------------------
DEFAULT_AUTO_FIELD = 'django.db.models.BigAutoField'


# Test Settings
# ------------------------------------------------------------------------------
# Temporary storage for test cases
if 'test' in sys.argv:
    import tempfile
    from django.core.files.storage import FileSystemStorage

    class TemporaryTestStorage(FileSystemStorage):
        def __init__(self, *args, **kwargs):
            super().__init__(location=tempfile.mkdtemp(), *args, **kwargs)

    DEFAULT_FILE_STORAGE = 'ft_transcendence.settings.TemporaryTestStorage'

# Logging Configuration
# ------------------------------------------------------------------------------

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
            'filename': '/home/alex/Ecole42/42cursus/ft_transcendence/logs/debug.log',  # Update this path
            'formatter': 'verbose',
        },
    },
    'loggers': {
        'django': {
            'handlers': ['file'],
            'level': 'INFO',  # Change to INFO to reduce verbosity
            'propagate': True,
        },
        'django.request': {
            'handlers': ['file'],
            'level': 'ERROR',  # Log only errors for requests
            'propagate': False,
        },
        'django.db.backends': {
            'handlers': ['file'],
            'level': 'ERROR',  # Log only errors for database operations
            'propagate': False,
        },
        'myapp': {
            'handlers': ['file'],
            'level': 'DEBUG',  # Keep debug level for your app (capture all messages)
            'propagate': False,
        },
    },
}
