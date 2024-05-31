/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 14:26:53 by astutz            #+#    #+#             */
/*   Updated: 2024/05/31 10:37:11 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"

// int main()
// {
// 	ClapTrap Edouard("Edourd");
// 	ClapTrap Gérard("Gérard");
// 	ClapTrap randomName = ClapTrap();

// 	while (Edouard.getHitPoints() > 0 || Gérard.getHitPoints() > 0 || randomName.getHitPoints() > 0)
// 	{
// 		Edouard.attack(Gérard.getName());
// 		Gérard.takeDamage(Edouard.getAttackDamage());
// 		randomName.attack(Gérard.getName());		
// 	}
	
// }

int	main(void)
{
	unsigned int	i = 1;
	ClapTrap	Louison("Louison");
	ClapTrap	Genievre("Genievre");
	std::cout << std::endl;

	Louison.getStats();
	Genievre.getStats();
	std::cout << std::endl;

	while (Genievre.getHitPoints() > 0)
	{
		Louison.setAttackDamage(i);
		Louison.attack("Genievre");
		Genievre.takeDamage(Louison.getAttackDamage());
		Genievre.beRepaired(2);
		i *= 3;
		std::cout << std::endl;
	}
	Louison.getStats();
	Genievre.getStats();
	std::cout << std::endl;
	return (0);
}