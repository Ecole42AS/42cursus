/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AForm.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 21:04:01 by astutz            #+#    #+#             */
/*   Updated: 2024/06/18 10:59:08 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AForm.hpp"

AForm::AForm(): _name("defautName"), _isSigned(false), _gradeToSign(150), _gradeToExec(150) {}

AForm::AForm(const std::string name, bool isSigned, const int gradeToSign, const int gradeToExec) :
_name(name),
_isSigned(isSigned),
_gradeToSign(gradeToSign),
_gradeToExec(gradeToExec)
{
	if (gradeToSign > 150 || gradeToExec > 150)
		throw AForm::GradeTooLowException();

	if (gradeToSign < 1 || gradeToExec < 1)
		throw AForm::GradeTooHighException();
}

AForm::~AForm() {}

AForm::AForm(const AForm &src):
_name(src._name),
_isSigned(src._isSigned),
_gradeToSign(src._gradeToExec),
_gradeToExec(src._gradeToExec) {}

AForm &AForm::operator=(const AForm &rhs)
{
	if (this != &rhs)
		_isSigned = rhs._isSigned;
	return *this;
}

const std::string AForm::getName() const
{
	return _name;
}

bool AForm::getIsSigned() const
{
	return _isSigned;	
}

int AForm::getGradeToSign() const
{
	return _gradeToSign;
}

int AForm::getGradeToExecute() const
{
	return _gradeToExec;
}

bool AForm::beSigned(Bureaucrat &obj)
{
	if (_gradeToSign >= obj.getGrade())
	{
		_isSigned = true;
		return true;
	}
	else
	{
		throw AForm::GradeTooLowException();
		return false;
	}
}

std::ostream &operator<<(std::ostream &os, const AForm &obj)
{
	os << "\nForm name: " << obj.getName() << "\nIs Form signed ? " << obj.getIsSigned() << " (1(yes), 0(no))\n" << "Grade required to sign the Aform: " << obj.getGradeToSign() << "\nGrade required to execute the form: " << obj.getGradeToExecute() << std::endl;
	return os;
}
