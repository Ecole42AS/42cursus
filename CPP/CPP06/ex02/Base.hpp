/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Base.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 09:52:56 by astutz            #+#    #+#             */
/*   Updated: 2024/06/25 10:44:52 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include <ctime>
#include <cstdlib>

class Base
{
private:
	Base *generate(void);
	void identify(Base *p);
	void identify(Base &p);
public:
	virtual ~Base();
};