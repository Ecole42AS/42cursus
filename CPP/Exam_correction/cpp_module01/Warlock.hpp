/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Warlock.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 16:55:28 by astutz            #+#    #+#             */
/*   Updated: 2024/08/05 19:27:55 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#pragma once
#include <iostream>
#include <map>
#include "ASpell.hpp"

class Warlock
{
	private:
		Warlock();
		Warlock(const Warlock &src);
		Warlock &operator=(const Warlock &rhs);
		std::string _name;
		std::string _title;
		std::map<std::string, ASpell *> _spellBook;
	public:
		~Warlock();
		Warlock(const std::string &name, const std::string &title);
		const std::string &getName() const;
		const std::string &getTitle() const;
		void setTitle(const std::string &title);
		void introduce() const;
		void learnSpell(ASpell *spell);
		void forgetSpell(std::string spellName);
		void launchSpell(std::string spellName, const ATarget &target);
};