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

void	ScalarConverter::getType(std::string literal)
{
	bool				isDouble = false;
	bool				isFloat = false;
	std::stringstream	ss(literal);


	if (literal.empty())
		return printError();
	if (std::isalpha(literal[0]) && literal.size() == 1)
		return printChar(literal[0]);
	for(int i = 0; i < (int)literal.length(); i++)
	{
		if ((literal[i] == '-' || literal[i] == '+') && i == 0)
			i++;
		if (std::isdigit(literal[i]))
			continue;
		else if (literal[i] == '.' && !isDouble)
			isDouble = true;
		else if (literal[i] == 'f' && isDouble && !isFloat)
		{
			isFloat = true;
			isDouble = false;
		}
		else
			return printError();
	}
	if (isDouble)
	{
		double				nb;
		ss >> nb;
		if (ss.fail() || !ss.eof()) // verifie si toutes les données ont été lues
            printError();
		printDouble(nb);
	}
	else if (isFloat)
	{
		float				nb;
		ss >> nb;
		if (ss.fail() || !ss.eof())
			printError();
		printFloat(nb);
	}
	else
	{
		int					nb;
		ss >> nb;
		if (ss.fail() || !ss.eof())
			printError();
		printInt(nb);
	}
}

void	ScalarConverter::convertInt(int nb)
{
	if (nb < INT_MIN || nb > INT_MAX)
		std::cout << "int: impossible" << std::endl;
	else
		std::cout << "int: " << nb << std::endl;
}

void	ScalarConverter::convertDouble(double nb)
{
	std::numeric_limits<double> limits;
	// std::cout << limits.min() << std::endl;
	// std::cout << DBL_MIN << std::endl;
	// std::cout << limits.max() << std::endl;
	// std::cout << DBL_MAX << std::endl;
	if (nb < limits.min() || nb > limits.max())
		std::cout << "double: impossible" << std::endl;
	else
		std::cout << "double: " << std::fixed << std::setprecision(1) << nb << std::endl;
}

void	ScalarConverter::convertFloat(float nb)
{
	std::numeric_limits<float> limits;
	// std::cout << limits.min() << std::endl;
	// std::cout << FLT_MIN << std::endl;
	// std::cout << limits.max() << std::endl;
	// std::cout << FLT_MAX << std::endl;
	if (nb < limits.min() || nb > limits.max())
		std::cout << "float: impossible" << std::endl;
	else
		std::cout << "float: " << std::fixed << std::setprecision(1) << nb << "f" << std::endl;
}

void ScalarConverter::convertChar(char nb)
{
	if ((nb >= 0 && nb < 32) || nb == 127) {
		std::cout << "char: Non displayable" << std::endl;
	} else if (nb >= 32 && nb <= 126) {
		std::cout << "char: '" << nb << "'" << std::endl;
	} else {
		std::cout << "char: Impossible" << std::endl;
	}
}


void	ScalarConverter::printInt(int nb)
{
	convertChar(static_cast<char>(nb));
	convertInt(nb);
	convertDouble(static_cast<double>(nb));
	convertFloat(static_cast<float>(nb));
}

void	ScalarConverter::printDouble(double nb)
{
	convertChar(static_cast<char>(nb));
	convertInt(static_cast<int>(nb));
	convertDouble(nb);
	convertFloat(static_cast<float>(nb));
}

void	ScalarConverter::printFloat(float nb)
{
	convertChar(static_cast<char>(nb));
	convertInt(static_cast<int>(nb));
	convertDouble(static_cast<double>(nb));
	convertFloat(nb);
}

void	ScalarConverter::printChar(char c)
{
	convertChar(c);
	convertInt(static_cast<int>(c));
	convertDouble(static_cast<double>(c));
	convertFloat(static_cast<float>(c));
}

void	ScalarConverter::printError()
{
	std::cout << "This type conversion is impossible !" << std::endl;
}

void	ScalarConverter::printSpecial(std::string literal)
{
	std::cout << "char: impossible" << std::endl;
	std::cout << "int: impossible" << std::endl;
	std::cout << "double: " << literal << std::endl;
	std::cout << "float: " << literal << "f" << std::endl;
}

void	ScalarConverter::convert(const std::string &literal)
{
	std::string	special[2][3] = {{"-inf", "+inf", "nan"}, {"-inff", "+inff", "nanf"}};
	bool		flag_spe = false;

	if (std::isalpha(literal[0]) && std::isalpha(literal[1]) && strcmp(literal.c_str(), "nan") && strcmp(literal.c_str(), "nanf"))
	{
		printError();
		return ;
	}

	for (int i = 0; i < 3; i++)
	{
		if ((literal == special[0][i]) || (literal == special[1][i]))
		{
			printSpecial(special[0][i]);
			flag_spe = true;
		}
	}

	if (!flag_spe)
		getType(literal);
}
