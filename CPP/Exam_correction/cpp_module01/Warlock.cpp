/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Warlock.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 17:07:36 by astutz            #+#    #+#             */
/*   Updated: 2024/08/05 19:28:17 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Warlock.hpp"

Warlock::Warlock() {}

Warlock::Warlock(const std::string &name, const std::string &title) : _name(name), _title(title)
{
	std::cout << _name << ": This looks like another boring day." << std::endl;
}

Warlock::~Warlock()
{
	std::cout << _name << ": My job here is done!" << std::endl;
}

Warlock::Warlock(const Warlock &src) : _name(src._name), _title(src._title) {}

Warlock &Warlock::operator=(const Warlock &rhs)
{
	if (this != &rhs)
	{
		_name = rhs._name;
		_title =rhs._title;
	}
	return *this;
}


const std::string &Warlock::getName() const
{
	return _name;
}

const std::string &Warlock::getTitle() const
{
	return _title;
}

void Warlock::setTitle(const std::string &title)
{
	_title = title;
}

void Warlock::introduce() const
{
	std::cout << _name << ": I am " << _name << ", " << _title << "!" << std::endl;
}


void Warlock::learnSpell(ASpell *spell)
{
	if (spell)	
		if (_spellBook.find(spell->getName()) == _spellBook.end())
			_spellBook[spell->getName()] = spell->clone();
}

void Warlock::forgetSpell(std::string spellName)
{
	if (_spellBook.find(spellName) != _spellBook.end())
		_spellBook.erase(_spellBook.find(spellName));
}

void Warlock::launchSpell(std::string spellName, const ATarget &target)
{
	if (_spellBook.find(spellName) != _spellBook.end())
		_spellBook[spellName]->launch(target);
}
