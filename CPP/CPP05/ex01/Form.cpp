/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 11:34:27 by astutz            #+#    #+#             */
/*   Updated: 2024/06/14 14:40:48 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Form.hpp"

	Form::Form(): _name("defautName"), _isSigned(false), _gradeToSign(150), _gradeToExec(150) {}
	
	Form::Form(const std::string name, bool isSigned, const int gradeToSign, const int gradeToExec) :
	_name(name),
	_isSigned(isSigned),
	_gradeToSign(gradeToSign),
	_gradeToExec(gradeToExec)
	{
		if (gradeToSign > 150 || gradeToExec > 150)
			throw Form::GradeTooLowException();

		if (gradeToSign < 1 || gradeToExec < 1)
			throw Form::GradeTooHighException();
	}
	
	Form::~Form() {}
	
	Form::Form(const Form &src):
	_name(src._name),
	_isSigned(src._isSigned),
	_gradeToSign(src._gradeToExec),
	_gradeToExec(src._gradeToExec) {}
	
	Form &Form::operator=(const Form &rhs)
	{
		if (this != &rhs)
			_isSigned = rhs._isSigned;
		return *this;
	}
	
	const std::string Form::getName() const
	{
		return _name;
	}
	
	bool Form::getIsSigned() const
	{
		return _isSigned;	
	}
	
	int Form::getGradeToSign() const
	{
		return _gradeToSign;
	}
	
	int Form::getGradeToExecute() const
	{
		return _gradeToExec;
	}
	
	bool Form::beSigned(Bureaucrat &obj)
	{
		if (_gradeToSign >= obj.getGrade())
		{
			_isSigned = true;
			return true;
		}
		else
		{
			throw Form::GradeTooLowException();
			return false;
		}
	}


	std::ostream &operator<<(std::ostream &os, const Form &obj)
	{
		os << "\nForm name: " << obj.getName() << "\nIs Form signed ? " << obj.getIsSigned() << " (1(yes), 0(no))\n" << "Grade required to sign the form: " << obj.getGradeToSign() << "\nGrade required to execute the form: " << obj.getGradeToExecute() << std::endl;
		return os;
	}
	