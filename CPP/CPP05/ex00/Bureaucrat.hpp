/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 09:14:31 by astutz            #+#    #+#             */
/*   Updated: 2024/06/14 10:36:02 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include <string>

class Bureaucrat
{
private:
	std::string _name;
	unsigned int _grade;
public:
	class GradeTooHighException : public std::exception
	{
	public:
		virtual const char *what() const throw()
		{
			return ("Grade is too high !");
		}
	};
	
	class GradeTooLowException : public std::exception
	{
	public:
		virtual const char *what() const throw()
		{
			return ("Grade is too low !");
		}
	};
		
	Bureaucrat();
	Bureaucrat(std::string _name, unsigned int _grade);
	Bureaucrat(Bureaucrat const &src);
	~Bureaucrat();
	Bureaucrat &operator=(Bureaucrat const &rhs);
	std::string getName() const;
	unsigned int getGrade() const;
	void upGrade();
	void downGrade();
	
};

std::ostream &operator<<(std::ostream &os, const Bureaucrat &obj);