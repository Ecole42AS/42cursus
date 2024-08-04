/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ATarget.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 10:14:57 by astutz            #+#    #+#             */
/*   Updated: 2024/08/04 10:23:03 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Atarget.hpp"

Atarget::Atarget()
{
	
}

virtual Atarget::~Atarget()
{
	
}

Atarget::Atarget(std::string type) : _type(type)
{

}

Atarget::ATarget(const Atarget &src) : _type(src._type), _effects(src._effects)
{
	
}

ATarget &Atarget::operator=(const ATarget &rhs)
{
	if (this != &rhs)
	{
		_type = rhs._type
		_effects = rhs._effects
	}
	return *this;
}

std::string Atarget::getType() const
{
	return _type;
}

void Atarget::getHitBySpell(const Aspell &spell) const
{
	
}
