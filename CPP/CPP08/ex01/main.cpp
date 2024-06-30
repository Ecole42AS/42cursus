/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 14:30:29 by astutz            #+#    #+#             */
/*   Updated: 2024/06/30 14:51:49 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Span.hpp"

int main() {
	Span sp = Span(6);
	std::cout << "Capacity of vec: " << sp.getVec().capacity() << std::endl;
	try
	{
		// std::vector<int>::iterator it = sp.getVec().begin() + 3;
		// sp.fillVec(sp.getVec().begin(), sp.getVec().end(), 1);
		// sp.fillVec(it, sp.getVec().end(), 1);
		// sp.fillVec(it, 	sp.getVec().end(), 1);
		// sp.fillVec(sp.setVec(sp.getVec()).begin(), sp.setVec(sp.getVec()).end(), 1);
		sp.addNumber(4);
		sp.addNumber(8);
		sp.addNumber(9);
		int longestSpan = sp.longestSpan();
		int shortestSpan = sp.shortestSpan();
		std::cout << "longestSpan: " << longestSpan << std::endl;
		std::cout << "shortestSpan: " << shortestSpan << std::endl;
		sp.printVec();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	try
	{
		std::vector<int> vec;
		vec.push_back(1);
		vec.push_back(2);
		Span sp2 = Span(4);
		std::cout << "Capacity of vec: " << sp2.getVec().capacity() << std::endl;
		std::cout << "Size of vec: " << sp2.getVec().size() << std::endl;
		

		sp2.fillVec(vec.begin(), vec.end(), 3);
		std::cout << "vec print : " << "sp2: " << sp2.getVec().at(1) << "vec: " << vec.at(1) << std::endl;
		sp2.printVec();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	
	try
	{
		Span sp3 = Span(6);
		sp3.addNumber(1);
		sp3.addNumber(2);
		// sp3.setVec().assign(2, 2);
		// sp3.printVec();
		std::vector<int> vec3;
		vec3.assign(4, 4);
		std::cout << "before" << std::endl;
		sp3.printVec();
		sp3.fillVec(vec3.begin(), vec3.end(), 4);
		// sp3.setVec(vec3);
		std::cout << "Print sp3 : " << std::endl;
		sp3.printVec();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	
	

    return 0;
}