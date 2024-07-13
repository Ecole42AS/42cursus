/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.hpp                               			:+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 15:57:36 by astutz            #+#    #+#             */
/*   Updated: 2024/06/19 15:57:36 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <cstring>
#include <climits>
#include <cstdlib>
#include <cctype>
#include <limits>
#include <cfloat>


class ScalarConverter {
private:
    ScalarConverter();
	~ScalarConverter();
    ScalarConverter(const ScalarConverter &src);
    ScalarConverter &operator=(const ScalarConverter &rhs);
	static void		getType(std::string literal);
	static void		convertInt(int nb);
	static void		convertDouble(double nb);
	static void		convertFloat(float nb);
	static void		convertChar(char nb);
	static void		printInt(int nb);
	static void		printDouble(double nb);
	static void		printFloat(float nb);
	static void		printChar(char c);
	static void		printError();
	static void		printSpecial(std::string literal);
public:
	class NotADigit : public std::exception
	{
	public:
		virtual const char *what() const throw()
		{
			return ("Error: Not a digit");
		}
	};
	class EmptyInput: public std::exception
	{
	public:
		virtual const char *what() const throw()
		{
			return ("Error: Empty input");
		}
	};
	static void convert(const std::string &literal);
};

