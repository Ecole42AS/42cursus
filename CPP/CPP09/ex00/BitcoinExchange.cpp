/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                               			:+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 15:32:49 by astutz            #+#    #+#             */
/*   Updated: 2024/07/13 15:32:49 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::~BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &src)
{
	if (!_csvFile.empty())
		_csvFile.insert(src._csvFile.begin(), src._csvFile.end());
	if (!_inputFile.empty())
		_inputFile.insert(src._inputFile.begin(), src._inputFile.end());
    *this = src;
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &rhs)
{
    if (this != &rhs) {
		
    }
    return *this;
}

void BitcoinExchange::parseCSV(std::string fileName)
{
	std::ifstream file(fileName.c_str());
	std::string date;
	std::string line;
	unsigned int price;


	if (!file.is_open())
	{
		std::cerr << "Error: could not open file." << std::endl;
		return;
	}

	while (std::getline(file, line))
	{
		std::cout << line << std::endl;
	}
	file.close();

}






























// BitcoinExchange::parseCSV(std::string filename)
// {
	// std::ifstream file(filename);
	// std::string line;

	// if (!file.is_open())
	// {
	// 	std::cerr << "Error: could not open file." << std::endl;
	// 	return;
	// }

	// while(std::getline(file, line))
	// {
	// 	std::string date;
	// 	double price;
	// 	std::istringstream ss(line);
	// 	std::string token;

	// 	std::getline(ss, token, ',');
	// 	date = token;
	// 	std::getline(ss, token, ',');
	// 	price = std::stod(token);
	// 	_csvFile[date] = price;
	// }
// }
