from .authentication import JWTAuthentication
from rest_framework.exceptions import AuthenticationFailed
from django.contrib.auth.models import AnonymousUser
from collections import namedtuple
import logging

logger = logging.getLogger("matchtracker-service")

class JWTMiddleware:
    def __init__(self, get_response):
        self.get_response = get_response
        self.jwt_auth = JWTAuthentication()

    def __call__(self, request):
        logger.debug(f"JWTMiddleware: Processing request for path {request.path}")
        try:
            # Tente d'authentifier l'utilisateur avec le JWTAuthentication
            user, _ = self.jwt_auth.authenticate(request)
            if user:
                # Crée une représentation simple de l'utilisateur authentifié
                request.user = namedtuple('User', ['id', 'username', 'is_authenticated'])(user.id, user.username, True)
                logger.info(f"JWTMiddleware: Authentication successful for user {request.user}")
            else:
                raise AuthenticationFailed("User not authenticated")
        except AuthenticationFailed as e:
            # Définit un utilisateur anonyme si l'authentification échoue
            logger.warning(f"JWTMiddleware: Authentication failed - {str(e)}")
            request.user = AnonymousUser()
        except Exception as e:
            # Capture les exceptions inattendues
            logger.error(f"JWTMiddleware: Unexpected error during authentication - {str(e)}")
            request.user = AnonymousUser()

        # Passe la requête au middleware ou à la vue suivante
        logger.debug(f"JWTMiddleware: Final user on request: {getattr(request, 'user', None)}")
        return self.get_response(request)
