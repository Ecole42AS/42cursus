#!/bin/zsh

# Fonction pour générer à la fois le fichier .cpp et le fichier .hpp avec une classe canonique
function generate_canonical_files() {
    local hpp_file="$1"

    # Vérifier si le fichier .hpp commence par une majuscule (pour correspondre à ta condition)
    if [[ "${hpp_file}" =~ ^[A-Z] ]]; then
        # Générer le nom du fichier .cpp en remplaçant l'extension .hpp par .cpp
        cpp_file="${hpp_file:r}.cpp"  # Utilisation de ${hpp_file:r} pour enlever l'extension .hpp
        
        # Générer le contenu du fichier .cpp avec les méthodes spécifiées
        if [ ! -f "${cpp_file}" ]; then
            cat > "${cpp_file}" <<EOF
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ${hpp_file:r}.cpp                               			:+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: $(date '+%Y/%m/%d %H:%M:%S') by astutz            #+#    #+#             */
/*   Updated: $(date '+%Y/%m/%d %H:%M:%S') by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "${hpp_file}"

${hpp_file%.hpp}::${hpp_file%.hpp}()
{
    // Constructor implementation
}

${hpp_file%.hpp}::~${hpp_file%.hpp}()
{
    // Destructor implementation
}

${hpp_file%.hpp}::${hpp_file%.hpp}(const ${hpp_file%.hpp} &src)
{
    *this = src;
}

${hpp_file%.hpp} &${hpp_file%.hpp}::operator=(const ${hpp_file%.hpp} &rhs)
{
    if (this != &rhs) {
        // Copy assignment implementation
        // Example: member_variable = rhs.member_variable;
    }
    return *this;
}

EOF
            echo "Fichier ${cpp_file} généré avec succès !"
        else
            echo "Le fichier ${cpp_file} existe déjà, aucune action nécessaire."
        fi

        # Générer le contenu du fichier .hpp avec la classe canonique et #pragma once
        if [ ! -f "${hpp_file}" ]; then
            cat > "${hpp_file}" <<EOF
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ${hpp_file%.hpp}.hpp                               			:+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: $(date '+%Y/%m/%d %H:%M:%S') by astutz            #+#    #+#             */
/*   Updated: $(date '+%Y/%m/%d %H:%M:%S') by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>

class ${hpp_file%.hpp} {
private:
    // Private members here
public:
    ${hpp_file%.hpp}();
    ~${hpp_file%.hpp}();
    ${hpp_file%.hpp}(const ${hpp_file%.hpp} &src);
    ${hpp_file%.hpp} &operator=(const ${hpp_file%.hpp} &rhs);
};

EOF
            echo "Fichier ${hpp_file} généré avec succès avec la classe canonique et #pragma once !"
        else
            echo "Le fichier ${hpp_file} existe déjà, aucune action nécessaire."
        fi
    else
        echo "Le nom de fichier '${hpp_file}' ne commence pas par une majuscule. La classe canonique ne peut pas être générée."
    fi
}

# Vérifier si un argument est fourni en ligne de commande
if [ $# -eq 0 ]; then
    echo "Usage: ./generate_cpp_class.zsh <nom_du_fichier>.hpp"
    exit 1
fi

# Utiliser le premier argument comme nom de fichier .hpp pour générer la classe canonique et ses fichiers associés
hpp_file="$1"

# Appeler la fonction pour générer les fichiers .cpp et .hpp avec la classe canonique
generate_canonical_files "${hpp_file}"
