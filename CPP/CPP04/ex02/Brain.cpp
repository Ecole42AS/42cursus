/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 12:22:27 by astutz            #+#    #+#             */
/*   Updated: 2024/06/03 17:29:22 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Brain.hpp"

Brain::Brain()
{
	std::cout << "Brain default constructor called" << std::endl;
}

Brain::~Brain()
{
	std::cout << "Brain destructor called" << std::endl;
}

Brain::Brain(const Brain &src)
{
	std::cout << "Brain copy constructor called" << std::endl;
	for (size_t i = 0; i < 100; i++)
		_ideas[i] = src._ideas[i];
	
	*this = src;
}

Brain &Brain::operator=(const Brain &rhs)
{
	std::cout << "Brain copy assignment operator called" << std::endl;
	if (this != &rhs)
	{
		for (size_t i = 0; i < 100; i++)
			_ideas[i] = rhs._ideas[i];
	}
	return *this;
}

const std::string* Brain::getIdea(int index) const {
        if (index >= 0 && index < 100)
            return &_ideas[index];
        else
			return NULL;
}

void Brain::setIdea(int index, const std::string &idea)
{
	if (index >=0 && index <= 100)
		_ideas[index] = idea;
	else
		std::cout << "Wrong index, choose between 0 and 100" << std::endl;;
	return;
}
