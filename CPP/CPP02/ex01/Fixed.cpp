/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 10:12:22 by astutz            #+#    #+#             */
/*   Updated: 2024/05/28 10:50:49 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

Fixed::Fixed() : _decimalBits(0)
{
	std::cout << "Default constructor called" << std::endl;	
}

Fixed::~Fixed()
{
	std::cout << "Destructor called" << std::endl;
}

Fixed::Fixed(const Fixed &src)
{
	std::cout << "Copy constructor called" << std::endl;
	*this = src;
}



std::ostream &operator<<(std::ostream &os, const Fixed &rhs) {
	os << rhs.toFloat(); // Affiche la valeur brute (_decimalBits) de l'objet Fixed
	return os;
}