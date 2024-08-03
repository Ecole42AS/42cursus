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

PmergeMe::PmergeMe(const PmergeMe &src) : _array(src._array), _deque(src._deque) {}

PmergeMe &PmergeMe::operator=(const PmergeMe &rhs) {
    if (this != &rhs) {
        _array = rhs._array;
        _deque = rhs._deque;
    }
    return *this;
}

std::vector<int>& PmergeMe::getArray() {
    return _array;
}

void PmergeMe::setArrayCapacity(size_t capacity) {
    _array.reserve(capacity);
}

void PmergeMe::merge(const std::vector<int>& leftArray, const std::vector<int>& rightArray, std::vector<int>& array) {
    size_t leftSize = leftArray.size();
    size_t rightSize = rightArray.size();
    size_t i = 0, l = 0, r = 0;

    while (l < leftSize && r < rightSize) {
        if (leftArray[l] < rightArray[r]) {
            array[i++] = leftArray[l++];
        } else {
            array[i++] = rightArray[r++];
        }
    }

    while (l < leftSize) {
        array[i++] = leftArray[l++];
    }

    while (r < rightSize) {
        array[i++] = rightArray[r++];
    }
}

void PmergeMe::mergeSort(std::vector<int>& array, size_t length) {
    if (length <= 1)
		return;
    size_t middle = length / 2;
    std::vector<int> leftArray(array.begin(), array.begin() + middle);
    std::vector<int> rightArray(array.begin() + middle, array.end());

    mergeSort(leftArray, middle);
    mergeSort(rightArray, length - middle);
    merge(leftArray, rightArray, array);
}


// ******************************************DEQUE******************************************


std::deque<int>& PmergeMe::getDeque() {
    return _deque;
}

// void PmergeMe::setDequeCapacity(size_t capacity) {
//     _deque.reserve(capacity);
// }

// Fonction de fusion des déques
void PmergeMe::mergeDeque(const std::deque<int>& leftDeque, const std::deque<int>& rightDeque, std::deque<int>& deque) {
    size_t leftSize = leftDeque.size();
    size_t rightSize = rightDeque.size();
    size_t i = 0, l = 0, r = 0;

    // Fusionner les déques
    while (l < leftSize && r < rightSize) {
        if (leftDeque[l] < rightDeque[r]) {
            deque[i++] = leftDeque[l++];
        } else {
            deque[i++] = rightDeque[r++];
        }
    }

    // Copier les éléments restants de leftDeque, s'il y en a
    while (l < leftSize) {
        deque[i++] = leftDeque[l++];
    }

    // Copier les éléments restants de rightDeque, s'il y en a
    while (r < rightSize) {
        deque[i++] = rightDeque[r++];
    }
}

// Fonction de tri par fusion
void PmergeMe::mergeSortDeque(std::deque<int>& deque) {
    size_t length = deque.size();
    if (length <= 1) return; // Cas de base

    size_t middle = length / 2;
    std::deque<int> leftDeque(deque.begin(), deque.begin() + middle);
    std::deque<int> rightDeque(deque.begin() + middle, deque.end());

    mergeSortDeque(leftDeque);
    mergeSortDeque(rightDeque);

    // Merge the sorted halves back into the original deque
    mergeDeque(leftDeque, rightDeque, deque);
}