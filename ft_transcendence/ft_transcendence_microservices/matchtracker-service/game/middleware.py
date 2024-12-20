from .authentication import JWTAuthentication
from rest_framework.exceptions import AuthenticationFailed

class JWTMiddleware:
    def __init__(self, get_response):
        self.get_response = get_response
        self.jwt_auth = JWTAuthentication()

    def __call__(self, request):
        try:
            user, _ = self.jwt_auth.authenticate(request)
            request.user = user
        except AuthenticationFailed as e:
            request.user = None  # Définir l'utilisateur comme non authentifié en cas d'erreur
        return self.get_response(request)
