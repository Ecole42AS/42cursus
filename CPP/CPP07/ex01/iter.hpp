/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iter.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 21:42:39 by astutz            #+#    #+#             */
/*   Updated: 2024/06/26 21:48:57 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>

template <typename T>

T arr[];
template <typename T>

T len = arr.length();
template <typename T>

void func(T arr[])
{
	for (size_t i = 0; i < ::len; i++)
	{
		func(arr[i]);
	}
	
}

void iter(T &a[], )