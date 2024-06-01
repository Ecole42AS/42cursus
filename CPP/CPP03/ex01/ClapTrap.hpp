/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 12:23:54 by astutz            #+#    #+#             */
/*   Updated: 2024/06/01 10:53:20 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include <string>

class ClapTrap
{
protected:
	std::string _name;
	unsigned int _hitPoints;
	unsigned int _energyPoints;
	unsigned int _attackDamage;
	
public:
	ClapTrap();
	~ClapTrap();
	ClapTrap(std::string name);
	ClapTrap(const ClapTrap &src);
	ClapTrap &operator=(const ClapTrap &rhs);
	void attack(const std::string& target);
	void takeDamage(unsigned int amount);
	void beRepaired(unsigned int amount);
	std::string getName() const;
	void setAttackDamage(unsigned int amount);
	unsigned int getAttackDamage() const;
	unsigned int getEnergyPoints() const;
	unsigned int getHitPoints() const;
	void getStats() const;
};
