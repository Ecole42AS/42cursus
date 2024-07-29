/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                               			:+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 15:32:49 by astutz            #+#    #+#             */
/*   Updated: 2024/07/13 15:32:49 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <sstream>
#include <iomanip>
#include <cstdlib>


class BitcoinExchange {
private:
    std::map<std::string, double> _csvFile;
    std::map<std::string, double> _inputFile;
public:
    BitcoinExchange();
    ~BitcoinExchange();
    BitcoinExchange(const BitcoinExchange &src);
    BitcoinExchange &operator=(const BitcoinExchange &rhs);
	void parseCSV();
	void parseInput(std::string fileName);
	std::string trim(const std::string& str);

};



// Bien sûr, je vais t'expliquer comment aborder cet exercice sans te donner directement de code.

// ### Étapes pour créer le programme

// 1. **Chargement des bases de données**:
//    - **CSV des prix du bitcoin** : Il s'agit d'un fichier CSV contenant les prix du bitcoin pour différentes dates. Il faut charger ce fichier en mémoire.
//    - **Fichier d'entrée** : Ce fichier contient des lignes avec des dates et des valeurs. Ce fichier sera lu en entrée du programme.

// 2. **Analyse des fichiers**:
//    - **CSV des prix du bitcoin** : Parse ce fichier pour obtenir une structure de données (par exemple, un dictionnaire ou une liste de tuples) où chaque date est associée à un prix.
//    - **Fichier d'entrée** : Parse ce fichier pour obtenir les dates et les valeurs.

// 3. **Validation des entrées**:
//    - Vérifie que chaque ligne du fichier d'entrée respecte le format attendu ("date | value").
//    - Vérifie que la date est au format "AAAA-MM-JJ".
//    - Vérifie que la valeur est un float ou un entier positif compris entre 0 et 1000.

// 4. **Recherche des prix et calcul**:
//    - Pour chaque date du fichier d'entrée, cherche le prix correspondant dans le fichier CSV des prix du bitcoin.
//    - Si la date n'existe pas, trouve la date la plus proche en prenant la date inférieure la plus proche.
//    - Multiplie la valeur donnée par le prix du bitcoin pour la date trouvée.

// 5. **Gestion des erreurs**:
//    - Si le fichier ne peut pas être ouvert, afficher un message d'erreur.
//    - Si une ligne contient une date invalide, afficher un message d'erreur.
//    - Si une valeur est négative ou dépasse 1000, afficher un message d'erreur.

// 6. **Affichage des résultats**:
//    - Pour chaque ligne valide du fichier d'entrée, afficher la date, la valeur initiale, et le résultat de la multiplication par le prix du bitcoin.

// ### Pseudo-code pour l'approche

// 1. Charger le fichier CSV des prix du bitcoin dans une structure de données.
// 2. Ouvrir et lire le fichier d'entrée.
// 3. Pour chaque ligne du fichier d'entrée:
//    - Vérifier le format de la ligne.
//    - Extraire la date et la valeur.
//    - Valider la date et la valeur.
//    - Chercher le prix du bitcoin pour la date donnée ou la date la plus proche inférieure.
//    - Calculer le résultat de la valeur multipliée par le prix du bitcoin.
//    - Afficher le résultat ou les messages d'erreur appropriés.

// ### Points importants à noter

// - Utiliser une structure de données appropriée pour stocker les prix du bitcoin. Un dictionnaire où les clés sont des dates et les valeurs sont les prix peut être très efficace.
// - Manipuler les dates avec une bibliothèque appropriée pour éviter les erreurs de formatage et pour faciliter la comparaison des dates.
// - Gérer les exceptions et les erreurs d'entrée de manière élégante pour fournir des messages d'erreur utiles à l'utilisateur.
// - Suivre les règles du programme imposées par l'exercice, notamment le nom du programme et le format des fichiers.

// En suivant ces étapes et en respectant les spécifications, tu devrais être en mesure de réaliser cet exercice avec succès. Bonne chance!