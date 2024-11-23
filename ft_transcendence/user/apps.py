from django.apps import AppConfig


class UserConfig(AppConfig): # UserConfig hérite de AppConfig
    default_auto_field = 'django.db.models.BigAutoField' # Utilise un BigAutoField pour défirnir la clé primaire, si cela n'est pas défini, Django utilise un AutoField par défaut
    name = 'user'

    def ready(self):
        import user.signals # signaux activés lorsque l'application est prête