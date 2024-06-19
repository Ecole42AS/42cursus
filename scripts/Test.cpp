/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Test.cpp                               	:+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 15:36:50 by astutz            #+#    #+#             */
/*   Updated: 2024/06/19 15:36:50 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Test.hpp"

Test::Test()
{
    // Constructor implementation
}

Test::~Test()
{
    // Destructor implementation
}

Test::Test(const Test &src)
{
    *this = src;
}

Test &Test::operator=(const Test &rhs)
{
    if (this != &rhs) {
        // Copy assignment implementation
        // Example: member_variable = rhs.member_variable;
    }
    return *this;
}

