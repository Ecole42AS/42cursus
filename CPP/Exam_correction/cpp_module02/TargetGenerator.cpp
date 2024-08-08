/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TargetGenerator.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 21:54:49 by astutz            #+#    #+#             */
/*   Updated: 2024/08/06 17:08:58 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "TargetGenerator.hpp"

TargetGenerator::TargetGenerator()
{
	
}

TargetGenerator::~TargetGenerator()
{
}

TargetGenerator::TargetGenerator(const TargetGenerator &src) : _target(src._target)
{
}

TargetGenerator &TargetGenerator::operator=(const TargetGenerator &rhs)
{
	if (this != &rhs)
		_target = rhs._target;
	return *this;
}	

void TargetGenerator::learnTargetType(ATarget* target)
{
	if (target)
		_target[target->getType()] = target;
}


void TargetGenerator::forgetTargetType(std::string const &targetType)
{
	if (!targetType.empty())
	{
		if (_target.find(targetType) != _target.end())
			_target.erase(_target.find(targetType));
	}
}

ATarget* TargetGenerator::createTarget(std::string const &targetType)
{
	ATarget *target = NULL;
	if (!targetType.empty())
	{
		if (_target.find(targetType) != _target.end())
			target = _target[targetType];
	}
	return target;
}
