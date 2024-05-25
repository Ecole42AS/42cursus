/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanA.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 20:59:42 by astutz            #+#    #+#             */
/*   Updated: 2024/05/25 09:52:15 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "Weapon.hpp"

class HumanA
{
private:
	Weapon &w;
	std::string name;
public:
	HumanA(std::string name, Weapon &w);
	~HumanA();
	void attack();
};
