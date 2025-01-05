"""
Middleware est une couche d'intermédiaire entre la requête et la vue. Il est utilisé pour effectuer des opérations sur la requête avant qu'elle n'atteigne la vue et sur la réponse avant qu'elle ne soit renvoyée au client.
"""
from django.utils import timezone
from rest_framework_simplejwt.authentication import JWTAuthentication
from django.utils.deprecation import MiddlewareMixin
from rest_framework.exceptions import AuthenticationFailed

class UpdateLastActivityMiddleware:
    def __init__(self, get_response):
        self.get_response = get_response

    def __call__(self, request):
        if request.user.is_authenticated:
            profile = request.user.profile
            profile.last_activity = timezone.now()
            profile.save()
        response = self.get_response(request)
        return response

class JWTValidationMiddleware(MiddlewareMixin):
    def process_request(self, request):
        auth = JWTAuthentication()
        header = request.META.get('HTTP_AUTHORIZATION')
        if not header or not header.startswith('Bearer '):
            request.user = None
            return

        try:
            raw_token = header.split(' ')[1]
            validated_token = auth.get_validated_token(raw_token)
            request.user = auth.get_user(validated_token)
        except AuthenticationFailed:
            request.user = None

class LogRequestMiddleware:
    def __init__(self, get_response):
        self.get_response = get_response

    def __call__(self, request):
        print(f"Host: {request.headers.get('Host')}")
        return self.get_response(request)
