/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanA.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 20:36:20 by astutz            #+#    #+#             */
/*   Updated: 2024/05/25 09:53:33 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HumanA.hpp"

HumanA::HumanA(std::string name, Weapon &w) : name(name), w(w) {}

HumanA::~HumanA(){}

void HumanA::attack()
{
	std::cout << name << " attacks with their " << w.getType() << std::endl;
}
