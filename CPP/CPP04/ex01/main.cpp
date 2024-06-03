/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 09:44:09 by astutz            #+#    #+#             */
/*   Updated: 2024/06/03 17:27:07 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cat.hpp"
#include "Dog.hpp"
#include "WrongCat.hpp"
#define ANIMAL_NB 8

// int	main()
// {
// 	for (int i = 0; i < ANIMAL_NB/2; i++)
// 	{
		
// 	}
	
// }


int main() {
    Brain originalBrain;
    originalBrain.setIdea(0, "Original idea");

    Brain copiedBrain = originalBrain;
    std::cout << "Original brain's idea: " << originalBrain.getIdea(0) << std::endl;
    std::cout << "Copied brain's idea: " << copiedBrain.getIdea(0) << std::endl;

    // Modifier l'idée de l'original
    originalBrain.setIdea(0, "Modified original idea");
    std::cout << "After modifying the original brain's idea:" << std::endl;
    std::cout << "Original brain's idea: " << originalBrain.getIdea(0) << std::endl;
    std::cout << "Copied brain's idea: " << copiedBrain.getIdea(0) << std::endl;

    // Test du polymorphisme et des destructeurs virtuels
    const Animal *meta = new Animal();
    const Animal *j = new Dog();
    const Animal *i = new Cat();
    std::cout << j->getType() << " " << std::endl;
    std::cout << i->getType() << " " << std::endl;
    i->makeSound(); // will output the cat sound!
    j->makeSound();
    meta->makeSound();

    delete meta;
    delete j;
    delete i;

    std::cout << std::endl;
    const WrongAnimal *wrongMeta = new WrongAnimal();
    const WrongAnimal *lara = new WrongCat();

    std::cout << "Lara is a " << lara->getType() << "." << std::endl;
    lara->makeSound();
    wrongMeta->makeSound();

    delete lara;
    delete wrongMeta;

    return 0;
}