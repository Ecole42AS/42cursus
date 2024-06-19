/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScalarConverter.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 14:08:46 by astutz            #+#    #+#             */
/*   Updated: 2024/06/19 14:27:44 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

class ScalarConverter {
private:
	// Private members here
public:
	ScalarConverter();
	~ScalarConverter();
	ScalarConverter(const ScalarConverter &src);
	ScalarConverter &operator=(const ScalarConverter &rhs);
};