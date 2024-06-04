/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 09:46:45 by astutz            #+#    #+#             */
/*   Updated: 2024/06/04 11:10:01 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include <string>

class Animal
{
protected:
	std::string _type;
public:
	Animal();
	Animal(std::string type);
	virtual ~Animal();
	Animal(const Animal &src);
	Animal &operator=(const Animal &rhs);
	virtual void makeSound() const;
	std::string getType() const;
};
