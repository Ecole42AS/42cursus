/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 10:49:39 by astutz            #+#    #+#             */
/*   Updated: 2024/06/04 09:28:38 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "Animal.hpp"
#include "Brain.hpp"

class Dog : public Animal
{
private:
	Brain *_Brain;
public:
	Dog();
	virtual ~Dog();
	Dog(const Dog &src);
	Dog &operator=(const Dog &rhs);
	void makeSound() const;
	Brain *getBrain(void) const;
};
