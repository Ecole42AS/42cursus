from .authentication import JWTAuthentication
from rest_framework.exceptions import AuthenticationFailed
from django.contrib.auth.models import AnonymousUser
from collections import namedtuple
import logging

logger = logging.getLogger("matchtracker-service")

from django.contrib.auth.models import AnonymousUser
from rest_framework.exceptions import AuthenticationFailed
from django.http import JsonResponse
from .authentication import JWTAuthentication
import logging

logger = logging.getLogger("matchtracker-service")

class JWTMiddleware:
    def __init__(self, get_response):
        self.get_response = get_response
        self.jwt_auth = JWTAuthentication()

    def __call__(self, request):
        logger.debug(f"JWTMiddleware: Processing request for path {request.path}")

        public_paths = ["/", "/static/", "/favicon.ico"]
        if any(request.path.startswith(path) for path in public_paths):
            logger.debug("JWTMiddleware: Public endpoint, skipping JWT authentication")
            return self.get_response(request)

        try:

            user, token = self.jwt_auth.authenticate(request)
            if user:
                request.user = user
                request.auth = token
                logger.info(f"JWTMiddleware: Authentication successful for user {user}")
            else:
                logger.warning("JWTMiddleware: No user found in token")
                request.user = AnonymousUser()

        except AuthenticationFailed as e:
            logger.warning(f"JWTMiddleware: Authentication failed - {str(e)}")
            return JsonResponse({"detail": str(e)}, status=401)

        except Exception as e:
            logger.error(f"JWTMiddleware: Unexpected error during authentication - {str(e)}")
            return JsonResponse({"detail": "An unexpected error occurred."}, status=500)

        return self.get_response(request)
