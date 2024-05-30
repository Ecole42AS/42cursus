/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 10:12:22 by astutz            #+#    #+#             */
/*   Updated: 2024/05/30 11:56:29 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

Fixed::Fixed() : _nb(0) {}

Fixed::~Fixed() {}

Fixed::Fixed(const Fixed &src)
{
	*this = src;
}

Fixed &Fixed::operator=(const Fixed &rhs)
{
	if (this != &rhs)
		this->_nb = rhs.getRawBits();
	return *this;
}

//donne l entier avant la virgule
Fixed::Fixed(const int i)
{
	_nb = i << _fractionalBits;
}

//Ce constructeur convertit efficacement un nombre à virgule flottante en une représentation fixe à virgule fixe en tenant compte du nombre de bits fractionnaires spécifié par _fractionalBits.
Fixed::Fixed(const float f)
{
	_nb = roundf(f * (1 << _fractionalBits));// roundf(f * 256)
}


int Fixed::getRawBits() const
{
    return _nb;
}

void Fixed::setRawBits(int const raw)
{
    _nb = raw;
}

float Fixed::toFloat() const
{
	return ((float)_nb / (1 << _fractionalBits));
}

int Fixed::toInt() const
{
	return (_nb >> _fractionalBits);
}

std::ostream &operator<<(std::ostream &os, const Fixed &rhs) {
	os << rhs.toFloat(); // Affiche la valeur convertie (_nb) de l'objet rhs
	return os;
}

bool	Fixed::operator>(const Fixed &nb) const
{
	return (this->toFloat() > nb.toFloat());
}

bool	Fixed::operator<(const Fixed &nb) const
{
	return (this->toFloat() < nb.toFloat());
}

bool	Fixed::operator>=(const Fixed &nb) const
{
	return (this->toFloat() >= nb.toFloat());
}

bool	Fixed::operator<=(const Fixed &nb) const
{
	return (this->toFloat() <= nb.toFloat());
}

bool	Fixed::operator==(const Fixed &n) const
{
	return (this->toFloat() == n.toFloat());
}

bool	Fixed::operator!=(const Fixed &n) const
{
	return (this->toFloat() != n.toFloat());
}

Fixed	Fixed::operator+(const Fixed &n) const
{
	return (Fixed(this->toFloat() + n.toFloat()));
}

Fixed	Fixed::operator-(const Fixed &n) const
{
	return (Fixed(this->toFloat() - n.toFloat()));
}

Fixed	Fixed::operator*(const Fixed &n) const
{
	return (Fixed(this->toFloat() * n.toFloat()));
}

Fixed	Fixed::operator/(const Fixed &n) const
{
	return (Fixed(this->toFloat() / n.toFloat()));
}


Fixed	&Fixed::operator++(void)
{
	setRawBits(getRawBits() + 1);
	return (*this);
}

Fixed	Fixed::operator++(int)
{
	Fixed	z = (*this);
	setRawBits(getRawBits() + 1);
	return (z);
}

Fixed	&Fixed::operator--(void)
{
	setRawBits(getRawBits() + 1);
	return (*this);
}

Fixed	Fixed::operator--(int)
{
	Fixed	z = (*this);
	setRawBits(getRawBits() + 1);
	return (z);
}

Fixed	&Fixed::min(Fixed &nb, Fixed &nb2)
{
	if (nb < nb2)
		return nb;
	return nb2;
}

Fixed const	&Fixed::min(const Fixed &nb, const Fixed &nb2)
{
	if (nb < nb2)
		return nb;
	return nb2;
}

Fixed	&Fixed::max(Fixed &nb, Fixed &nb2)
{
	if (nb > nb2)
		return nb;
	return nb2;
}

Fixed const	&Fixed::max(const Fixed &nb, const Fixed &nb2)
{
	if (nb > nb2)
		return nb;
	return nb2;
}