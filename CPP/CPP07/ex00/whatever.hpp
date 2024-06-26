/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   whatever.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 19:16:27 by astutz            #+#    #+#             */
/*   Updated: 2024/06/26 21:30:31 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>


template <typename T>

void swap(T &a, T &b)
{
	T tmp;
	tmp = a;
	a = b;
	b = tmp;
}

template <typename T>

const T min(const T a, const T b)
{
	if (a < b)
		return a;
	else
		return b;
}

template <typename T>

const T max(const T a, const T b)
{
	if (a > b)
		return a;
	else
		return b;
}
