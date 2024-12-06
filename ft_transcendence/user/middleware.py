"""
Middleware est une couche d'intermédiaire entre la requête et la vue. Il est utilisé pour effectuer des opérations sur la requête avant qu'elle n'atteigne la vue et sur la réponse avant qu'elle ne soit renvoyée au client.
"""
from django.utils import timezone

# Middleware qui met à jour la date de dernière activité de l'utilisateur à chaque requête
class UpdateLastActivityMiddleware:
    def __init__(self, get_response): # initialise get_response pour l'utiliser dans la méthode __call__
        self.get_response = get_response

    def __call__(self, request):
        if request.user.is_authenticated:
            profile = request.user.profile
            profile.last_activity = timezone.now()
            profile.save()
        response = self.get_response(request) # Passe la requête au middleware suivant et si c'est le dernier, à la vue
        return response
