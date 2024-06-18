/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 11:28:48 by astutz            #+#    #+#             */
/*   Updated: 2024/06/18 12:37:21 by astutz           ###   ########.fr       */
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
	return *this;
}

AForm* Intern::makeForm(std::string const &formName, std::string const &target) {
	std::vector<std::pair<std::string, std::function<AForm*(std::string const&)>>> forms = {
		{"robotomy request", [](std::string const &target) -> AForm* { return new RobotomyRequestForm(target); }},
		{"shrubbery creation", [](std::string const &target) -> AForm* { return new ShrubberyCreationForm(target); }},
		{"presidential pardon", [](std::string const &target) -> AForm* { return new PresidentialPardonForm(target); }}
	};

	for (auto &form : forms) {
		if (form.first == formName) {
			std::cout << "Intern creates " << formName << std::endl;
			return form.second(target);
		}
	}
	throw FormNotFoundException();
	// std::cout << "Error: Requested form \"" << formName << "\" does not exist." << std::endl;
	// return nullptr;
}
