/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShrubberyCreationForm.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 21:30:51 by astutz            #+#    #+#             */
/*   Updated: 2024/06/15 22:23:01 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ShrubberyCreationForm.hpp"

	ShrubberyCreationForm::ShrubberyCreationForm(): AForm("Shrubbery", false, 145, 137)
	{
		_target = "default_target";
	}
	
	ShrubberyCreationForm::ShrubberyCreationForm(std::string target): AForm("Shrubbery", false, 145, 137), _target(target) {}
	
	ShrubberyCreationForm::~ShrubberyCreationForm() {}
	
	ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm &src) : AForm(src)
	{
		_target = src._target;
	}
	
	ShrubberyCreationForm &ShrubberyCreationForm::operator=(const ShrubberyCreationForm &rhs)
	{
		if (this != &rhs)
		{
			_target = rhs._target;
			AForm::operator=(rhs);
		}
		return *this;
	}
	
