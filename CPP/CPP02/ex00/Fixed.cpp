/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 11:07:42 by astutz            #+#    #+#             */
/*   Updated: 2024/05/27 21:29:06 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

Fixed::Fixed()
{
	std::cout << "Default constructor called" << std::endl;
}

Fixed::~Fixed() {}

Fixed::Fixed(Fixed const &src)
{
	std::cout << "Copy constructor called" << std::endl;
}

Fixed &Fixed::operator=(Fixed const &rhs)
{
	if (this != &rhs)
	{
		std::cout << "Copy assignment operator called" << std::endl;
		this->_decimalBits = rhs.getRawBits();

		return *this;
	}
}

int Fixed::getRawBits() const
{
	std::cout << "getRawBits member function called" << std::endl;
	return (_decimalBits);
}

void Fixed::setRawBits(int const newDecimalBits)
{
	std::cout << "setRawBits member function called" << std::endl;
	_decimalBits = newDecimalBits;

}