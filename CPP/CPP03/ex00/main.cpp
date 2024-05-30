/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 14:26:53 by astutz            #+#    #+#             */
/*   Updated: 2024/05/30 15:56:27 by astutz           ###   ########.fr       */
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
	ClapTrap	Bob("Bob");
	ClapTrap	Optimus("Optimus");
	std::cout << std::endl;

	Bob.getStats();
	Optimus.getStats();
	std::cout << std::endl;

	while (Optimus.getHitPoints() > 0)
	{
		Bob.setAttackDamage(i);
		Bob.attack("Optimus");
		Optimus.takeDamage(Bob.getAttackDamage());
		Optimus.beRepaired(2);
		i *= 3;
		std::cout << std::endl;
	}
	Bob.getStats();
	Optimus.getStats();
	std::cout << std::endl;
	return (0);
}