/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 12:06:56 by astutz            #+#    #+#             */
/*   Updated: 2024/06/29 14:00:43 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "easyfind.hpp"

int main() {
    std::vector<int> vec;

	vec.push_back(1);
	vec.push_back(3);
	vec.push_back(5);

    std::cout << "Contenu du vecteur : ";
    printVec(vec);

    try 
	{
        easyFind(vec, 3);
    }
	catch (const std::runtime_error& e)
	{
        std::cerr << "Erreur : " << e.what() << std::endl;
    }

    try 
	{
        easyFind(vec, 10);
    }
	catch (const std::runtime_error& e)
	{
        std::cerr << "Erreur : " << e.what() << std::endl;
    }

    return 0;
}
