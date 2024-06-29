/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   easyfind.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 16:27:47 by astutz            #+#    #+#             */
/*   Updated: 2024/06/29 13:52:52 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include <vector>
#include <exception>
#include <algorithm>
#include <sstream>

template <typename T>
std::string to_str(T value) {
    std::ostringstream os;
    os << value;
    return os.str();
}

void printVec(const std::vector<int>& vec) {
    for (std::vector<int>::const_iterator it = vec.begin(); it != vec.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

template<typename T>
void easyFind(T &container, int n)
{
    typename T::iterator it = std::find(container.begin(), container.end(), n);

    if (it != container.end())
    {
        std::cout << "First occurrence of " << n << " is at index " << std::distance(container.begin(), it) << std::endl;
    }
    else
    {
       throw std::runtime_error("No value found for " + to_str(n));
    }
}

// template <typename T>
// int easyFind(T &p1, int p2)
// {
// 	typename T::iterator it;
// 	for (it = p1.begin(); it != p1.end(); it++)
// 	{
// 		if (p2 == *it)
// 			return *it;
// 	}
// 	throw std::runtime_error("No value found for " + std::to_string(p2));
// }