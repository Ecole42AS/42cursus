/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 09:26:32 by astutz            #+#    #+#             */
/*   Updated: 2024/06/15 23:13:39 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

Bureaucrat::Bureaucrat(): _name("default"), _grade((int) 150) {}

Bureaucrat::Bureaucrat(std::string name, int grade): _name(name), _grade(grade)
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
		_grade = rhs._grade;			
	}
	return (*this);
}

std::string Bureaucrat::getName() const
{
	return _name;
}

int Bureaucrat::getGrade() const
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

void Bureaucrat::signForm(AForm &form)
{
    try
    {
        form.beSigned(*this); // Appel direct sans vérification de retour
        std::cout << *this << " signed " << form << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << getName() << " couldn't sign the form " << form.getName() << " because ";
        std::cerr << e.what() << std::endl;
    }
}

// void Bureaucrat::executeForm(AForm const & form)
// {
	
// }


std::ostream &operator<<(std::ostream &os, const Bureaucrat &obj)
{
	os << obj.getName() << ", bureaucrat grade " << obj.getGrade();
	return os;
}
	