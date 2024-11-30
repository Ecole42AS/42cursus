from django.contrib import admin
from django.contrib.auth.admin import UserAdmin
from .models import CustomUser, Profile

# Définir une classe inline pour afficher et éditer les profils liés dans l'admin
class ProfileInline(admin.StackedInline):
    model = Profile
    can_delete = False
    verbose_name_plural = 'Profiles'
    fk_name = 'user'

# Étendre UserAdmin pour inclure ProfileInline
class CustomUserAdmin(UserAdmin):
    inlines = [ProfileInline]  # Inclure les profils dans l'administration des utilisateurs
    list_display = ('username', 'email', 'first_name', 'last_name', 'is_staff', 'display_name')  # Champs affichés dans la liste
    list_select_related = ('profile',)  # Optimiser les requêtes en préchargeant les profils

    # Ajouter un champ pour afficher le `display_name` du profil
    def display_name(self, instance):
        return instance.profile.display_name
    display_name.short_description = 'Nom d\'affichage'

    # Permettre l'édition des champs liés au profil uniquement si un objet utilisateur existe
    def get_inline_instances(self, request, obj=None):
        if not obj:
            return []
        return super().get_inline_instances(request, obj)

# Enregistrer CustomUser avec CustomUserAdmin
admin.site.register(CustomUser, CustomUserAdmin)
