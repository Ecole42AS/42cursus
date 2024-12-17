import logging
from django.contrib.sessions.models import Session

# Initialisez le logger pour les sessions
session_logger = logging.getLogger('session_debug')

def debug_session_middleware(get_response):
    """
    Middleware pour afficher les informations de session dans les logs.
    """
    def middleware(request):
        session_key = request.COOKIES.get('sessionid')
        if session_key:
            try:
                session = Session.objects.get(session_key=session_key)
                session_logger.debug(
                    f"Session Key: {session_key}, Session Data: {session.get_decoded()}"
                )
            except Session.DoesNotExist:
                session_logger.debug(f"Session {session_key} not found in the database.")
        else:
            session_logger.debug("No session key found in cookies.")

        # Passe la requête au prochain middleware ou à la vue
        response = get_response(request)
        return response

    return middleware
