/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AForm.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 21:04:34 by astutz            #+#    #+#             */
/*   Updated: 2024/06/15 21:47:47 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "Bureaucrat.hpp"

class Bureaucrat;
class AForm
{
protected:
	const std::string _name;
	bool _isSigned;
	const int _gradeToSign;
	const int _gradeToExec;
public:
	class GradeTooHighException : public std::exception
	{
	public:
		virtual const char *what() const throw()
		{
			return ("Grade is too high to sign the form !");
		}
	};

	class GradeTooLowException : public std::exception
	{
	public:
		virtual const char *what() const throw()
		{
			return ("Grade is too low to sign the form !");
		}
	};
	
	AForm();
	AForm(const std::string name, bool isSigned, const int gradeToSign, const int gradeToExec);
	~AForm();
	AForm(const AForm &src);
	AForm &operator=(const AForm &rhs);
	const std::string getName() const;
	bool getIsSigned() const;
	int getGradeToSign() const;
	int getGradeToExecute() const;
	bool beSigned(Bureaucrat &obj);
	
};

std::ostream &operator<<(std::ostream &os, const AForm &obj);
