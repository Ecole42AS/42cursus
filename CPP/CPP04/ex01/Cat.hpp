/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 10:09:45 by astutz            #+#    #+#             */
/*   Updated: 2024/06/04 09:29:01 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "Animal.hpp"
#include "Brain.hpp"

class Cat : public Animal
{
private:
	Brain *_Brain;
public:
	Cat();
	virtual ~Cat();
	Cat(const Cat &src);
	Cat &operator=(const Cat &rhs);
	void makeSound() const;
	Brain *getBrain(void) const;
};

