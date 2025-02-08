from rest_framework_simplejwt.exceptions import TokenError
from rest_framework_simplejwt.authentication import JWTAuthentication
from rest_framework.exceptions import AuthenticationFailed

class EnhancedJWTAuthentication(JWTAuthentication):
    def authenticate(self, request):
        auth_header = request.headers.get('Authorization')

        if not auth_header or not auth_header.startswith('Bearer '):
            return None

        try:

            return super().authenticate(request)
        except TokenError as e:
            raise AuthenticationFailed({
                'error': 'Token invalid or expired',
                'details': str(e)
            })
        except Exception as e:
            raise AuthenticationFailed({
                'error': 'Authentication failed',
                'details': str(e)
            })
