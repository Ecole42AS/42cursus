/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanA.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 20:36:20 by astutz            #+#    #+#             */
/*   Updated: 2024/05/24 21:15:10 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Weapon.cpp"

HumanA::HumanA(Weapon)
{
	
}

HumanA::~HumanA()
{
}

void HumanA::attack()
{
	// Weapon w;
		std::cout << name << " attacks with their " << w.getType() << std::endl;
}
