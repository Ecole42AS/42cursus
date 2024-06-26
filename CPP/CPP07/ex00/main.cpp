/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 20:54:52 by astutz            #+#    #+#             */
/*   Updated: 2024/06/26 21:38:56 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "whatever.hpp"

int main()
{
	int a = 2;
	int b = 3;
	char c = 'c';
	char d = 'z';
	float f = 43.22f;
	float g = 34.33f;
	std::string s = "string 1";
	std::string s2 = "string 2";
	
	swap(a, b);
	std::cout << "a = " << a << "\nb = " << b << std::endl;
	swap(c, d);
	std::cout << "c = " << c << "\nd = " << d << std::endl;
	swap(f, g);
	std::cout << "f = " << f << "\ng = " << g << std::endl;
	swap(s, s2);
	std::cout << "s = " << s << "\ns2 = " << s2 << std::endl;
	
	std::cout << "---------------- MIN --------------" << std::endl;
	std::cout << "a = " << a << " b = " << b << " --> min = " << ::min(a, b) << std::endl;
	std::cout << "c = " << c << " d = " << d << " --> min = " << ::min(c, d) << std::endl;
	std::cout << "f = " << f << " g = " << g << " --> min = " << ::min(f, g) << std::endl;
	std::cout << "s = " << s << " s2 = " << s2 << " --> min = " << ::min(s, s2) << std::endl;

	std::cout << "---------------- MAX --------------" << std::endl;
	std::cout << "a = " << a << " b = " << b << " --> max = " << ::max(a, b) << std::endl;
	std::cout << "c = " << c << " d = " << d << " --> max = " << ::max(c, d) << std::endl;
	std::cout << "f = " << f << " g = " << g << " --> max = " << ::max(f, g) << std::endl;
	std::cout << "s = " << s << " s2 = " << s2 << " --> max = " << ::max(s, s2) << std::endl;
}