/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 14:26:53 by astutz            #+#    #+#             */
/*   Updated: 2024/06/03 09:35:58 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"
#include "ScavTrap.hpp"
#include "FragTrap.hpp"

//LIFO (construction et destruction fonctionne comme une stack)
int	main()
{
	unsigned int	i = 1;
	ClapTrap	Louison("Louison");
	ClapTrap	Genievre("Genievre");
	ScavTrap	TrappyScavy("Trappy Scavy");
	FragTrap	FraggyTrappy("Fraggy Trappy");
	std::cout << std::endl;

	Louison.getStats();
	Genievre.getStats();
	TrappyScavy.getStats();
	FraggyTrappy.getStats();
	std::cout << std::endl;

	while (Genievre.getHitPoints() > 0)
	{
		Louison.setAttackDamage(i);
		Louison.attack("Genievre");
		Genievre.takeDamage(Louison.getAttackDamage());
		Genievre.beRepaired(2);
		TrappyScavy.guardGate();
		i *= 3;
		std::cout << std::endl;
	}
	TrappyScavy.attack("Louison");
	Louison.takeDamage(TrappyScavy.getAttackDamage());
	FraggyTrappy.highFivesGuys();
	std::cout << std::endl;

	Louison.getStats();
	Genievre.getStats();
	TrappyScavy.getStats();
	FraggyTrappy.getStats();
	std::cout << std::endl;
	return (0);
}