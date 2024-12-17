from django.contrib.auth.models import AnonymousUser, User
from rest_framework.authentication import BaseAuthentication
from rest_framework.exceptions import AuthenticationFailed
from rest_framework_simplejwt.tokens import AccessToken


class JWTAuthentication(BaseAuthentication):
    """
    Custom JWT Authentication to validate the token and extract user.
    """
    def authenticate(self, request):
        auth_header = request.headers.get("Authorization")
        if not auth_header or not auth_header.startswith("Bearer "):
            return None  # Pas de token fourni

        token = auth_header.split(" ")[1]
        try:
            # Valider et décoder le token
            decoded_token = AccessToken(token)
            user_id = decoded_token["user_id"]

            # Créer un objet utilisateur temporaire avec is_authenticated=True
            user = User(id=user_id, username=f"user_{user_id}")
            user.is_authenticated = True

            return user, None  # Retourner l'objet utilisateur
        except Exception as e:
            raise AuthenticationFailed("Invalid or expired token")
