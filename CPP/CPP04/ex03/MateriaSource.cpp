/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MateriaSource.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 13:23:17 by astutz            #+#    #+#             */
/*   Updated: 2024/06/05 16:15:55 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MateriaSource.hpp"

MateriaSource::MateriaSource() : _index(0) 
{
	std::cout << "MateriaSource default constructor called" << std::endl;
    for (int i = 0; i < MAX_STOCK_SIZE; ++i) 
    {
        _stock[i] = NULL;
    }
}

MateriaSource::MateriaSource(const MateriaSource &src) 
{
	std::cout << "MateriaSource copy constructor called" << std::endl;
    *this = src;
}

MateriaSource::~MateriaSource() 
{
	std::cout << "MateriaSource destructor called" << std::endl;
    for (int i = 0; i < MAX_STOCK_SIZE; ++i) 
    {
        delete _stock[i];
    }
}

MateriaSource &MateriaSource::operator=(const MateriaSource &rhs) 
{
	std::cout << "MateriaSource copy assignment operator called" << std::endl;
    if (this != &rhs) 
    {
        for (int i = 0; i < MAX_STOCK_SIZE; ++i) 
        {
            if (_stock[i] != NULL) 
            {
                delete _stock[i];
            }
            if (rhs._stock[i] != NULL) 
            {
                _stock[i] = rhs._stock[i]->clone();
            } 
            else 
            {
                _stock[i] = NULL;
            }
        }
        _index = rhs._index;
    }
    return *this;
}

void MateriaSource::learnMateria(AMateria *materia) 
{
    if (materia == NULL) 
    {
        return;
    }

    // Si le tableau n'est pas plein, ajouter la materia à l'emplacement vide
    for (int i = 0; i < MAX_STOCK_SIZE; ++i) 
    {
        if (_stock[i] == NULL) 
        {
            _stock[i] = materia;
            return;
        }
    }

    // Si le tableau est plein, supprimer la Materia à l'emplacement _index
    delete _stock[_index];
    _stock[_index] = materia;
    _index = (_index + 1) % MAX_STOCK_SIZE; // Déplacer _index au prochain emplacement circulairement
}

AMateria *MateriaSource::createMateria(const std::string &type) 
{
    for (int i = 0; i < MAX_STOCK_SIZE; ++i) 
    {
        if (_stock[i] != NULL && _stock[i]->getType() == type) 
            return _stock[i]->clone();
    }
    return NULL;
}