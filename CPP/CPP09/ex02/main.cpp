/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 13:21:56 by astutz            #+#    #+#             */
/*   Updated: 2024/08/02 21:44:13 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int main(int ac, char **av) {
    PmergeMe pmergeMe;
    size_t length = ac - 1;

    if (ac == 1) {
        std::cerr << "Usage: ./PmergeMe [int1] [int2] [int3] ..." << std::endl;
        return 1;
    }

    pmergeMe.setArrayCapacity(length);
    std::vector<int>& array = pmergeMe.getArray(); // Utilisez la méthode modifiée ici

    std::cout << "Before: ";
    for (size_t i = 0; i < length; ++i) {
        int nb = std::atoi(av[i + 1]);
        if (nb == 0 && av[i + 1][0] != '0') {
            std::cerr << "Invalid number: " << av[i + 1] << std::endl;
            return 1;
        }
        array.push_back(nb);
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;

    pmergeMe.mergeSort(array, length);

    std::cout << "After: ";
    for (size_t i = 0; i < length; ++i) {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}
