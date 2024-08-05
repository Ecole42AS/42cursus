/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ATarget.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 09:39:26 by astutz            #+#    #+#             */
/*   Updated: 2024/08/04 13:11:06 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include "ASpell.hpp"

class ASpell;
class ATarget
{
	protected:
		std::string _type;
	public:
		ATarget();
		virtual ~ATarget();
		ATarget(std::string type);
		ATarget(const ATarget &src);
		ATarget &operator=(const ATarget &rhs);
		const std::string &getType() const;
		void getHitBySpell(const ASpell &spell) const;
		virtual ATarget *clone() const = 0;	
};