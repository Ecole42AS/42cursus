/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MutantStack.cpp                               			:+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 18:42:39 by astutz            #+#    #+#             */
/*   Updated: 2024/07/03 18:42:39 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "MutantStack.hpp"

template<typename T>
MutantStack<T>::MutantStack() {}

MutantStack::~MutantStack() {}

MutantStack::MutantStack(const MutantStack &src)
{
    *this = src;
}

MutantStack &MutantStack::operator=(const MutantStack &rhs)
{
    if (this != &rhs) {
		
    }
    return *this;
}

