/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 10:12:22 by astutz            #+#    #+#             */
/*   Updated: 2024/05/29 21:27:25 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

Fixed::Fixed() : _nb(0)
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
		this->_nb = rhs.getRawBits();
	return *this;
}

//Enlève la virgule(10.00)
Fixed::Fixed(const int i)
{
	std::cout << "Int constructor called" << std::endl;
	_nb = i << _fractionalBits;
}

//convertis un float(nombre a virgule flotante) en un nombre a virgule fixe
Fixed::Fixed(const float f)
{
	std::cout << "Float constructor called" << std::endl;
	_nb = roundf(f * (1 << _fractionalBits));// roundf(f * 256)
}


int Fixed::getRawBits() const
{
    return this->_nb;
}

void Fixed::setRawBits(int const raw)
{
    std::cout << "setRawBits member function called" << std::endl;
    this->_nb = raw;
}

float Fixed::toFloat() const
{
	return ((float)_nb / (1 << _fractionalBits)); //faire divisé par 256 pour maintenir la position de la ,
}

int Fixed::toInt() const
{
	return (_nb >> _fractionalBits); //donne la partie entière du nombre
}

std::ostream &operator<<(std::ostream &os, const Fixed &rhs) {
	os << rhs.toFloat(); // Affiche la valeur convertie (_nb) de l'objet rhs
	return os;
}