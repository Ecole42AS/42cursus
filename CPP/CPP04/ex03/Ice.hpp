/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ice.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 10:26:29 by astutz            #+#    #+#             */
/*   Updated: 2024/06/05 10:31:38 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "AMateria.hpp"

class Ice : public AMateria
{
private:
	std::string _name;
public:
	Ice();
	~Ice();
	Ice(std::string name);
	Ice(const Ice &src);
	Ice &operator=(const Ice &rhs);
	AMateria* clone() const;
	void use(ICharacter& target);
};
