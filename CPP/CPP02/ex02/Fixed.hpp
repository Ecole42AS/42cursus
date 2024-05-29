/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 10:12:50 by astutz            #+#    #+#             */
/*   Updated: 2024/05/29 11:10:53 by astutz           ###   ########.fr       */
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
	int _nb2;
	static int const _fractionalBits = 8;
public:
	Fixed();
	~Fixed();
	Fixed(const Fixed &src);
	Fixed &operator=(const Fixed &rhs);
	Fixed(const int i);
	Fixed(const float f);
	int getRawBits() const;
	void setRawBits(int const raw);
	float toFloat() const;
	int toInt() const;
	static int &min(int &_nb, int &_nb2);
	static int &min(const int &_nb, const int &_nb2);
	static int &max(int &_nb, int &_nb2);
	static int &max(const int &_nb, const int &_nb2);
	
};

std::ostream &operator<<(std::ostream &os, const Fixed &rhs);
std::ostream &operator>(std::ostream &os, const Fixed &rhs);
std::ostream &operator<(std::ostream &os, const Fixed &rhs);
std::ostream &operator>=(std::ostream &os, const Fixed &rhs);
std::ostream &operator<=(std::ostream &os, const Fixed &rhs);
std::ostream &operator==(std::ostream &os, const Fixed &rhs);
std::ostream &operator!=(std::ostream &os, const Fixed &rhs);
std::ostream &operator+(std::ostream &os, const Fixed &rhs);
std::ostream &operator-(std::ostream &os, const Fixed &rhs);
std::ostream &operator*(std::ostream &os, const Fixed &rhs);
std::ostream &operator/(std::ostream &os, const Fixed &rhs);
