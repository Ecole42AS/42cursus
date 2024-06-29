/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 14:30:29 by astutz            #+#    #+#             */
/*   Updated: 2024/06/29 16:26:11 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Span.hpp"

int main() {
	Span sp = Span(2);
	std::cout << "Capacity of vec: " << sp.getVec().capacity() << std::endl;
	try
	{
		sp.addNumber(4);
		sp.addNumber(8);
		sp.addNumber(9);
		int longestSpan = sp.longestSpan();
		int shortestSpan = sp.shortestSpan();
		std::cout << "longestSpan: " << longestSpan << std::endl;
		std::cout << "shortestSpan: " << shortestSpan << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	

    return 0;
}