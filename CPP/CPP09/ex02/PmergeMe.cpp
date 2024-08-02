/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                               			:+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 12:37:25 by astutz            #+#    #+#             */
/*   Updated: 2024/08/02 12:37:25 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {}

PmergeMe::~PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe &src)
{
    *this = src;
}

PmergeMe &PmergeMe::operator=(const PmergeMe &rhs)
{
    if (this != &rhs) {
		
    }
    return *this;
}

// Fonction de fusion des tableaux
void PmergeMe::merge(int* leftArray, int leftSize, int* rightArray, int rightSize, int* array) {
    int i = 0, l = 0, r = 0;

    // Fusionner les tableaux
    while (l < leftSize && r < rightSize) {
        if (leftArray[l] < rightArray[r]) {
            array[i++] = leftArray[l++];
        } else {
            array[i++] = rightArray[r++];
        }
    }

    // Copier les éléments restants de leftArray, s'il y en a
    while (l < leftSize) {
        array[i++] = leftArray[l++];
    }

    // Copier les éléments restants de rightArray, s'il y en a
    while (r < rightSize) {
        array[i++] = rightArray[r++];
    }
}

// Fonction de tri par fusion
void PmergeMe::mergeSort(int* array, int length) {
    if (length <= 1) return; // Cas de base

    int middle = length / 2;
    int* leftArray = new int[middle];
    int* rightArray = new int[length - middle];

    // Copier les données dans les tableaux temporaires
    for (int i = 0; i < middle; ++i) {
        leftArray[i] = array[i];
    }
    for (int i = middle; i < length; ++i) {
        rightArray[i - middle] = array[i];
    }

    mergeSort(leftArray, middle);
    mergeSort(rightArray, length - middle);
    merge(leftArray, middle, rightArray, length - middle, array);

    delete[] leftArray;
    delete[] rightArray;
}

