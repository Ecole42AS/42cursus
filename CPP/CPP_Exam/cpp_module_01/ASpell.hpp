/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ASpell.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 09:24:13 by astutz            #+#    #+#             */
/*   Updated: 2024/08/04 10:23:54 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>

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
		Aspell(const ASpell &src);
		Aspell &operator=(const Aspell &rhs);
		std::string getName() const;
		std::string getEffects() const;
		virtual Aspell *clone() const = 0;
		void launch(const ATarget &target) const;
};