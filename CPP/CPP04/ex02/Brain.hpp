/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 12:07:58 by astutz            #+#    #+#             */
/*   Updated: 2024/06/03 17:11:36 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include <string>

class Brain
{
private:
	std::string _ideas[100];
public:
	Brain();
	~Brain();
	Brain(const Brain &src);
	Brain &operator=(const Brain &rhs);
	const std::string* getIdea(int index) const;
	void setIdea(int index, const std::string &idea);
};
