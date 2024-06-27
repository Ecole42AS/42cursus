/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iter.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 21:42:39 by astutz            #+#    #+#             */
/*   Updated: 2024/06/27 09:13:43 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>

template <typename T, typename F>

void iter(T *arr, size_t len, F func)
{
	for (size_t i = 0; i < len; i++)
	{
		func(arr[i]);
	}
}

template <typename T>
void print(const T &element)
{
	std::cout << element << std::endl;
}

template <typename T>
void increment(T &element) {
    ++element;
}
