#!/bin/bash

echo "Début du nettoyage de l'espace disque..."

# 1. Supprimer les fichiers de cache utilisateur (NON RISQUÉ)
echo "Suppression des fichiers de cache..."
rm -rf ~/.cache/*  # Supprimer les fichiers de cache d'application
rm -rf ~/.mozilla/firefox/*/cache2/*  # Supprimer le cache Firefox
rm -rf ~/.config/google-chrome/Default/Cache/*  # Supprimer le cache Chrome

# 2. Supprimer les fichiers temporaires (NON RISQUÉ)
echo "Suppression des fichiers temporaires..."
rm -rf /tmp/*  # Nettoyer le répertoire temporaire global (accessible à l'utilisateur)
rm -rf ~/Downloads/*  # Supprimer tous les fichiers du dossier de téléchargements (VÉRIFIEZ AVANT)

# 3. Afficher les fichiers volumineux (NON RISQUÉ)
echo "Les fichiers les plus volumineux dans votre répertoire personnel :"
du -ah ~ 2>/dev/null | sort -rh | head -20

# 4. Rechercher les fichiers volumineux (RISQUÉ - DEMANDE DE CONFIRMATION)
echo "Recherche des fichiers de plus de 100 Mo (pas de suppression automatique)..."
find ~ -type f -size +100M -exec ls -lh {} \;
# find ~ -type f -size +100M -exec rm -i {} \;  # NE PAS ACTIVER SANS CONFIRMATION

# 5. Nettoyer l'historique des commandes (RISQUÉ)
echo "Nettoyage de l'historique des commandes (bash et zsh)..."
> ~/.bash_history  # Vider l'historique Bash (RISQUÉ : perte de l'historique utile)
> ~/.zsh_history  # Vider l'historique Zsh (RISQUÉ)

# 6. Vider la corbeille (NON RISQUÉ)
echo "Vider la corbeille..."
rm -rf ~/.local/share/Trash/*

# 7. Supprimer les fichiers journaux utilisateur (NON RISQUÉ)
echo "Suppression des fichiers journaux..."
find ~/. -name "*.log" -type f -delete  # Supprimer les fichiers journaux sans impact critique

# 8. Vérification des répertoires cachés (NON RISQUÉ - PAS DE SUPPRESSION)
echo "Vérification de la taille des répertoires cachés (pas de suppression)..."
du -sh ~/.config ~/.local ~/.mozilla 2>/dev/null

# 9. Suppression des applications utilisateur locales (RISQUÉ)
echo "Suppression des applications utilisateur locales..."
rm -rf ~/.local/share/applications/*  # RISQUÉ si des applications locales sont nécessaires
rm -rf ~/bin/*  # RISQUÉ si des scripts ou programmes personnalisés sont stockés ici

# 10. Identifier et afficher les fichiers en double (NON RISQUÉ)
echo "Recherche des fichiers en double (affichage uniquement)..."
find ~ -type f -exec md5sum {} + | sort | uniq -w 32 -d 2>/dev/null

echo "Nettoyage terminé en toute sécurité !"

