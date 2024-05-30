/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 10:12:50 by astutz            #+#    #+#             */
/*   Updated: 2024/05/30 11:54:23 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include <string>
#include <cmath>

class Fixed
{
private:
	int _nb;
	static int const _fractionalBits = 8;
public:
	Fixed();
	~Fixed();
	Fixed(const Fixed &src);
	Fixed &operator=(const Fixed &rhs);
	Fixed(const int i);
	Fixed(const float f);
	int 				getRawBits() const;
	void 				setRawBits(int const raw); 
	float 				toFloat() const;
	int 				toInt() const;
	static Fixed 		&min(Fixed &nb, Fixed &nb2);
	const static Fixed 	&min(const Fixed &nb, const Fixed &nb2);
	static Fixed		&max(Fixed &nb, Fixed &nb2);
	const static Fixed	&max(const Fixed &nb, const Fixed &nb2);
	bool 				operator>(const Fixed &nb) const;
	bool 				operator<(const Fixed &nb) const;
	bool				operator>=(const Fixed &nb) const;
	bool				operator<=(const Fixed &nb) const;
	bool				operator==(const Fixed &nb) const;
	bool				operator!=(const Fixed &nb) const;
	Fixed				operator+(const Fixed &nb) const;
	Fixed				operator-(const Fixed &nb) const;
	Fixed				operator*(const Fixed &nb) const;
	Fixed				operator/(const Fixed &nb) const;
	Fixed				&operator++(void);
	Fixed				operator++(int);
	Fixed				&operator--(void);
	Fixed				operator--(int);

	
};

std::ostream		&operator<<(std::ostream &os, const Fixed &rhs);

