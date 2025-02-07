from channels.middleware import BaseMiddleware
from django.contrib.auth.models import AnonymousUser
from game.authentication import JWTAuthentication  # Adaptez ce chemin à l'emplacement de votre classe
import logging
from urllib.parse import parse_qs


logger = logging.getLogger("channels.token_auth")

# class JWTAuthMiddleware(BaseMiddleware):
#     async def __call__(self, scope, receive, send):
#         # Extraire le token depuis la query string, par exemple ?token=xxx
#         query_string = scope.get("query_string", b"").decode()
#         token = None
#         if query_string.startswith("token="):
#             token = query_string.split("=", 1)[1]

#         if token:
#             try:
#                 jwt_auth = JWTAuthentication()
#                 user, _ = jwt_auth.authenticate_credentials(token)
#                 scope["user"] = user
#                 logger.info(f"WebSocket JWT auth successful for user {user}")
#             except Exception as e:
#                 logger.warning(f"WebSocket JWT auth failed: {e}")
#                 scope["user"] = AnonymousUser()
#         else:
#             scope["user"] = AnonymousUser()

#         return await super().__call__(scope, receive, send)
class JWTAuthMiddleware(BaseMiddleware):
    async def __call__(self, scope, receive, send):
        query_string = scope.get("query_string", b"").decode()
        query_params = parse_qs(query_string)
        token_list = query_params.get("token")
        token = token_list[0] if token_list else None
        logger.debug(f"Query string: {query_string}")
        logger.debug(f"Token extrait: {token}")


        if token:
            try:
                jwt_auth = JWTAuthentication()
                user, _ = jwt_auth.authenticate_credentials(token)
                scope["user"] = user
                logger.info(f"WebSocket JWT auth successful for user {user}")
            except Exception as e:
                logger.warning(f"WebSocket JWT auth failed: {e}")
                scope["user"] = AnonymousUser()
        else:
            scope["user"] = AnonymousUser()

        return await super().__call__(scope, receive, send)