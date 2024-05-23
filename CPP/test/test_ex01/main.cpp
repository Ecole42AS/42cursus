/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:15:17 by astutz            #+#    #+#             */
/*   Updated: 2024/05/23 13:15:18 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"

int main() {
	std::string input;
    int _current_index = 0;
	PhoneBook phonebook;

	while (1)
	{
		std::cout << "Choose ADD, SEARCH or EXIT: " << std::endl;
		std::getline(std::cin, input);
		if (input == "ADD")
		{
			phonebook.add_phonebook_contact(_current_index);
		}
		else if (input == "SEARCH")
			phonebook.search_contact();
		else if (input == "EXIT")
			break;
		else
			std::cout << "Invalid choice: please choose between ADD, SEARCH and EXIT" << std::endl;

	}
	return (0);
}
