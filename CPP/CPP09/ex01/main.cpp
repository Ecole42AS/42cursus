/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 10:06:43 by astutz            #+#    #+#             */
/*   Updated: 2024/08/02 10:19:13 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

int main(int ac, char **av)
{
	try
	{
		if (ac != 2) {
			std::cerr << "Usage: ./RPN \"[RPN expression]\"" << std::endl;
			return 1;
		}
		RPN rpn;
		std::cout << rpn.getResult(av[1]) << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	
	return 0;
}