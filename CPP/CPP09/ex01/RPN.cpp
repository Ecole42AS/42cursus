/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 12:02:28 by astutz            #+#    #+#             */
/*   Updated: 2024/08/02 12:32:59 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "RPN.hpp"

RPN::RPN() {}

RPN::~RPN() {}

RPN::RPN(const RPN &src)
{
    *this = src;
}

RPN &RPN::operator=(const RPN &rhs)
{
    if (this != &rhs) {
        _stack = rhs._stack;
    }
    return *this;
}


int RPN::getResult(const std::string &str)
{
	std::istringstream iss(str);
	char c;

	while (iss >> c)
	{
		if (std::isdigit(c))
			_stack.push(c - '0');
		else if (c == '+' || c == '-' || c == '*' || c == '/')
		{
			if (_stack.size() < 2)
				throw std::invalid_argument("Error: insufficient values in the expression");

			int b = _stack.top();
			_stack.pop();
			int a = _stack.top();
			_stack.pop();

			switch (c)
			{
				case '+': _stack.push(a + b); break;
				case '-': _stack.push(a - b); break;
				case '*': _stack.push(a * b); break;
				case '/':
					if (b == 0)
						throw std::invalid_argument("Division by 0 is not allowed");
					_stack.push(a / b);
					break;
			}
		} 
		else if (c != ' ')
			throw std::invalid_argument("Error: invalid character encountered");
	}

	if (_stack.size() != 1) 
		throw std::invalid_argument("Error: stack size is not 1");

	return _stack.top();
}