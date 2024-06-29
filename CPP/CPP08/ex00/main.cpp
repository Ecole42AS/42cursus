/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 12:06:56 by astutz            #+#    #+#             */
/*   Updated: 2024/06/29 13:55:26 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "easyfind.hpp" // Inclure le fichier d'en-tête contenant votre code

int main() {
    std::vector<int> vec;

	vec.push_back(1);
	vec.push_back(3);
	vec.push_back(5);

    // Tester la fonction printVec
    std::cout << "Contenu du vecteur : ";
    printVec(vec);

    // Tester la fonction easyFind avec une valeur présente dans le vecteur
    try {
        easyFind(vec, 3);
    } catch (const std::runtime_error& e) {
        std::cerr << "Erreur : " << e.what() << std::endl;
    }

    // Tester la fonction easyFind avec une valeur absente du vecteur
    try {
        easyFind(vec, 10);
    } catch (const std::runtime_error& e) {
        std::cerr << "Erreur : " << e.what() << std::endl;
    }

    return 0;
}
