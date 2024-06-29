/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.hpp                               			:+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 14:02:35 by astutz            #+#    #+#             */
/*   Updated: 2024/06/29 14:02:35 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include <vector>
#include <algorithm>

class Span {
private:
	unsigned int _maxSize;
    std::vector<int> _vec;
public:
    Span();
    Span(unsigned int N);
    ~Span();
    Span(const Span &src);
    Span &operator=(const Span &rhs);
	const std::vector<int> &getVec() const;
	void addNumber(int n);
  	int shortestSpan() const;
	int longestSpan() const;
};

