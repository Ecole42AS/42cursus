/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FragTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 09:19:38 by astutz            #+#    #+#             */
/*   Updated: 2024/06/03 09:23:10 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FragTrap.hpp"
#include "ClapTrap.hpp"

FragTrap::FragTrap() : ClapTrap("default")
{
	_hitPoints = 100;
	_energyPoints = 100;
	_attackDamage = 30;
	std::cout << "A new FragTrap is created. It is.... " << _name << "!" << std::endl;

}

FragTrap::FragTrap(std::string name) : ClapTrap(name)
{
	_hitPoints = 100;
	_energyPoints = 100;
	_attackDamage = 30;
	std::cout << "A new FragTrap is created. It is.... " << _name << "!" << std::endl;
}

FragTrap::~FragTrap()
{
	std::cout << "Destructor called (FragTrap)" << std::endl;
}

FragTrap::FragTrap(const FragTrap &src) : ClapTrap(src)
{
	std::cout << "Copy constructor called (FragTrap)" << std::endl;
	*this = src;
}

FragTrap &FragTrap::operator=(const FragTrap &rhs) {
    std::cout << "Copy assignment operator called (FragTrap)" << std::endl;
    if (this != &rhs)
        ClapTrap::operator=(rhs);
    return *this;
}

void FragTrap::highFivesGuys(void)
{
	std::cout << "FragTrap " << getName() << " is asking for a high five !" << std::endl;
}
