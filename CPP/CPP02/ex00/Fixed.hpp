/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 10:31:24 by astutz            #+#    #+#             */
/*   Updated: 2024/05/31 14:14:31 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include <string>

class Fixed
{
private:
	int _decimalBits; //valeur brute du nombre en virgule fixe. Cette valeur est stockée sous forme d'un entier et est utilisée pour représenter à la fois la partie entière et la partie fractionnaire du nombre.
	static int const _fractionalBits = 8; //nb de bit utiliser pour représenter les chiffres après la virgule
public:
	Fixed();
	~Fixed();
	Fixed(Fixed const &src); //constructeur par copie 
	Fixed &operator=(Fixed const &rhs); //rhs = right-hand side, opérateur d'assignation par copie, est utilisée pour copier les valeurs d'un objet à un autre déjà existant de la même classe.(utile pour des ressources dynamiques)
	int getRawBits() const;
	void setRawBits(int const raw);

};