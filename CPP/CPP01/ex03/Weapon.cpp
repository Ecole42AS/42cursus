/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 20:50:13 by astutz            #+#    #+#             */
/*   Updated: 2024/05/27 09:34:20 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Weapon.hpp"

Weapon::Weapon(std::string type): type(type) {}

Weapon::~Weapon() {}

const std::string &Weapon::getType()
{
	return (type);
}

void Weapon::setType(std::string newType)
{
	type = newType;
}
