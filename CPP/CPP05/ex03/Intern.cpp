/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 11:28:48 by astutz            #+#    #+#             */
/*   Updated: 2024/06/19 13:52:10 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Intern.hpp"

Intern::Intern() {}

Intern::~Intern() {}

Intern::Intern(const Intern &src)
{
	*this = src;
}

Intern &Intern::operator=(const Intern &rhs)
{
	*this = rhs;
	return *this;
}

AForm* Intern::createRobotomyRequestForm(std::string const &target) {
	return new RobotomyRequestForm(target);
}

AForm* Intern::createShrubberyCreationForm(std::string const &target) {
	return new ShrubberyCreationForm(target);
}

AForm* Intern::createPresidentialPardonForm(std::string const &target) {
	return new PresidentialPardonForm(target);
}

AForm* Intern::makeForm(std::string const &formName, std::string const &target) {
	struct FormMethod {
		std::string name;
		AForm* (Intern::*methodPtr)(std::string const &);
	};

	FormMethod forms[] = {
		{"robotomy request", &Intern::createRobotomyRequestForm},
		{"shrubbery creation", &Intern::createShrubberyCreationForm},
		{"presidential pardon", &Intern::createPresidentialPardonForm}
	};

	for (int i = 0; i < 3; ++i) {
		if (forms[i].name == formName) {
			AForm* form = (this->*forms[i].methodPtr)(target);
			std::cout << "Intern creates " << formName << std::endl;
			return form;
		}
	}
	throw FormNotFoundException();
}
