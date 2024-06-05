/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ICharacter.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 09:45:24 by astutz            #+#    #+#             */
/*   Updated: 2024/06/05 14:42:11 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once
// #include "AMateria.hpp"
#include <string>
#include <iostream>

class AMateria; //sinon erreur ICharacter.hpp:21:28: error: ‘AMateria’ has not been declared virtual void equip(AMateria* m) = 0; cela est une déclaration anticipée
class ICharacter
{
public:
	virtual ~ICharacter() {}
	virtual std::string const & getName() const = 0;
	virtual void equip(AMateria* m) = 0;
	virtual void unequip(int idx) = 0;
	virtual void use(int idx, ICharacter& target) = 0;
};
