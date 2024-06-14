/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 09:13:35 by astutz            #+#    #+#             */
/*   Updated: 2024/06/14 11:11:20 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

int main()
{
	try
	{
		Bureaucrat Joe;
		Joe.downGrade();
		std::cout << Joe << std::endl;
		Bureaucrat Thierry("Thierry", 0);
		Thierry.upGrade();
		std::cout << Joe << std::endl;
		std::cout << Thierry << std::endl;
	}
    catch (const Bureaucrat::GradeTooLowException &e) {
        std::cerr << "Caught GradeTooLowException: " << e.what() << std::endl;
    }
    catch (const Bureaucrat::GradeTooHighException &e) {
        std::cerr << "Caught GradeTooHighException: " << e.what() << std::endl;
    }
    catch (const std::exception &e) {
        std::cerr << "Caught standard exception: " << e.what() << std::endl;
    }
    catch (...) {
        std::cerr << "Caught unknown exception!" << std::endl;
    }

	return 0;
}