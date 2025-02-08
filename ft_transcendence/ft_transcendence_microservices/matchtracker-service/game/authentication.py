
from rest_framework.authentication import BaseAuthentication
from rest_framework.exceptions import AuthenticationFailed
from rest_framework_simplejwt.tokens import AccessToken
from collections import namedtuple
from .utils import get_user_data
import logging

logger = logging.getLogger("matchtracker-service")

from rest_framework.exceptions import AuthenticationFailed

class JWTAuthentication(BaseAuthentication):
    def authenticate(self, request):
        try:
            auth_header = request.headers.get("Authorization")
            if not auth_header or not auth_header.startswith("Bearer "):
                raise AuthenticationFailed("No token provided or invalid format")

            token = auth_header.split(" ")[1]
            logger.debug(f"Token received: {token}")

            decoded_token = AccessToken(token)
            logger.debug(f"Decoded token: {decoded_token}")

            user_id = decoded_token.get("user_id")
            if not user_id:
                raise AuthenticationFailed("Invalid token structure")

            user_data = get_user_data(user_id, token)
            if not user_data:
                raise AuthenticationFailed("User not found")

            user = namedtuple("User", ["id", "username", "is_authenticated"])(
                id=user_data["id"], username=user_data["username"], is_authenticated=True
            )
            return (user, token)

        except AuthenticationFailed as e:
            logger.warning(f"Authentication failed: {e}")
            raise
        except Exception as e:
            logger.error(f"Unexpected error during authentication: {e}")
            raise AuthenticationFailed("Invalid or expired token")
