from .authentication import JWTAuthentication
from rest_framework.exceptions import AuthenticationFailed
from django.contrib.auth.models import AnonymousUser
from collections import namedtuple
import logging

logger = logging.getLogger("matchtracker-service")

# class JWTMiddleware:
#     def __init__(self, get_response):
#         self.get_response = get_response
#         self.jwt_auth = JWTAuthentication()

#     def __call__(self, request):
#         logger.debug(f"JWTMiddleware: Processing request for path {request.path}")
#         try:
#             # Tente d'authentifier l'utilisateur avec le JWTAuthentication
#             user, _ = self.jwt_auth.authenticate(request)
#             if user:
#                 # Crée une représentation simple de l'utilisateur authentifié
#                 request.user = namedtuple('User', ['id', 'username', 'is_authenticated'])(user.id, user.username, True)
#                 logger.info(f"JWTMiddleware: Authentication successful for user {request.user}")
#             else:
#                 raise AuthenticationFailed("User not authenticated")
#         except AuthenticationFailed as e:
#             # Définit un utilisateur anonyme si l'authentification échoue
#             logger.warning(f"JWTMiddleware: Authentication failed - {str(e)}")
#             request.user = AnonymousUser()
#         except Exception as e:
#             # Capture les exceptions inattendues
#             logger.error(f"JWTMiddleware: Unexpected error during authentication - {str(e)}")
#             request.user = AnonymousUser()

#         # Passe la requête au middleware ou à la vue suivante
#         logger.debug(f"JWTMiddleware: Final user on request: {getattr(request, 'user', None)}")
#         return self.get_response(request)

# class JWTMiddleware:
#     def __init__(self, get_response):
#         self.get_response = get_response
#         self.jwt_auth = JWTAuthentication()

#     def __call__(self, request):
#         logger.debug(f"JWTMiddleware: Processing request for path {request.path}")
#         try:
#             user, token = self.jwt_auth.authenticate(request)
#             if user:
#                 request.user = user
#                 logger.info(f"JWTMiddleware: Authentication successful for user {user}")
#             else:
#                 raise AuthenticationFailed("User not authenticated")
#         except AuthenticationFailed as e:
#             logger.warning(f"JWTMiddleware: Authentication failed - {str(e)}")
#             request.user = AnonymousUser()
#         except Exception as e:
#             logger.error(f"JWTMiddleware: Unexpected error during authentication - {str(e)}")
#             request.user = AnonymousUser()

#         return self.get_response(request)

from .authentication import JWTAuthentication
from rest_framework.exceptions import AuthenticationFailed
from django.contrib.auth.models import AnonymousUser
import logging

logger = logging.getLogger("matchtracker-service")

class JWTMiddleware:
    def __init__(self, get_response):
        self.get_response = get_response
        self.jwt_auth = JWTAuthentication()

    def __call__(self, request):
        logger.debug(f"JWTMiddleware: Processing request for path {request.path}")
        logger.debug(f"Requête reçue avec en-têtes : {request.headers}")

        # Vérifiez si un utilisateur est déjà authentifié par un autre middleware
        if hasattr(request, 'user') and request.user.is_authenticated:
            logger.debug("JWTMiddleware: User already authenticated by another middleware.")
            return self.get_response(request)

        try:
            # Authentifiez l'utilisateur avec JWTAuthentication
            user, token = self.jwt_auth.authenticate(request)
            if user:
                request.user = user
                request.auth = token  # Stockez le token pour un usage ultérieur
                logger.info(f"JWTMiddleware: Authentication successful for user {user}")
            else:
                logger.warning("JWTMiddleware: No user found in token")
                request.user = AnonymousUser()
        except AuthenticationFailed as e:
            logger.warning(f"JWTMiddleware: Authentication failed - {str(e)}")
            request.user = AnonymousUser()
            request.auth = None
        except Exception as e:
            logger.error(f"JWTMiddleware: Unexpected error during authentication - {str(e)}")
            request.user = AnonymousUser()
            request.auth = None

        if isinstance(request.user, AnonymousUser):
            raise AuthenticationFailed("Authentication is required")  # Ajout ici
        
        logger.debug(f"Final user on request in middleware: {request.user}, is_authenticated: {request.user.is_authenticated}")
        return self.get_response(request)
