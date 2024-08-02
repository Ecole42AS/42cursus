/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 13:21:56 by astutz            #+#    #+#             */
/*   Updated: 2024/08/02 13:26:00 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int main() {
    int array[] = {8, 2, 5, 3, 4, 7, 6, 1};
    int length = sizeof(array) / sizeof(array[0]);

	PmergeMe pmergeMe;
    pmergeMe.mergeSort(array, length);

    for (int i = 0; i < length; ++i) {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}