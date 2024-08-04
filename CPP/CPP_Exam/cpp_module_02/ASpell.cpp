/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ASpell.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 09:59:33 by astutz            #+#    #+#             */
/*   Updated: 2024/08/04 12:38:44 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ASpell.hpp"

ASpell::ASpell()
{
	
}

ASpell::~ASpell()
{
	
}

ASpell::ASpell(std::string name, std::string effects) : _name(name), _effects(effects)
{

}

ASpell::ASpell(const ASpell &src) : _name(src._name), _effects(src._effects)
{
	
}

ASpell &ASpell::operator=(const ASpell &rhs)
{
	if (this != &rhs)
	{
		_name = rhs._name;
		_effects = rhs._effects;
	}
	return *this;
}

std::string ASpell::getName() const
{
	return _name;
}

std::string ASpell::getEffects() const
{
	return _effects;
}

void ASpell::launch(const ATarget &target) const
{
	target.getHitBySpell(*this);
}
