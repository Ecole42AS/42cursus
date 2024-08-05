/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ASpell.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 09:24:13 by astutz            #+#    #+#             */
/*   Updated: 2024/08/04 21:47:31 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include "ATarget.hpp"

class ATarget;
class ASpell
{
	protected:
		std::string _name;
		std::string _effects;
	public:
		ASpell();
		virtual ~ASpell();
		ASpell(std::string name, std::string effects);
		ASpell(const ASpell &src);
		ASpell &operator=(const ASpell &rhs);
		std::string getName() const;
		std::string getEffects() const;
		virtual ASpell *clone() const = 0;
		void launch(const ATarget &target) const;
};