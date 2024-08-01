#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{
}

BitcoinExchange::~BitcoinExchange()
{
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &src)
{
    *this = src;
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &rhs)
{
    if (this != &rhs)
    {
        _csvFile = rhs._csvFile;
        _inputFile = rhs._inputFile;
    }
    return *this;
}

void BitcoinExchange::parseCSV()
{
    std::ifstream file("data.csv");
    if (!file.is_open())
    {
        std::cerr << "Error: could not open CSV file." << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream ss(line);
        std::string date;
        float price;

        if (std::getline(ss, date, ',') && (ss >> price))
        {
            date = trim(date);
            _csvFile[date] = price;
        }
    }
}

void BitcoinExchange::parseInput(std::string fileName)
{
    std::ifstream file(fileName.c_str());
    if (!file.is_open())
    {
        std::cerr << "Error: could not open input file." << std::endl;
        return;
    }

    std::string line;

    if (!std::getline(file, line))
    {
        std::cerr << "Error: file is empty or could not read from file." << std::endl;
        return;
    }

    std::string trimmedLine = trim(line);
    if (trimmedLine != "date | value")
    {
        std::cerr << "Error: incorrect header in input file. Expected 'date | value', but found '" << trimmedLine << "'." << std::endl;
    }


    while (std::getline(file, line))
    {
        std::string trimmedLine = trim(line);

        if (!trimmedLine.empty())
        {
            std::string date;
            float value;

            std::istringstream ss(trimmedLine);
            if (std::getline(ss, date, '|') && (ss >> value))
            {
                date = trim(date);
				if (!isValidDate(date))
					std::cerr << "Error: invalid date." << std::endl;
				else if (value < 0)
					std::cerr << "Error: not a positive number." << std::endl;
				else if (value > 1000)
					std::cerr << "Error: too large a number." << std::endl;
				else
				{
					std::map<std::string, float>::iterator it = _csvFile.find(date);
					if (it != _csvFile.end() && isValidDate(date))
						std::cout << date << " => " << value << " = " << value * it->second << std::endl;
					else
					{
						it = _csvFile.lower_bound(date); //retourne iterator sur le premier élément >= date
						--it;
						std::cout << date << " => " << value << " = " << value * it->second << std::endl;
					}	
				}
            }
            else
            {
                std::cerr << "Error: bad input => " << trimmedLine << std::endl;
            }
        }
    }
}

std::string BitcoinExchange::trim(const std::string& str)
{
    std::string trimmed = str;
    size_t start = trimmed.find_first_not_of(" \t");
    size_t end = trimmed.find_last_not_of(" \t");

    if (start == std::string::npos)
    {
        return "";
    }

    return trimmed.substr(start, end - start + 1);
}

#include "BitcoinExchange.hpp"
#include <ctime>
#include <cstdlib>
#include <sstream>
#include <iostream>

bool BitcoinExchange::isValidDate(const std::string& date) const
{
    if (date.size() != 10)
        return false;

    if (date[4] != '-' || date[7] != '-' || !std::isdigit(date[0]) || !std::isdigit(date[1]) ||
        !std::isdigit(date[2]) || !std::isdigit(date[3]) || !std::isdigit(date[5]) ||
        !std::isdigit(date[6]) || !std::isdigit(date[8]) || !std::isdigit(date[9]))
    {
        return false;
    }

    int year = std::atoi(date.substr(0, 4).c_str());
    int month = std::atoi(date.substr(5, 2).c_str());
    int day = std::atoi(date.substr(8, 2).c_str());

    if (year < 2009 || (year == 2009 && (month < 1 || (month == 1 && day < 2))))
        return false;

    if (month < 1 || month > 12)
        return false;

    if (day < 1 || day > 31)
        return false;

    if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30)
        return false;

    if (month == 2)
	{
        bool isLeapYear = (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
        if (isLeapYear && day > 29)
            return false;
        
        else if (!isLeapYear && day > 28)
            return false;
    }

    return true;
}



void BitcoinExchange::processLines()
{
    std::map<std::string, float>::const_iterator inputIt;
    for (inputIt = _inputFile.begin(); inputIt != _inputFile.end(); ++inputIt)
    {
        const std::string& date = inputIt->first;
        float value = inputIt->second;

        std::map<std::string, float>::const_iterator csvIt = _csvFile.lower_bound(date);

        if (csvIt != _csvFile.end() && csvIt->first == date)
        {
            float price = csvIt->second;
            float result = value * price;
            std::cout << date << " => " << value << " = " << std::fixed << std::setprecision(2) << result << std::endl;
        }
        else
        {
            std::cerr << "Error: No price available for the date or previous date." << std::endl;
        }
    }
}
