/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 09:26:32 by astutz            #+#    #+#             */
/*   Updated: 2024/06/14 10:51:00 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

	Bureaucrat::Bureaucrat(): _name("default"), _grade((unsigned int) 150) {}
	
	Bureaucrat::Bureaucrat(std::string name, unsigned int grade): _name(name), _grade(grade)
	{
		if (grade > 150)
			throw Bureaucrat::GradeTooLowException();
		if (grade < 1)
			throw Bureaucrat::GradeTooHighException();
	}
	
	Bureaucrat::Bureaucrat(Bureaucrat const &src)
	{
		*this = src;
	}
	
	Bureaucrat::~Bureaucrat() {}
	
	Bureaucrat &Bureaucrat::operator=(Bureaucrat const &rhs)
	{
		if (this != &rhs)
		{
			_name = rhs._name;
			_grade = rhs._grade;			
		}
		return (*this);
	}
	
	std::string Bureaucrat::getName() const
	{
		return _name;
	}
	
	unsigned int Bureaucrat::getGrade() const
	{
		return _grade;
	}
	
	void Bureaucrat::upGrade()
	{
		_grade--;
		if (_grade < 1)
			throw(Bureaucrat::GradeTooHighException());
	}
	
	void Bureaucrat::downGrade()
	{
		_grade++;
		if (_grade > 150)
			throw (Bureaucrat::GradeTooLowException());
	}

	std::ostream &operator<<(std::ostream &os, const Bureaucrat &obj)
	{
		os << obj.getName() << ", bureaucrat grade " << obj.getGrade();
		return os;
	}
	