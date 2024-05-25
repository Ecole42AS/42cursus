/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanB.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 08:47:34 by astutz            #+#    #+#             */
/*   Updated: 2024/05/25 10:00:48 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Weapon.hpp"

class HumanB
{
private:
	Weapon *w;
	std::string name;
public:
	HumanB(std::string name);
	~HumanB();
	void	attack();
	void	setWeapon(Weapon &w);
};

