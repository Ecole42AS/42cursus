/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanB.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 08:53:22 by astutz            #+#    #+#             */
/*   Updated: 2024/05/25 12:57:56 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HumanB.hpp"

HumanB::HumanB(std::string name): w(NULL), name(name) {}

HumanB::~HumanB() {}

void	HumanB::attack()
{
	if (w != NULL)
		std::cout << name << " attacks with their " << w->getType() << std::endl;
	else
		std::cout << name << " has no weapon..." << std::endl;
}

void	HumanB::setWeapon(Weapon &w)
{
		this->w = &w;
}
