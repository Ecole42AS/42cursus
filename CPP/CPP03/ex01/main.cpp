/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 14:26:53 by astutz            #+#    #+#             */
/*   Updated: 2024/06/03 09:09:52 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"
#include "ScavTrap.hpp"

int	main()
{
	unsigned int	i = 1;
	ClapTrap	Louison("Louison");
	ClapTrap	Genievre("Genievre");
	ScavTrap	TrappyScavy("Trappy Scavy");
	std::cout << std::endl;

	Louison.getStats();
	Genievre.getStats();
	TrappyScavy.getStats();
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
	std::cout << std::endl;

	Louison.getStats();
	Genievre.getStats();
	TrappyScavy.getStats();
	std::cout << std::endl;
	return (0);
}