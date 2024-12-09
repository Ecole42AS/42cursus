"""
Personnalisation de l'administration de Django pour inclure les profils liés
"""
from django.contrib import admin
from django.contrib.auth.admin import UserAdmin
from .models import CustomUser, Profile

class ProfileInline(admin.StackedInline):
    model = Profile
    can_delete = False
    verbose_name_plural = 'Profiles'
    fk_name = 'user'

class CustomUserAdmin(UserAdmin):
    inlines = [ProfileInline] 
    list_display = ('username', 'email', 'first_name', 'last_name', 'is_staff', 'display_name') 
    list_select_related = ('profile',) 

    def display_name(self, instance):
        return instance.profile.display_name
    display_name.short_description = 'Nom d\'affichage'

    def get_inline_instances(self, request, obj=None):
        if not obj:
            return []
        return super().get_inline_instances(request, obj)

admin.site.register(CustomUser, CustomUserAdmin)
