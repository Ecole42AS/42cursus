/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AMateria.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 10:38:38 by astutz            #+#    #+#             */
/*   Updated: 2024/06/05 15:10:07 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include <string>
#include "ICharacter.hpp"

//Les Materias sont des sorts
class AMateria
{
protected:
	std::string type;
public:
	AMateria();
	AMateria(std::string const &type);
	virtual ~AMateria();
	AMateria(const AMateria &src);
	AMateria &operator=(const AMateria &rhs);
	std::string const &getType() const; //Returns the materia type
	virtual AMateria *clone() const = 0;
	virtual void use(ICharacter& target);
};
