/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 12:31:35 by astutz            #+#    #+#             */
/*   Updated: 2024/05/30 15:57:28 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"


ClapTrap::ClapTrap(): _name("randomName"), _hitPoints((unsigned int)10), _energyPoints((unsigned int)10), _attackDamage((unsigned int)0)
{
	std::cout << "Default constructor called" << std::endl;	
}

ClapTrap::ClapTrap(std::string name) : _name(name), _hitPoints((unsigned int)10), _energyPoints((unsigned int)10), _attackDamage((unsigned int)0)
{
		std::cout << "name constructor called" << std::endl;	
}

ClapTrap::~ClapTrap()
{
	std::cout << "Destructor called" << std::endl;
}

ClapTrap::ClapTrap(const ClapTrap &src)
{
	std::cout << "Copy constructor called" << std::endl;
	*this = src;
}

ClapTrap &ClapTrap::operator=(const ClapTrap &rhs)
{
	std::cout << "Copy assignment operator called" << std::endl;
	if(this != &rhs)
	{
		_name = rhs._name;
		_hitPoints = rhs._hitPoints;
		_energyPoints = rhs._energyPoints;
		_attackDamage = rhs._attackDamage;
	}
	return (*this);
}


void ClapTrap::attack(const std::string& target)
{
	if (_hitPoints == 0)
		std::cout << "ClapTrap " << _name << " is already dead !" << std::endl;
	else if (_energyPoints == 0)
		std::cout << "ClapTrap " << _name << " has no more energy !" << std::endl;
	else
	{
		std::cout << "ClapTrap " << _name << " attacks " << target << " causing " << _attackDamage << " points of damage!" << std::endl;
		_energyPoints--;
	}
	return;
}

void ClapTrap::takeDamage(unsigned int amount)
{
	if (_hitPoints == 0)
		std::cout << "ClapTrap " << _name << " is already dead !" << std::endl;
	else if (_hitPoints <= amount)
		std::cout << "ClapTrap " << _name << " has no more life, he takes too much damage, he DIED !" << std::endl;
	else
	{
		_hitPoints -= amount;
		std::cout << "ClapTrap " << _name << " takes " << amount << " points of damage and has now " << _hitPoints << " points of life left." << std::endl;
	}
	return;	
}

void ClapTrap::beRepaired(unsigned int amount)
{
	if (_hitPoints == 0)
		std::cout << "ClapTrap " << _name << " is already dead !" << std::endl;
	else if (_energyPoints == 0)
		std::cout << "ClapTrap " << _name << " has no more energy !" << std::endl;
	else
	{
		_hitPoints += amount;
		_energyPoints--;
		std::cout << "ClapTrap " << _name << " be repaired of " << amount << " points of life !" << std::endl;
		std::cout << "He has now " << _hitPoints << " life points and " << _energyPoints << " energy points left !" << std::endl;
	}
	return;		
}

std::string ClapTrap::getName() const
{
	return _name;
}

void ClapTrap::setAttackDamage(unsigned int amount)
{
	_attackDamage = amount;
	return;
}

unsigned int ClapTrap::getAttackDamage() const
{
	return _attackDamage;
}

unsigned int ClapTrap::getEnergyPoints() const
{
	return _energyPoints;
}

unsigned int ClapTrap::getHitPoints() const
{
	return _hitPoints;
}

void ClapTrap::getStats() const
{
	std::cout << "Name: " << _name << std::endl;
	std::cout << "Life points: " << _hitPoints << std::endl;
	std::cout << "Energy points: " << _energyPoints << std::endl;
	std::cout << "AttackDamage: " << _attackDamage << std::endl;
}