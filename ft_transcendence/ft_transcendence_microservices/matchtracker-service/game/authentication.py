















































from rest_framework.authentication import BaseAuthentication
from rest_framework.exceptions import AuthenticationFailed
from rest_framework_simplejwt.tokens import AccessToken
from collections import namedtuple
from .utils import get_user_data
import logging

logger = logging.getLogger("matchtracker-service")







































class JWTAuthentication(BaseAuthentication):
    def authenticate(self, request):
        logger.info("Authenticating request...")
        auth_header = request.headers.get("Authorization")
        logger.debug(f"Authorization header: {auth_header}")

        if not auth_header or not auth_header.startswith("Bearer "):
            logger.warning("No token provided or invalid format")
            raise AuthenticationFailed("No token provided or invalid format")

        token = auth_header.split(" ")[1]
        logger.debug(f"Token received: {token}")

        try:
            decoded_token = AccessToken(token)
            logger.debug(f"Decoded token: {decoded_token}")
            user_id = decoded_token.get("user_id")
            if not user_id:
                raise AuthenticationFailed("Invalid token structure: missing 'user_id'")

            user_data = get_user_data(user_id, token)
            logger.debug(f"User data fetched: {user_data}")
            if not user_data:
                raise AuthenticationFailed("User not found in User Service")

            User = namedtuple("User", ["id", "username", "is_authenticated"])
            user = User(id=user_data["id"], username=user_data["username"], is_authenticated=True)
            logger.debug(f"Authenticated user: {user}")
            return user, token

        except Exception as e:
            logger.error(f"Authentication failed: {e}")
            raise AuthenticationFailed(f"Invalid or expired token: {e}")
