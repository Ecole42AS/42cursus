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
            
            user, _ = self.jwt_auth.authenticate(request)
            if user:
                
                request.user = namedtuple('User', ['id', 'username', 'is_authenticated'])(user.id, user.username, True)
                logger.info(f"JWTMiddleware: Authentication successful for user {request.user}")
            else:
                raise AuthenticationFailed("User not authenticated")
        except AuthenticationFailed as e:
            
            logger.warning(f"JWTMiddleware: Authentication failed - {str(e)}")
            request.user = AnonymousUser()
        except Exception as e:
            
            logger.error(f"JWTMiddleware: Unexpected error during authentication - {str(e)}")
            request.user = AnonymousUser()

        
        logger.debug(f"JWTMiddleware: Final user on request: {getattr(request, 'user', None)}")
        return self.get_response(request)
