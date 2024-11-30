from django.utils import timezone

# Middleware qui met à jour la date de dernière activité de l'utilisateur à chaque requête
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
