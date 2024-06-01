/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScavTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 16:11:06 by astutz            #+#    #+#             */
/*   Updated: 2024/06/01 11:09:15 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScavTrap.hpp"
#include "ClapTrap.hpp"


ScavTrap::ScavTrap() {}

ScavTrap::ScavTrap(std::string name) : ClapTrap(_name(name)) {}

ScavTrap::~ScavTrap()
{
	
}

ScavTrap::ScavTrap(const ScavTrap &src)
{
	
}

ScavTrap::ScavTrap &operator=(const ScavTrap &rhs)
{
	
}

void ScavTrap::guardGate()
{
	std::cout << "ScavTrap " << getName() << " is now in Gate keeper mode" << std::endl;
}
