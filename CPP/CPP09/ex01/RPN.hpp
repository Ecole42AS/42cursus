/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                               			:+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 09:55:30 by astutz            #+#    #+#             */
/*   Updated: 2024/08/02 09:55:30 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include <stack>
#include <sstream>
#include <stdexcept>


class RPN {
private:
    std::stack<int> _stack;
public:
    RPN();
    ~RPN();
    RPN(const RPN &src);
    RPN &operator=(const RPN &rhs);
	int getResult(const std::string &str); 
};

