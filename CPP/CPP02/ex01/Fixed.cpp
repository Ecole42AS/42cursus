/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 10:12:22 by astutz            #+#    #+#             */
/*   Updated: 2024/05/28 12:03:51 by astutz           ###   ########.fr       */
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

Fixed &Fixed::operator=(const Fixed &rhs)
{
	std::cout << "Copy assignment operator called" << std::endl;
	if (this != &rhs)
		this->_decimalBits = rhs.getRawBits();
	return *this;
}

//donne l entier avant la virgule
Fixed::Fixed(const int i)
{
	std::cout << "Int constructor called" << std::endl;
	_decimalBits = i << _fractionalBits;
}

//Ce constructeur convertit efficacement un nombre à virgule flottante en une représentation fixe à virgule fixe en tenant compte du nombre de bits fractionnaires spécifié par _fractionalBits.
Fixed::Fixed(const float f)
{
	std::cout << "Float constructor called" << std::endl;
	_decimalBits = roundf(f * (1 << _fractionalBits));// roundf(f * 256)  //roundf arrondi au plus proche
}


int Fixed::getRawBits() const
{
    std::cout << "getRawBits member function called" << std::endl;
    return this->_decimalBits;
}

void Fixed::setRawBits(int const raw)
{
    std::cout << "setRawBits member function called" << std::endl;
    this->_decimalBits = raw;
}

	float toFloat() const;
	int toInt() const;

std::ostream &operator<<(std::ostream &os, const Fixed &rhs) {
	os << rhs.toFloat(); // Affiche la valeur convertie (_decimalBits) de l'objet rhs
	return os;
}