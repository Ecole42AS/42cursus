/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 23:14:27 by astutz            #+#    #+#             */
/*   Updated: 2024/06/18 11:09:29 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"


int main()
{
	try
	{
		Bureaucrat Antoine("Antoine", 137);
		Bureaucrat Joe("Joe", 45);
		Bureaucrat Victor("Victor", 5);
		ShrubberyCreationForm shrubForm("myTarget");
		RobotomyRequestForm robotomyForm("mySecondTarget");
		PresidentialPardonForm PresidentialForm("myThirdTarget");
		// shrubForm.execute(Antoine);
		// robotomyForm.execute(Joe);
		// PresidentialForm.execute(Victor);
		Antoine.executeForm(shrubForm);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	
	
	
}