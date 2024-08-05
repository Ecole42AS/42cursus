/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ATarget.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 10:14:57 by astutz            #+#    #+#             */
/*   Updated: 2024/08/04 13:07:25 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ATarget.hpp"

ATarget::ATarget()
{
	
}

ATarget::~ATarget()
{
	
}

ATarget::ATarget(std::string type) : _type(type)
{

}

ATarget::ATarget(const ATarget &src) : _type(src._type)
{
	
}

ATarget &ATarget::operator=(const ATarget &rhs)
{
	if (this != &rhs)
		_type = rhs._type;
	return *this;
}

const std::string &ATarget::getType() const
{
	return _type;
}

void ATarget::getHitBySpell(const ASpell &spell) const
{
	std::cout << _type << " has been " << spell.getEffects() << "!" << std::endl;
}
