/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ice.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 10:26:29 by astutz            #+#    #+#             */
/*   Updated: 2024/06/05 14:54:51 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "AMateria.hpp"
#include "ICharacter.hpp"


class Ice : public AMateria
{
public:
	Ice();
	~Ice();
	Ice(const Ice &src);
	Ice &operator=(const Ice &rhs);
	AMateria* clone() const;
	void use(ICharacter& target);
};
