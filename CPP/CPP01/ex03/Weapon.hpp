/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 20:36:58 by astutz            #+#    #+#             */
/*   Updated: 2024/05/25 08:58:09 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include <string>

class Weapon
{
private:
	std::string type;
public:
	Weapon(std::string type);
	~Weapon();
	const std::string &getType();
	void setType(std::string newType);
};