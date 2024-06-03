/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 10:17:03 by astutz            #+#    #+#             */
/*   Updated: 2024/06/03 17:03:52 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"
#include "Brain.hpp"

Dog::Dog() : Animal("Dog")
{
	std::cout << "Dog default constructor called" << std::endl;
	_Brain = new Brain();
}

Dog::~Dog()
{
	std::cout << "Dog destructor called" << std::endl;
	delete _Brain;
}

Dog::Dog(const Dog &src) : Animal(src), _Brain(new Brain(*src._Brain))
{
    std::cout << "Dog copy constructor called" << std::endl;
}


Dog &Dog::operator=(const Dog &rhs)
{
	std::cout << "Dog copy assignment operator called" << std::endl;
	if (this != &rhs)
	{
		Animal::operator=(rhs);
		*_Brain = *rhs._Brain;
	}
	return *this;
}

void Dog::makeSound() const
{
	std::cout << "Woooooof" << std::endl;
}