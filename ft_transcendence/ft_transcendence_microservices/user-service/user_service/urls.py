from django.contrib import admin
from django.urls import path, include
from django.conf import settings
from django.conf.urls.static import static
from rest_framework_simplejwt.views import (
    TokenObtainPairView,
    TokenRefreshView,
)
from user.views import ValidateTokenView

urlpatterns = [
    path('admin/', admin.site.urls),  # Interface d'administration
    path('api-auth/', include('rest_framework.urls')),  # Ajoutez cette ligne
    path('api/user/', include('user.urls')),  # Routes spécifiques à l'app 'user'
    path('api/token/', TokenObtainPairView.as_view(), name='token_obtain_pair'),
    path('api/token/refresh/', TokenRefreshView.as_view(), name='token_refresh'),
    path('validate/', ValidateTokenView.as_view(), name='validate_user'),
]

# Servir les fichiers médias en mode DEBUG
if settings.DEBUG:
    urlpatterns += static(settings.MEDIA_URL, document_root=settings.MEDIA_ROOT)
