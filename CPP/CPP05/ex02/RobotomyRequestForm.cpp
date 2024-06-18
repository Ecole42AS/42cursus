/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RobotomyRequestForm.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 09:25:47 by astutz            #+#    #+#             */
/*   Updated: 2024/06/18 10:16:54 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RobotomyRequestForm.hpp"

RobotomyRequestForm::RobotomyRequestForm(): AForm("Robotomy", false, 72, 45)
{
	_target = "default_target";
}

RobotomyRequestForm::RobotomyRequestForm(std::string target): AForm("Robotomy", false, 72, 45), _target(target) {}

RobotomyRequestForm::~RobotomyRequestForm() {}

RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm &src) : AForm(src)
{
	_target = src._target;
}

RobotomyRequestForm &RobotomyRequestForm::operator=(const RobotomyRequestForm &rhs)
{
	if (this != &rhs)
	{
		_target = rhs._target;
		AForm::operator=(rhs);
	}
	return *this;
}

void RobotomyRequestForm::execute(Bureaucrat const & executor) const
{
	if (executor.getGrade() <= getGradeToExecute())
	{
		std::srand(static_cast<unsigned int>(std::time(0)));

		std::cout << "BRRRRRRRR VRRRRRR ZZZZZZZZ" << std::endl;

		int randomValue = std::rand() % 2;
		
		if (randomValue)
			std::cout << _target << " has been robotomized successfully !" << std::endl;
		else
			std::cout << "The robotomy failed on " << _target << " !" << std::endl;		
	}
	else
		throw GradeTooLowException();
}
