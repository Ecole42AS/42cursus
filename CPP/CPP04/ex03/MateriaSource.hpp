/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MateriaSource.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 12:32:29 by astutz            #+#    #+#             */
/*   Updated: 2024/06/05 14:18:08 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "IMateriaSource.hpp"

class MateriaSource : public IMateriaSource
{
private:
	static const int MAX_STOCK_SIZE = 4; // mieux qu'une macro car la macro peut avoir des problèmes de portée et de lisibilité
	int	_index; //stocker une materia lorsqu'elle est apprise
	AMateria *_stock[MAX_STOCK_SIZE];
public:
	MateriaSource();
	~MateriaSource();
	MateriaSource(const MateriaSource &src);
	MateriaSource &operator=(const MateriaSource &rhs);

	void learnMateria(AMateria*);
	AMateria* createMateria(std::string const & type);
};