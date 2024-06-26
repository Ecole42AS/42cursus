/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iter.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 21:42:39 by astutz            #+#    #+#             */
/*   Updated: 2024/06/26 22:11:59 by astutz           ###   ########.fr       */
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
