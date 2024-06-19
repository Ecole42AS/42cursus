/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Hogur.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 15:34:37 by astutz            #+#    #+#             */
/*   Updated: 2024/06/19 15:34:37 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Hogur.hpp"
#include <iostream> // Example include

Hogur::Hogur()
{
    // Constructor implementation
}

Hogur::~Hogur()
{
    // Destructor implementation
}

Hogur::Hogur(const Hogur &src)
{
    *this = src;
}

Hogur &Hogur::operator=(const Hogur &rhs)
{
    if (this != &rhs) {
        // Copy assignment implementation
        // Example: member_variable = rhs.member_variable;
    }
    return *this;
}

