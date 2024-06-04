/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 09:44:09 by astutz            #+#    #+#             */
/*   Updated: 2024/06/04 09:26:37 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cat.hpp"
#include "Dog.hpp"
#include "WrongCat.hpp"
#define ANIMAL_NB 8


// int main()
// {
// 	const Animal* j = new Dog();
// 	const Animal* i = new Cat();
// 	delete j;//should not create a leak
// 	delete i;
	
// 	Animal *animalArray[ANIMAL_NB];
	
// 	for (int i = 0; i < ANIMAL_NB/2; i++)
// 	{
// 		animalArray[i] = new Cat();
// 		std::cout << std::endl;
// 	}

// 	for (int i = ANIMAL_NB / 2; i < ANIMAL_NB; i++)
// 	{
// 		animalArray[i] = new Dog();
// 		std::cout << std::endl;
// 	}
	
// 	for (int i = 0; i < ANIMAL_NB; i++)
// 	{
// 		delete animalArray[i];
// 		std::cout << std::endl;
// 	}
// 	return 0;
// }



int	main(void)
{
	int	nb = 5;
	int	i = -1;
	const Animal	*Herd[nb];

	while (++i < nb)
	{
		if (i % 2 == 0)
		{
			Herd[i] = new Dog;
			std::cout << std::endl;
		}
		else
		{
			Herd[i] = new Cat;
			std::cout << std::endl;
		}
	}

	std::cout << "ANIMAL AND SOUND?" << std::endl;
	std::cout << "The number 2 is " << Herd[1]->getType() << "." << std::endl;
	Herd[1]->makeSound();
	std::cout << "The number 5 is " << Herd[4]->getType() << "." << std::endl;
	Herd[4]->makeSound();
	std::cout << std::endl;

	while (i-- > 0)
	{
		delete Herd[i];
		std::cout << std::endl;
	}

	std::cout << "DEEP COPY" << std::endl;
	Cat	Peach;
	Cat	Peach_tmp;

	Peach.getBrain()->setIdeas(0, "This is an idea!");
	Peach_tmp = Peach;
	std::cout << std::endl;
	std::cout << Peach.getBrain()->getIdeas(0) << "." << std::endl;
	std::cout << Peach_tmp.getBrain()->getIdeas(0) << "." << std::endl;
	std::cout << std::endl;
	Peach.getBrain()->setIdeas(0, "Hell no!");
	std::cout << Peach.getBrain()->getIdeas(0) << "." << std::endl;
	std::cout << Peach_tmp.getBrain()->getIdeas(0) << "." << std::endl;
	std::cout << std::endl;
	return (0);
}


// int	main()
// {

	
// 	return 0;
// }


// int main() {
//     Brain originalBrain;
//     originalBrain.setIdea(0, "Original idea");

//     Brain copiedBrain = originalBrain;
//     std::cout << "Original brain's idea: " << originalBrain.getIdea(0) << std::endl;
//     std::cout << "Copied brain's idea: " << copiedBrain.getIdea(0) << std::endl;

//     // Modifier l'idée de l'original
//     originalBrain.setIdea(0, "Modified original idea");
//     std::cout << "After modifying the original brain's idea:" << std::endl;
//     std::cout << "Original brain's idea: " << originalBrain.getIdea(0) << std::endl;
//     std::cout << "Copied brain's idea: " << copiedBrain.getIdea(0) << std::endl;

//     // Test du polymorphisme et des destructeurs virtuels
//     const Animal *meta = new Animal();
//     const Animal *j = new Dog();
//     const Animal *i = new Cat();
//     std::cout << j->getType() << " " << std::endl;
//     std::cout << i->getType() << " " << std::endl;
//     i->makeSound(); // will output the cat sound!
//     j->makeSound();
//     meta->makeSound();

//     delete meta;
//     delete j;
//     delete i;

//     std::cout << std::endl;
//     const WrongAnimal *wrongMeta = new WrongAnimal();
//     const WrongAnimal *lara = new WrongCat();

//     std::cout << "Lara is a " << lara->getType() << "." << std::endl;
//     lara->makeSound();
//     wrongMeta->makeSound();

//     delete lara;
//     delete wrongMeta;

//     return 0;
// }