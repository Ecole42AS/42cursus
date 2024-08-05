/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SpellBook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 13:53:31 by astutz            #+#    #+#             */
/*   Updated: 2024/08/04 22:30:15 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SpellBook.hpp"

SpellBook::SpellBook()
{
	
}

SpellBook::~SpellBook()
{
	std::map<std::string, ASpell*>::iterator it = _spellBook.begin();
	for (; it != _spellBook.end(); ++it)
		delete it->second;
	_spellBook.clear();
}

SpellBook::SpellBook(const SpellBook &src)
{
	(void) src;
}

SpellBook &SpellBook::operator=(const SpellBook &rhs)
{
	(void) rhs;
	return *this;
}

void SpellBook::learnSpell(ASpell* spell)
{
	if (spell)
		if (_spellBook.find(spell->getName()) == _spellBook.end())
			_spellBook[spell->getName()] = spell->clone();
}	

void SpellBook::forgetSpell(std::string const &spellName)
{
   if (!spellName.empty())
    {
        std::map<std::string, ASpell*>::iterator it = _spellBook.find(spellName);

        if (it != _spellBook.end())
        {
            delete it->second;
            
            _spellBook.erase(it);
        }
    }
}

ASpell* SpellBook::createSpell(std::string const &spellName)//méthode de recherche de sort par rapport à son nom
{
	ASpell *tmp = NULL;
	if (!spellName.empty())
		if (_spellBook.find(spellName) != _spellBook.end())
			tmp = _spellBook[spellName];
	return tmp;
}

