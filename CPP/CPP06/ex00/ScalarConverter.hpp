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
#include <iostream>
#include <string>
#include <cstdlib>
#include <cctype>


class ScalarConverter {
private:
    ScalarConverter();
	~ScalarConverter();
    ScalarConverter(const ScalarConverter &src);
    ScalarConverter &operator=(const ScalarConverter &rhs);
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

