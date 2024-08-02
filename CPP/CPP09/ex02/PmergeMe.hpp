/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                               			:+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 12:37:25 by astutz            #+#    #+#             */
/*   Updated: 2024/08/02 12:37:25 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include <vector>

class PmergeMe {
private:
    // Private members here
public:
    PmergeMe();
    ~PmergeMe();
    PmergeMe(const PmergeMe &src);
    PmergeMe &operator=(const PmergeMe &rhs);
	void merge(int* leftArray, int leftSize, int* rightArray, int rightSize, int* array);
	void mergeSort(int* array, int length);
};

