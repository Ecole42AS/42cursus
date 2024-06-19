/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Test2.cpp                               			:+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 15:37:49 by astutz            #+#    #+#             */
/*   Updated: 2024/06/19 15:37:49 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Test2.hpp"

Test2::Test2()
{
    // Constructor implementation
}

Test2::~Test2()
{
    // Destructor implementation
}

Test2::Test2(const Test2 &src)
{
    *this = src;
}

Test2 &Test2::operator=(const Test2 &rhs)
{
    if (this != &rhs) {
        // Copy assignment implementation
        // Example: member_variable = rhs.member_variable;
    }
    return *this;
}

