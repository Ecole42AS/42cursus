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

// void BitcoinExchange::parseInput(std::string fileName)
// {
//     std::ifstream file(fileName.c_str());
//     if (!file.is_open())
//     {
//         std::cerr << "Error: could not open input file." << std::endl;
//         return;
//     }

//     std::string line;
// 	std::cout << line << std::endl;
//     if (!std::getline(file, line) || trim(line) != "date | value")
//     {
//         std::cerr << "Error: incorrect header in input file. Expected 'date | value'." << std::endl;
//         return;
//     }
// 	std::cout << line << std::endl;

//     while (std::getline(file, line))
//     {

//         std::string trimmedLine = trim(line);

//         if (!trimmedLine.empty())
//         {
//             std::string date;
//             float value;

//             std::istringstream ss(trimmedLine);
//             if (std::getline(ss, date, '|') && (ss >> value))
//             {
//                 date = trim(date);
//                 // if (isValidDate(date) && isValidValue(value))
//                 // {
// 				// std::cout << date << std::endl;
// 				// std::cout << value << std::endl;
//                     _inputFile[date] = value;
//                 // }
//                 // else
//                 // {
//                 //     if (value < 0)
//                 //         std::cerr << "Error: not a positive number." << std::endl;
//                 //     else if (value > 1000)
//                 //         std::cerr << "Error: too large a number." << std::endl;
//                 //     else
//                 //         std::cerr << "Error: invalid data in line '" << trimmedLine << "'." << std::endl;
//                 // }
//             }
//             // else
//             // {
//             //     std::cerr << "Error: bad input => " << trimmedLine << std::endl;
//             // }
//         }
// 		// processLines();
//     }
// 	for (std::map<std::string, float>::iterator it = _inputFile.begin(); it != _inputFile.end(); ++it) {
// 		std::cout << it->first << ": " << std::fixed << std::setprecision(2) << it->second << std::endl;
// 	}
// }


void BitcoinExchange::parseInput(std::string fileName)
{
    std::ifstream file(fileName.c_str());
    if (!file.is_open())
    {
        std::cerr << "Error: could not open input file." << std::endl;
        return;
    }

    std::string line;
    if (!std::getline(file, line) || trim(line) != "date | value")
    {
        std::cerr << "Error: incorrect header in input file. Expected 'date | value'." << std::endl;
        return;
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
                // if (isValidDate(date) && isValidValue(value))
				std::map<std::string, float>::iterator it = _csvFile.find(date);
				if (it != _csvFile.end())
					std::cout << date << " => " << value << " = " << value * it->second << std::endl;
				else
				{
					it = _csvFile.lower_bound(date);
					--it;
					std::cout << date << " => " << value << " = " << value * it->second << std::endl;
				}	
				// return ;
			// }
            //     else
            //     {
            //         if (value < 0)
            //             std::cerr << "Error: not a positive number." << std::endl;
            //         else if (value > 1000)
            //             std::cerr << "Error: too large a number." << std::endl;
            //         else
            //             std::cerr << "Error: invalid data in line '" << trimmedLine << "'." << std::endl;
            //     }
            }
            else
            {
                std::cerr << "Error: bad input => " << trimmedLine << std::endl;
            }
        }
    }
}



// void BitcoinExchange::printInputFile()
// {
// 	std::string outputFileName = "output.txt";
//     std::ofstream outFile(outputFileName.c_str());

//     if (!outFile.is_open()) {
//         std::cerr << "Error: could not open output file." << std::endl;
//         return;
//     }

//     for (std::map<std::string, float>::iterator it = _inputFile.begin(); it != _inputFile.end(); ++it) {
//         outFile << it->first << ": " << std::fixed << std::setprecision(2) << it->second << std::endl;
//     }

//     outFile.close();

// }


void BitcoinExchange::printInputFile()
{
    std::string outputFileName = "output.txt";
    std::ofstream outFile(outputFileName.c_str());

    if (!outFile.is_open())
    {
        std::cerr << "Error: could not open output file." << std::endl;
        return;
    }

    for (std::map<std::string, float>::const_iterator it = _inputFile.begin(); it != _inputFile.end(); ++it)
    {
        outFile << it->first << ": " << std::fixed << std::setprecision(2) << it->second << std::endl;
    }

    outFile.close();
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

bool BitcoinExchange::isValidDate(const std::string& date)
{
    if (date.size() != 10) return false;
    return date[4] == '-' && date[7] == '-' && 
           std::isdigit(date[0]) && std::isdigit(date[1]) && std::isdigit(date[2]) && std::isdigit(date[3]) &&
           std::isdigit(date[5]) && std::isdigit(date[6]) &&
           std::isdigit(date[8]) && std::isdigit(date[9]);
}

bool BitcoinExchange::isValidValue(const float value)
{
    return value >= 0 && value <= 1000;
}

// bool BitcoinExchange::isValidValue(float value)
// {
//     if (value < 0)
//     {
//         std::cerr << "Error: not a positive number." << std::endl;
//         return false;
//     }
//     if (value > 1000)
//     {
//         std::cerr << "Error: too large a number." << std::endl;
//         return false;
//     }
//     return true;
// }


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
