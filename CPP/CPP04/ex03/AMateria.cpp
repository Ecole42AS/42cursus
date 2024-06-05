/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AMateria.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 09:41:26 by astutz            #+#    #+#             */
/*   Updated: 2024/06/05 15:53:28 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AMateria.hpp"

AMateria::AMateria() : type("default")
{
	std::cout << "AMateria default constructor called" << std::endl;
}

AMateria::AMateria(std::string const &type) : type(type)
{
	std::cout << "AMateria type constructor called" << std::endl;
}

AMateria::~AMateria()
{
	std::cout << "AMateria destructor called" << std::endl;
}

AMateria::AMateria(const AMateria &src)
{
	std::cout << "AMateria copy constructor called" << std::endl;
	*this = src;
}

AMateria &AMateria::operator=(const AMateria &rhs)
{
	std::cout << "AMateria copy assignment operator called" << std::endl;
	if (this != &rhs)
		type = rhs.type;
	return (*this);
}

std::string const & AMateria::getType() const
{
	return (type);
}

void AMateria::use(ICharacter& target)
{
	std::cout << target.getName() << " is using " << type << std::endl;
}


// AMateria type constructor called
// Ice default constructor called
// AMateria type constructor called
// Cure default constructor called
// Character me constructor called
// AMateria copy constructor called
// AMateria copy assignment operator called
// Ice copy constructor called
// Ice copy assignment operator called
// me equip the ice material in the slot number 0.
// AMateria copy constructor called
// AMateria copy assignment operator called
// Cure copy constructor called
// Cure copy assignment operator called
// me equip the cure material in the slot number 1.
// Character bob constructor called
// meuses 0x559563ba53d0 against bob
// * shoots an ice bolt at bob *
// meuses 0x559563ba5400 against bob
// * heals bob's wounds *
// Character bob destructor called
// Character me destructor called
// Ice destructor called
// AMateria destructor called
// Cure destructor called
// AMateria destructor called
// Ice destructor called
// AMateria destructor called
// Cure destructor called
// AMateria destructor called

// AMateria type constructor called
// Ice default constructor called
// AMateria type constructor called
// Cure default constructor called
// Character me constructor called
// AMateria copy constructor called
// AMateria copy assignment operator called
// Ice copy constructor called
// Ice copy assignment operator called
// me equip the ice material in the slot number 0.
// AMateria copy constructor called
// AMateria copy assignment operator called
// Cure copy constructor called
// Cure copy assignment operator called
// me equip the cure material in the slot number 1.
// Character bob constructor called
// meuses 0x5636b4ab53d0 against bob
// * shoots an ice bolt at bob *
// meuses 0x5636b4ab5400 against bob
// * heals bob's wounds *
// Character bob destructor called
// Character me destructor called
// Ice destructor called
// AMateria destructor called
// Cure destructor called
// AMateria destructor called
// Ice destructor called
// AMateria destructor called
// Cure destructor called
// AMateria destructor called