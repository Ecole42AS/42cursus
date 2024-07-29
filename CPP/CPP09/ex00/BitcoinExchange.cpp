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

BitcoinExchange::BitcoinExchange(const BitcoinExchange &src) : _csvFile(src._csvFile), _inputFile(src._inputFile) {}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &rhs)
{
    if (this != &rhs) {
		_csvFile = rhs._csvFile;
		_inputFile = rhs._inputFile;
    }
    return *this;
}

// Fonction utilitaire pour trim les espaces
std::string BitcoinExchange::trim(const std::string& str)
{
    std::string trimmed = str;
    size_t start = trimmed.find_first_not_of(" \t");
    size_t end = trimmed.find_last_not_of(" \t");

    if (start == std::string::npos)
        return "";

    return trimmed.substr(start, end - start + 1);
}

void BitcoinExchange::parseInput(std::string fileName) {
	std::ifstream file(fileName.c_str());
	std::string line;

	if (!file.is_open()) {
		std::cerr << "Error: could not open file." << std::endl;
		return;
	}

	std::getline(file, line);
	if  (line.empty() ) {
		std::cerr << "Error: file is empty." << std::endl;
		return;
	}

	while (std::getline(file, line)) {
		std::size_t pipePos = line.find('|');

		if (pipePos == std::string::npos) {
			std::cerr << "Error: line format is incorrect (no pipe found): " << line << std::endl;
			continue;
		}

		std::string date = line.substr(0, pipePos);
		std::string valueStr = line.substr(pipePos + 1);
		valueStr = trim(valueStr);

		if (valueStr.empty()) {
			std::cerr << "Error: value is empty for line: " << line << std::endl;
			continue;
		}

		double value = std::atof(valueStr.c_str());
		if (value == 0.0 && valueStr != "0") {
			std::cerr << "Error: invalid value for line: " << line << std::endl;
			continue;
		}

		_inputFile[date] = value;
	}

	file.close();

	std::string outputFileName = "output.txt";
    std::ofstream outFile(outputFileName.c_str());

    if (!outFile.is_open()) {
        std::cerr << "Error: could not open output file." << std::endl;
        return;
    }

    for (std::map<std::string, double>::iterator it = _inputFile.begin(); it != _inputFile.end(); ++it) {
        outFile << it->first << ": " << std::fixed << std::setprecision(2) << it->second << std::endl;
    }

    outFile.close();

}

void BitcoinExchange::parseCSV() {
    std::ifstream file("data.csv");
    std::string line;

    if (!file.is_open()) {
        std::cerr << "Error: could not open file." << std::endl;
        return;
    }

	std::getline(file, line);
    while (std::getline(file, line)) {
        std::size_t commaPos = line.find(',');

        if (commaPos == std::string::npos) {
            std::cerr << "Error: line format is incorrect (no comma found): " << line << std::endl;
            continue;
        }

        std::string date = line.substr(0, commaPos);
        std::string priceStr = line.substr(commaPos + 1);
        priceStr = trim(priceStr);

        if (priceStr.empty()) {
            std::cerr << "Error: price is empty for line: " << line << std::endl;
            continue;
        }

        double price = std::atof(priceStr.c_str());
        if (price == 0.0 && priceStr != "0") {
            std::cerr << "Error: invalid price value for line: " << line << std::endl;
            continue;
        }

        _csvFile[date] = price;
    }

    file.close();

	// std::string outputFileName = "output.txt";
    // std::ofstream outFile(outputFileName.c_str());

    // if (!outFile.is_open()) {
    //     std::cerr << "Error: could not open output file." << std::endl;
    //     return;
    // }

    // for (std::map<std::string, double>::iterator it = _csvFile.begin(); it != _csvFile.end(); ++it) {
    //     outFile << it->first << ": " << std::fixed << std::setprecision(2) << it->second << std::endl;
    // }

    // outFile.close();

}


