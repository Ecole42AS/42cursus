/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Array.hpp                               			:+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 10:45:01 by astutz            #+#    #+#             */
/*   Updated: 2024/06/27 10:45:01 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>

template <typename T>
class Array {
private:

public:
    Array<T>();
    Array<T>(size_t len);
    ~Array<T>();
    Array<T>(const Array &src);
    Array<T> &operator=(const Array &rhs);
};

Array::Array<T>()
{
	
}

Array::Array<T>(size_t len)
{

}

Array::~Array<T>()
{

}

Array::Array<T>(const Array &src)
{

}

Array::Array<T> &operator=(const Array &rhs)
{

}
