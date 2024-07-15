/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 14:30:29 by astutz            #+#    #+#             */
/*   Updated: 2024/07/15 21:02:42 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Span.hpp"

// int main() {
	// try
	// {
	// 	Span sp = Span(8);
	// 	sp.addNumber(4);
	// 	sp.addNumber(8);
	// 	sp.addNumber(9);
	// 	std::cout << "size: " << sp.getVec().size() << std::endl;
	// 	std::cout << "Max size: " << sp.getMaxSize() << std::endl;
	// 	sp.printVec();
	// 	sp.fillVec((sp.getVec().begin()) + 4 , (sp.getVec().end()) - 1, 1);
	// }
	// catch(const std::exception& e)
	// {
	// 	std::cerr << e.what() << '\n';
	// }
	
	// Span sp = Span(6);
	// std::cout << "Capacity of vec: " << sp.getVec().capacity() << std::endl;
	// try
	// {
	// 	// std::vector<int>::iterator it = sp.getVec().begin() + 3;
	// 	// sp.fillVec(sp.getVec().begin(), sp.getVec().end(), 1);
	// 	// sp.fillVec(it, sp.getVec().end(), 1);
	// 	// sp.fillVec(it, 	sp.getVec().end(), 1);
	// 	// sp.fillVec(sp.setVec(sp.getVec()).begin(), sp.setVec(sp.getVec()).end(), 1);
	// 	sp.addNumber(4);
	// 	sp.addNumber(8);
	// 	sp.addNumber(9);
	// 	int longestSpan = sp.longestSpan();
	// 	int shortestSpan = sp.shortestSpan();
	// 	std::cout << "longestSpan: " << longestSpan << std::endl;
	// 	std::cout << "shortestSpan: " << shortestSpan << std::endl;
	// 	sp.printVec();
	// }
	// catch(const std::exception& e)
	// {
	// 	std::cerr << e.what() << '\n';
	// }
	// try
	// {
	// 	std::vector<int> vec;
	// 	vec.push_back(1);
	// 	vec.push_back(2);
	// 	Span sp2 = Span(4);
	// 	std::cout << "Capacity of vec: " << sp2.getVec().capacity() << std::endl;
	// 	std::cout << "Size of vec: " << sp2.getVec().size() << std::endl;
		

	// 	sp2.fillVec(vec.begin(), vec.end(), 3);
	// 	std::cout << "vec print : " << "sp2: " << sp2.getVec().at(1) << "vec: " << vec.at(1) << std::endl;
	// 	sp2.printVec();
	// }
	// catch(const std::exception& e)
	// {
	// 	std::cerr << e.what() << '\n';
	// }
	
	// try
	// {
	// 	Span sp3 = Span(6);
	// 	sp3.addNumber(1);
	// 	sp3.addNumber(2);
	// 	// sp3.setVec().assign(2, 2);
	// 	// sp3.printVec();
	// 	std::vector<int> vec3;
	// 	vec3.assign(4, 4);
	// 	std::cout << "before" << std::endl;
	// 	sp3.printVec();
	// 	sp3.fillVec(vec3.begin(), vec3.end(), 4);
	// 	// sp3.setVec(vec3);
	// 	std::cout << "Print sp3 : " << std::endl;
	// 	sp3.printVec();
	// }
	// catch(const std::exception& e)
	// {
	// 	std::cerr << e.what() << '\n';
	// }
	
	

//     return 0;
// }


int main() {
    try {
        Span sp = Span(3);
        sp.addNumber(4);
        sp.addNumber(8);
        sp.addNumber(9);

        std::cout << "capacity: " << sp.getVec().capacity() << std::endl;
        std::cout << "size: " << sp.getVec().size() << std::endl;
        std::cout << "Max size: " << sp.getMaxSize() << std::endl;
        
        // Vérification du premier élément du vecteur
        if (!sp.getVec().empty()) {
            std::vector<int>::iterator itBegin = sp.getVec().begin();
            std::cout << "itBegin: " << *itBegin << std::endl;
        } else {
            std::cerr << "Le vecteur est vide." << std::endl;
        }
        
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }

    return 0;
}
// int main() {
//     try {
//         Span sp = Span(3);
//         sp.addNumber(4);
//         sp.addNumber(8);
//         sp.addNumber(9);
// 		std::cout << "capacity: " << sp.getVec().capacity() << std::endl;
//         std::cout << "size: " << sp.getVec().size() << std::endl;
//         std::cout << "Max size: " << sp.getMaxSize() << std::endl;
//         // sp.printVec();
		
//         // Début à begin() + 4
//         std::vector<int>::iterator itBegin = sp.getVec().begin();
//         std::vector<int>::iterator itEnd = (sp.getVec().end()) - 1;

// 		std::cout << "itBegin: " << *itBegin << std::endl;
// 		std::cout << "itEnd: " << *itEnd << std::endl;
// 		// itBegin += sp.getVec().size();

//         // if (std::distance(itBegin, itEnd) >= 1) {
//         //     itBegin += sp.getVec().size();  // Déplacer l'itérateur de 4 positions
//         // }
		
//         // sp.fillVec(itBegin, itEnd, 1);

//         // Afficher le vecteur après remplissage
//         // sp.printVec();
//     } catch (const std::exception& e) {
//         std::cerr << e.what() << '\n';
//     }

//     return 0;
// }