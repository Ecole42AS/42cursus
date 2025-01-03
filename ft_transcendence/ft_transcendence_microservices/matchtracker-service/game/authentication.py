# from django.contrib.auth.models import AnonymousUser
# from rest_framework.authentication import BaseAuthentication
# from rest_framework.exceptions import AuthenticationFailed
# from rest_framework_simplejwt.tokens import AccessToken
# from .utils import get_user_data, is_token_revoked  # Importez les fonctions utilitaires

# class JWTAuthentication(BaseAuthentication):
#     """
#     Custom JWT Authentication to validate the token and enrich the user.
#     """
#     def authenticate(self, request):
#         auth_header = request.headers.get("Authorization")
#         if not auth_header or not auth_header.startswith("Bearer "):
#             return None  # Aucun token fourni

#         token = auth_header.split(" ")[1]
#         if not token:
#             raise AuthenticationFailed("Token is missing or empty")

#         try:
#             # Décoder et valider le token
#             decoded_token = AccessToken(token)

#             # Vérifier si le token a été révoqué
#             if is_token_revoked(token):
#                 raise AuthenticationFailed("Token has been revoked")

#             user_id = decoded_token.get("user_id")
#             if not user_id:
#                 raise AuthenticationFailed("Invalid token structure: missing 'user_id'")

#             # Récupérer les informations utilisateur depuis le service `User`
#             user_data = get_user_data(user_id)
#             if not user_data:
#                 raise AuthenticationFailed("User not found in User Service")

#             # Créer un utilisateur enrichi avec les données récupérées
#             user = AnonymousUser()
#             user.id = user_id
#             user.username = user_data.get("username", f"user_{user_id}")
#             user.is_authenticated = True

#             return user, None
#         except AuthenticationFailed as e:
#             raise e  # Propager les exceptions explicites
#         except Exception as e:
#             raise AuthenticationFailed(f"Invalid or expired token: {str(e)}")

from rest_framework.authentication import BaseAuthentication
from rest_framework.exceptions import AuthenticationFailed
from rest_framework_simplejwt.tokens import AccessToken
from collections import namedtuple
from .utils import get_user_data

class JWTAuthentication(BaseAuthentication):
    def authenticate(self, request):
        auth_header = request.headers.get("Authorization")
        if not auth_header or not auth_header.startswith("Bearer "):
            raise AuthenticationFailed("No token provided or invalid format")

        token = auth_header.split(" ")[1]
        if not token:
            raise AuthenticationFailed("Token is missing or empty")

        try:
            # Valider et décoder le token
            decoded_token = AccessToken(token)
            user_id = decoded_token.get("user_id")
            if not user_id:
                raise AuthenticationFailed("Invalid token structure: missing 'user_id'")

            # Récupérer les informations utilisateur depuis le service User
            user_data = get_user_data(user_id, token)
            if not user_data:
                raise AuthenticationFailed("User not found in User Service")

            # Créer un objet utilisateur temporaire
            User = namedtuple("User", ["id", "username", "is_authenticated"])
            user = User(
                id=user_data["id"],
                username=user_data["username"],
                is_authenticated=True
            )

            return user, None
        except Exception as e:
            raise AuthenticationFailed(f"Invalid or expired token: {str(e)}")
