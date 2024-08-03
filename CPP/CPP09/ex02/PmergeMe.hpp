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
#include <deque>
#include <cstdlib>
#include <climits>

class PmergeMe {
private:
    std::vector<int> _array;
    std::deque<int> _deque;
public:
    PmergeMe();
    ~PmergeMe();
    PmergeMe(const PmergeMe &src);
    PmergeMe &operator=(const PmergeMe &rhs);
    
    void merge(const std::vector<int>& leftArray, const std::vector<int>& rightArray, std::vector<int>& array);
    void mergeSort(std::vector<int>& array, size_t length);
    std::vector<int>& getArray();
    void setArrayCapacity(size_t capacity);
	std::deque<int>& getDeque();
	void setDequeCapacity(size_t capacity);
	void mergeSortDeque(std::deque<int>& deque);
	void mergeDeque(const std::deque<int>& leftDeque, const std::deque<int>& rightDeque, std::deque<int>& deque);
};
