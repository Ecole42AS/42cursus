/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 20:54:52 by astutz            #+#    #+#             */
/*   Updated: 2024/06/27 09:27:39 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "whatever.hpp"


// ************************** EXERCISE DATA ******************************
int main( void ) {
	int a = 2;
	int b = 3;
	::swap( a, b );
	std::cout << "a = " << a << ", b = " << b << std::endl;
	std::cout << "min( a, b ) = " << ::min( a, b ) << std::endl;
	std::cout << "max( a, b ) = " << ::max( a, b ) << std::endl;
	std::string c = "chaine1";
	std::string d = "chaine2";
	::swap(c, d);
	std::cout << "c = " << c << ", d = " << d << std::endl;
	std::cout << "min( c, d ) = " << ::min( c, d ) << std::endl;
	std::cout << "max( c, d ) = " << ::max( c, d ) << std::endl;
	return 0;
}


// ***********************MY TEST*************************
// int main()
// {
// 	int a = 2;
// 	int b = 3;
// 	char c = 'c';
// 	char d = 'z';
// 	float f = 43.22f;
// 	float g = 34.33f;
// 	std::string s = "string 1";
// 	std::string s2 = "string 2";
	
// 	swap(a, b);
// 	std::cout << "a = " << a << "\nb = " << b << std::endl;
// 	swap(c, d);
// 	std::cout << "c = " << c << "\nd = " << d << std::endl;
// 	swap(f, g);
// 	std::cout << "f = " << f << "\ng = " << g << std::endl;
// 	swap(s, s2);
// 	std::cout << "s = " << s << "\ns2 = " << s2 << std::endl;
	
// 	std::cout << "---------------- MIN --------------" << std::endl;
// 	std::cout << "a = " << a << " b = " << b << " --> min = " << ::min(a, b) << std::endl;
// 	std::cout << "c = " << c << " d = " << d << " --> min = " << ::min(c, d) << std::endl;
// 	std::cout << "f = " << f << " g = " << g << " --> min = " << ::min(f, g) << std::endl;
// 	std::cout << "s = " << s << " s2 = " << s2 << " --> min = " << ::min(s, s2) << std::endl;

// 	std::cout << "---------------- MAX --------------" << std::endl;
// 	std::cout << "a = " << a << " b = " << b << " --> max = " << ::max(a, b) << std::endl;
// 	std::cout << "c = " << c << " d = " << d << " --> max = " << ::max(c, d) << std::endl;
// 	std::cout << "f = " << f << " g = " << g << " --> max = " << ::max(f, g) << std::endl;
// 	std::cout << "s = " << s << " s2 = " << s2 << " --> max = " << ::max(s, s2) << std::endl;
// }