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

// BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &rhs)
// {
//     if (this != &rhs) {
// 		_csvFile = rhs._csvFile;
// 		_inputFile = rhs._inputFile;
//     }
//     return *this;
// }

// void BitcoinExchange::parseCSV(std::string fileName) {
//     std::ifstream file(fileName.c_str());
//     std::string date;
//     std::string line;
//     double price;

//     if (!file.is_open()) {
//         std::cerr << "Error: could not open file." << std::endl;
//         return;
//     }
// 	std::getline(file, line);
//     while (std::getline(file, line)) {
//         // std::cout << line << std::endl;

//         size_t commaPos = line.find(",");
//         if (commaPos == std::string::npos) {
//             std::cerr << "Error: line does not contain a comma." << std::endl;
//         }

//         date = line.substr(0, commaPos);
//         std::string priceStr = line.substr(commaPos + 1);

//         std::stringstream ss(priceStr);
//         if (!(ss >> price)) {
//             std::cerr << "Error: invalid price value." << line << std::endl;
//         }
// 			_csvFile[date] = price;
// 	}

//     file.close();

// 	std::string outputFileName = "output.txt";
//     std::ofstream outFile(outputFileName.c_str());

//     if (!outFile.is_open()) {
//         std::cerr << "Error: could not open output file." << std::endl;
//         return;
//     }

//     for (std::map<std::string, double>::iterator it = _csvFile.begin(); it != _csvFile.end(); ++it) {
//         outFile << it->first << ": " << std::fixed << std::setprecision(2) << it->second << std::endl;
//     }

//     outFile.close();

//     file.close();

// }

// void BitcoinExchange::parseCSV(std::string filename) {
//     std::ifstream file(filename.c_str());
//     std::string line;

//     if (!file.is_open()) {
//         std::cerr << "Error: could not open file." << std::endl;
//         return;
//     }

//     while (std::getline(file, line)) {
//         std::size_t commaPos = line.find(',');

//         if (commaPos == std::string::npos) {
//             std::cerr << "Error: line format is incorrect: " << line << std::endl;
//             continue;
//         }

//         std::string date = line.substr(0, commaPos);
//         std::string priceStr = line.substr(commaPos + 1);
// 		if (priceStr.empty()) {
// 			std::cerr << "Error: price is empty." << std::endl;
// 			continue;
// 		}
//         double price = std::atof(priceStr.c_str());

//         _csvFile[date] = price;
//     }

// 	//    Nom du fichier de sortie
//     std::string outputFileName = "output.txt";
//     std::ofstream outFile(outputFileName.c_str());

//     if (!outFile.is_open()) {
//         std::cerr << "Error: could not open output file." << std::endl;
//         return;
//     }

//     for (std::map<std::string, double>::iterator it = _csvFile.begin(); it != _csvFile.end(); ++it) {
//         outFile << it->first << ": " << std::fixed << std::setprecision(2) << it->second << std::endl;
//     }

//     outFile.close();

//     file.close();
// }

// Fonction utilitaire pour trim les espaces
std::string trim(const std::string& str) {
    std::string trimmed = str;
    size_t start = trimmed.find_first_not_of(" \t");
    size_t end = trimmed.find_last_not_of(" \t");

    if (start == std::string::npos) // La chaîne est vide ou contient seulement des espaces
        return "";

    return trimmed.substr(start, end - start + 1);
}

void BitcoinExchange::parseCSV(std::string filename) {
    std::ifstream file(filename.c_str());
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
        priceStr = trim(priceStr); // Enlever les espaces autour du prix

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

