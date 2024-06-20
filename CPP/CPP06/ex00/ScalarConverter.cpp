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

void ScalarConverter::convert(const std::string &literal)
{
    try
    {
        if (literal.empty()) // Vérifie si la chaîne est vide
        {
            throw TooShortInput();
        }

        for (size_t i = 0; i < literal.length(); ++i)
        {
            if (!std::isdigit(static_cast<unsigned char>(literal[i])))
            {
                throw NotADigit();
            }
        }
		int intValue = atoi(literal.c_str());
		std::cout << intValue << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
}

