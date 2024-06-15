/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ShrubberyCreationForm.cpp                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 21:30:51 by astutz            #+#    #+#             */
/*   Updated: 2024/06/15 23:28:03 by astutz           ###   ########.fr       */
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

	void ShrubberyCreationForm::execute(Bureaucrat const & executor) const
	{
		std::string fileName = _target + "_shrubbery";
		
		std::ofstream file(fileName.c_str());
		
		if (file.is_open())
		{
			file << "    _-_\n"
				<< "  /~~   ~~\\\n"
				<< " /~~        ~~\\\n"
				<< "{    O  O      }\n"
				<< " \\      <       /\n"
				<< "    \\         /\n"
				<< "      ~-____-~\n";			
		}
		else
		{
			std::cerr << executor << " Failed to create " << fileName << std::endl;
	        return;
		}
		file.close();
	}
