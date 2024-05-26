/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 18:33:23 by astutz            #+#    #+#             */
/*   Updated: 2024/05/26 11:23:34 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <fstream>

/*
référence qui permettent d'éviter les copie et améliore les perfs. 
l'autre avantage est qu'on ne peut pas modifier les valeurs des params
std::string::npos représente la valeur maximale possible pour une variable de type size_t 
qui est retournée par find si la chaine n'est pas trouvée
sinon c'est la première occurrence qui est retournée
*/
void replaceString(std::string& source, const std::string& s1, const std::string& s2) {
    size_t pos = 0;
    while ((pos = source.find(s1, pos)) != std::string::npos) {
        source.erase(pos, s1.length());
        source.insert(pos, s2);
        pos += s2.length();
    }
}

int main(int ac, char **av) {
    if (ac != 4) {
        std::cerr << "Usage: " << av[0] << " <filename> <s1> <s2>\n";
        return 1;
    }

    std::string filename = av[1];
    std::string s1 = av[2];
    std::string s2 = av[3];
    std::string line;

    /*
    ifstream: classe dans la librairie standard qui permet de lire un fichier via un de ses constructeurs
    (return true si bien ouvert)
    Utilisation de c_str() pour obtenir un pointeur const char* car la classe std::ifstream a besoin d'un pointeur vers le chemin du fichier
    */
    std::ifstream inputFile(filename.c_str());
    if (!inputFile) {
        std::cerr << "Error: Cannot open file " << filename << "\n";
        return 1;
    }

    // crée une instance(ou objet) de la classe ofstream qui permet d'écrire dans le fichier newFilename (file qui est créé grâce à l'objet)
    std::string newFilename = filename + ".replace";
    std::ofstream outputFile(newFilename.c_str());
    if (!outputFile) {
        std::cerr << "Error: Cannot create file " << newFilename << "\n";
        return 1;
    }

    // EOF entraîne le retour de false par getline
    while (std::getline(inputFile, line)) {
        replaceString(line, s1, s2);
        outputFile << line << std::endl;  // Écrire la ligne modifiée dans le fichier de sortie
    }

    inputFile.close();
    outputFile.close();

    return 0;
}
