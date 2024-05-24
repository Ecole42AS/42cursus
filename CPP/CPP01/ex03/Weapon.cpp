/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 20:50:13 by astutz            #+#    #+#             */
/*   Updated: 2024/05/24 20:59:09 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Weapon.hpp"


Weapon::Weapon() {}

Weapon::~Weapon() {}

const &Weapon::getType()
{
	const &typeREF = type;
	return (typeREF);
}

void Weapon::getType(std::string newType)
{
	type = newType;
	return;
}
