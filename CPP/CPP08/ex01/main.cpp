/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 14:30:29 by astutz            #+#    #+#             */
/*   Updated: 2024/07/16 15:08:25 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Span.hpp"

int main()
{
	try
	{
		Span span(10);
		span.addNumber(10);
		span.addNumber(20);
		span.addNumber(30);
		span.addNumber(40);
		span.addNumber(50);

		std::vector<int> numbers;

		numbers.push_back(60);
		numbers.push_back(70);
		numbers.push_back(80);
		numbers.push_back(90);
		numbers.push_back(100);

		span.addRange(numbers.begin(), numbers.end());

		span.printVec();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}

	return 0;
}