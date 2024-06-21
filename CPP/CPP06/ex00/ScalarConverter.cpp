/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.cpp                               			:+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 15:57:36 by astutz            #+#    #+#             */
/*   Updated: 2024/06/19 15:57:36 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"

ScalarConverter::ScalarConverter() {}

ScalarConverter::~ScalarConverter() {}

ScalarConverter::ScalarConverter(const ScalarConverter &src)
{
	(void)src;
}

ScalarConverter &ScalarConverter::operator=(const ScalarConverter &rhs)
{
	(void)rhs;
    return *this;
}

// void ScalarConverter::convert(const std::string &literal)
// {
//     try
//     {
//         if (literal.empty())
//         {
//             throw EmptyInput();
//         }

//         for (size_t i = 0; i < literal.length(); ++i)
//         {
//             if (!std::isdigit(static_cast<unsigned char>(literal[i])))
//             {
//                 throw NotADigit();
//             }
//         }
// 		int intValue = atoi(literal.c_str());
// 		std::cout << intValue << std::endl;
//     }
//     catch(const std::exception& e)
//     {
//         std::cout << e.what() << std::endl;
//     }
// }





void				ScalarConverter::getType(std::string str)
{
	bool				isDouble = false;
	bool				isFloat = false;
	std::stringstream	ss(str);

	if (str.empty())
		return printError();
	if (std::isalpha(str[0]) && str.size() == 1)
		return printChar(str[0]);
	for(int i = 0; i < (int)str.length(); i++)
	{
		if ((str[i] == '-' || str[i] == '+') && i == 0)
			i++;
		if (std::isdigit(str[i]))
			continue;
		else if (str[i] == '.' && !isDouble)
			isDouble = true;
		else if (str[i] == 'f' && isDouble && !isFloat)
		{
			isFloat = true;
			isDouble = false;
		}
		else
			return printError();
	}
	if (isDouble)
	{
		printDouble(std::atof(str.c_str()));
	}
	else if (isFloat)
	{
		printFloat(std::atof(str.c_str()));
	}
	else
	{
		printInt(std::atoi(str.c_str()));
	}
}

void				ScalarConverter::convertInt(int nb)
{
	if (nb < INT_MIN || nb > INT_MAX)
		std::cout << "int: impossible" << std::endl;
	else
		std::cout << "int: " << nb << std::endl;
}

void				ScalarConverter::convertDouble(double nb)
{
	std::cout << "double: " << std::fixed << std::setprecision(1) << nb << std::endl;
}

void				ScalarConverter::convertFloat(float nb)
{
	std::cout << "float: " << std::fixed << std::setprecision(1) << nb << "f" << std::endl;
}

void ScalarConverter::convertChar(char nb)
{
	if ((nb >= 0 && nb <= 32) || nb == 127) {
		std::cout << "char: Non displayable" << std::endl;
		// } else if (nb > 127) {
		// 	std::cout << "char: Impossible" << std::endl;
	} else {
		std::cout << "char: '" << nb << "'" << std::endl;
	}
}


void				ScalarConverter::printInt(int nb)
{
	convertChar(static_cast<char>(nb));
	convertInt(nb);
	convertDouble(static_cast<double>(nb));
	convertFloat(static_cast<float>(nb));
}

void				ScalarConverter::printDouble(double nb)
{
	convertChar(static_cast<char>(nb));
	convertInt(static_cast<int>(nb));
	convertDouble(nb);
	convertFloat(static_cast<float>(nb));
}

void				ScalarConverter::printFloat(float nb)
{
	convertChar(static_cast<char>(nb));
	convertInt(static_cast<int>(nb));
	convertDouble(static_cast<double>(nb));
	convertFloat(nb);
}

void				ScalarConverter::printChar(char c)
{
	convertChar(c);
	convertInt(static_cast<int>(c));
	convertDouble(static_cast<double>(c));
	convertFloat(static_cast<float>(c));
}

void				ScalarConverter::printError()
{
	std::cout << "This type conversion is impossible !" << std::endl;
}

void				ScalarConverter::printSpecial(std::string str)
{
	std::cout << "char: impossible" << std::endl;
	std::cout << "int: impossible" << std::endl;
	std::cout << "double: " << str << std::endl;
	std::cout << "float: " << str << "f" << std::endl;
}

void				ScalarConverter::convert(const std::string &str)
{
	std::string	special[2][3] = {{"-inf", "+inf", "nan"}, {"-inff", "+inff", "nanf"}};
	bool		flag_spe = false;

	if (std::isalpha(str[0]) && std::isalpha(str[1]) && strcmp(str.c_str(), "nan") && strcmp(str.c_str(), "nanf"))
	{
		printError();
		return ;
	}

	for (int i = 0; i < 3; i++)
	{
		if ((str == special[0][i]) || (str == special[1][i]))
		{
			printSpecial(special[0][i]);
			flag_spe = true;
		}
	}

	if (!flag_spe)
		getType(str);
}
