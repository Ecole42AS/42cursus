/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 10:17:10 by astutz            #+#    #+#             */
/*   Updated: 2024/06/25 13:24:42 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Base.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"

Base *generate(void)
{
	std::srand(static_cast<unsigned int>(std::time(0)));
	int n = std::rand() % 3;
	if (n == 0)
		return new A;
	else if (n == 1)
		return new B;
	else
		return new C;
}

void identify(Base *p)
{
	if (dynamic_cast<A *>(p))
		std::cout << "Pointer point to A" << std::endl;
	else if (dynamic_cast<B *>(p))
		std::cout << "Pointer point to B" << std::endl;
	else if (dynamic_cast<C *>(p))
		std::cout << "Pointer point to C" << std::endl;
	else
		std::cout << "PTR is nullptr" << std::endl;	
}

void identify(Base &p)
{
    try
    {
        dynamic_cast<A &>(p);
        std::cout << "Reference to A" << std::endl;
        return;
    }
    catch (const std::exception& e) {}

    try
    {
        dynamic_cast<B &>(p);
        std::cout << "Reference to B" << std::endl;
        return;
    }
    catch (const std::exception& e) {}

    try
    {
        dynamic_cast<C &>(p);
        std::cout << "Reference to C" << std::endl;
        return;
    }
    catch (const std::exception& e) {}
}


int main()
{
	Base *base = generate();
	identify(base);
	identify(*base);
	delete base;
	return 0;
}
