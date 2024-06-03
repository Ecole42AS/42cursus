/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 09:44:09 by astutz            #+#    #+#             */
/*   Updated: 2024/06/03 12:01:24 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cat.hpp"
#include "Dog.hpp"
#include "WrongCat.hpp"

// int main()
// {
// 	const Animal* meta = new Animal();
// 	const Animal* j = new Dog();
// 	const Animal* i = new Cat();
// 	std::cout << j->getType() << " " << std::endl;
// 	std::cout << i->getType() << " " << std::endl;
// 	i->makeSound(); //will output the cat sound!
// 	j->makeSound();
// 	meta->makeSound();
// 	// ...
// 	return 0;
// }

int	main(void)
{
	const Animal	*Meta = new Animal();
	const Animal	*Rudolph = new Dog();
	const Animal	*Daisy = new Cat();

	std::cout << "Rudolph is a " << Rudolph->getType() << "." << std::endl;
	std::cout << "Daisy is a " << Daisy->getType() << "." << std::endl;
	Rudolph->makeSound();
	Daisy->makeSound();
	Meta->makeSound();

	delete Daisy;
	delete Rudolph;
	delete Meta;

	std::cout << std::endl;
	const WrongAnimal 	*WrongMeta = new WrongAnimal();
	const WrongAnimal	*Lara = new WrongCat();

	std::cout << "Lara is a " << Lara->getType() << "." << std::endl;
	Lara->makeSound();
	WrongMeta->makeSound();

	delete Lara;
	delete WrongMeta;
	return (0);
}