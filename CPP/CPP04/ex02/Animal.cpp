/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 09:50:39 by astutz            #+#    #+#             */
/*   Updated: 2024/06/04 11:09:20 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "Animal.hpp"

// Animal::Animal() : _type("Animal")
// {
// 	std::cout << "Animal default constructor called" << std::endl;
// }

// Animal::Animal(std::string type) : _type(type)
// {
// 	std::cout << "Type animal constructor called" << std::endl;
// }

// Animal::~Animal()
// {
// 	std::cout << "Animal destructor called" << std::endl;
// }

// Animal::Animal(const Animal &src)
// {
// 	std::cout << "Animal copy constructor called" << std::endl;
// 	*this = src;
// }

// Animal &Animal::operator=(const Animal &rhs)
// {
//     std::cout << "Animal copy assignment operator called" << std::endl;
// 	if (this != &rhs)
// 		_type = rhs._type;
// 	return *this;
// }

// // void Animal::makeSound() const
// // {
// // 	std::cout << "No sound's emitted.." << std::endl;
// // }

// std::string Animal::getType() const
// {
// 	return _type;
// }

// Animal.cpp
#include "Animal.hpp"

Animal::Animal() : _type("Animal")
{
    std::cout << "Animal default constructor called" << std::endl;
}

Animal::Animal(std::string type) : _type(type)
{
    std::cout << "Type animal constructor called" << std::endl;
}

Animal::~Animal()
{
    std::cout << "Animal destructor called" << std::endl;
}

Animal::Animal(const Animal &src)
{
    std::cout << "Animal copy constructor called" << std::endl;
    *this = src;
}

Animal &Animal::operator=(const Animal &rhs)
{
    std::cout << "Animal copy assignment operator called" << std::endl;
    if (this != &rhs)
        _type = rhs._type;
    return *this;
}

std::string Animal::getType() const
{
    return _type;
}