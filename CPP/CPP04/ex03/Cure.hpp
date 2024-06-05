/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cure.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 11:19:01 by astutz            #+#    #+#             */
/*   Updated: 2024/06/05 11:26:15 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "AMateria.hpp"

class Cure : public AMateria
{
public:
	Cure();
	~Cure();
	Cure(std::string name);
	Cure(const Cure &src);
	Cure &operator=(const Cure &rhs);
	AMateria* clone() const;
	void use(ICharacter& target);
};