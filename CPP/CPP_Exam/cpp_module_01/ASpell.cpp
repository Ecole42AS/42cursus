/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ASpell.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 09:59:33 by astutz            #+#    #+#             */
/*   Updated: 2024/08/04 10:18:13 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Aspell.hpp"

Aspell::ASpell()
{
	
}

virtual Aspell::~ASpell()
{
	
}

Aspell::ASpell(std::string name, std::string effects) : _name(name), _effects(effects)
{

}

Aspell::Aspell(const ASpell &src) : _name(src._name), _effects(src._effects)
{
	
}

Aspell &Aspell::operator=(const Aspell &rhs)
{
	if (this != &rhs)
	{
		_name = rhs._name
		_effects = rhs._effects
	}
	return *this;
}

std::string Aspell::getName() const
{
	return _name;
}

std::string Aspell::getEffects() const
{
	return _effects;
}

void Aspell::launch(const ATarget &target) const
{
	target.getHitBySpell();
}
