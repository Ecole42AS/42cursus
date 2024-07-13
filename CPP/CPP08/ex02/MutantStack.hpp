/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MutantStack.hpp                               			:+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 18:42:39 by astutz            #+#    #+#             */
/*   Updated: 2024/07/03 18:42:39 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include <stack>

template <typename T>
class MutantStack : public std::stack<T>
{
public:
	MutantStack<T>();
	~MutantStack<T>();
	MutantStack<T>(const MutantStack &src);
	MutantStack<T> &operator=(const MutantStack &rhs);
	typedef typename std::stack<T>::container_type::iterator iterator;
	iterator begin();
	iterator end();
};