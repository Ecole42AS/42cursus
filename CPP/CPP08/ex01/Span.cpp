/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.cpp                               			:+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 14:02:35 by astutz            #+#    #+#             */
/*   Updated: 2024/06/29 14:02:35 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Span.hpp"

Span::Span() {}

Span::Span(unsigned int N)
{
	_vec.reserve(N);
	_maxSize = N;
}

Span::~Span() {}

Span::Span(const Span &src) : _vec(src._vec) {}

Span &Span::operator=(const Span &rhs)
{
    if (this != &rhs) {
		_vec = rhs._vec;
    }
    return *this;
}

const std::vector<int> &Span::getVec() const
{
	return _vec;
}

void Span::setVec(std::vector<int> vec)
{
	_vec = vec;
}

void Span::addNumber(int n)
{
	if (_vec.size() < _maxSize)
		_vec.push_back(n);
	else
		throw std::runtime_error("Vector is full");
}

int Span::shortestSpan() const {
    if (_vec.size() < 2) {
        throw std::runtime_error("Error: Cannot calculate shortest span: Span contains less than 2 numbers.");
    }

    std::vector<int> sortedVec(_vec);
    std::sort(sortedVec.begin(), sortedVec.end());

    int minSpan = sortedVec[1] - sortedVec[0];

    for (size_t i = 2; i < sortedVec.size(); ++i)
	{
        int span = sortedVec[i] - sortedVec[i - 1];
        if (span < minSpan)
            minSpan = span;
    }

    return minSpan;
}

int Span::longestSpan() const
{
    if (_vec.size() < 2) {
        throw std::runtime_error("Error: Cannot calculate longest span: Span contains less than 2 numbers.");
    }

    std::vector<int> sortedVec(_vec);
    std::sort(sortedVec.begin(), sortedVec.end());

    int maxSpan = sortedVec[1] - sortedVec[0];

    for (size_t i = 2; i < sortedVec.size(); ++i)
	{
        int span = sortedVec[i] - sortedVec[i - 1];
        if (span > maxSpan)
            maxSpan = span;
    }

    return maxSpan;
}

void Span::fillVec(std::vector<int>::iterator itBegin, std::vector<int>::iterator itEnd, int n)
{
	if (_vec.size() + std::distance(itBegin, itEnd) > _maxSize)
		throw std::runtime_error("You don't respect the max size !");
	for (; itBegin < itEnd; itBegin++)
	{
		std::vector<int> vec;
std::vector<int> source = {1, 2, 3, 4};

// Utilisation de std::copy avec std::back_inserter pour ajouter les éléments de source à vec
std::copy(source.begin(), source.end(), std::back_inserter(vec));

		// *itBegin = n;
		_vec.push_back(*itBegin + n);
	}		
}

void Span::printVec() const
{
	for (std::vector<int>::const_iterator it = _vec.begin(); it != _vec.end(); it++)
	{
		std::cout << *it << std::endl;
	}
}