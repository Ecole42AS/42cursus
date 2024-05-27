/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 12:12:01 by astutz            #+#    #+#             */
/*   Updated: 2024/05/27 09:07:31 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"

int main() {
    Harl Harl;

	std::cout << "DEBUG :" << std::endl;
	Harl.complain("DEBUG");

	std::cout << "INFO :" << std::endl;
	Harl.complain("INFO");

	std::cout << "WARNING :" << std::endl;
	Harl.complain("WARNING");

	std::cout << "ERROR" << std::endl;
	Harl.complain("ERROR");
 
    Harl.complain("helloworld");

    return 0;
}