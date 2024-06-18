/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 11:23:09 by astutz            #+#    #+#             */
/*   Updated: 2024/06/18 12:38:47 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "AForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "PresidentialPardonForm.hpp"

class Intern
{
public:
	class FormNotFoundException : public std::exception
	{
	public:
		virtual const char *what() const throw()
		{
			return ("Error: Requested form does not exist.");
		}
	};
	Intern();
	Intern(std::string target);
	~Intern();
	Intern(const Intern &src);
	Intern &operator=(const Intern &rhs);
	AForm* Intern::makeForm(std::string const &formName, std::string const &target);
};
