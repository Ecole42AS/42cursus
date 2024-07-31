/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 15:33:49 by astutz            #+#    #+#             */
/*   Updated: 2024/07/31 22:06:07 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int main(int ac, char **av)
{
	try
	{
	if (ac == 2)
	{
		BitcoinExchange btc;
		btc.parseCSV();
		btc.parseInput(av[1]);
		// btc.printInputFile();
		btc.processLines();
		// std::ifstream ifs(av[1]);
		
		// if (!ifs)
		// 	throw std::invalid_argument("Error: could not open file.");
		// ifs.close();
	}
	else
		throw std::invalid_argument("Error: could not open file.");	
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	
	return (0);
}