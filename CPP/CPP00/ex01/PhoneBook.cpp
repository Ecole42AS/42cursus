/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:15:41 by astutz            #+#    #+#             */
/*   Updated: 2024/05/23 13:15:42 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"

PhoneBook::PhoneBook() : _current_index(0) {}

void PhoneBook::add_phonebook_contact(int &_current_index) {
    Contact contact = Contact::create_contact();
    _contacts[_current_index] = contact;
    _current_index = (_current_index + 1) % MAX_CONTACTS;

    std::cout << "Contact added successfully." << std::endl;
}


int PhoneBook::print_contacts() const {
	int i = -1;
	std::cout	<< std::setw(10) << "index" << "|"
				<< std::setw(10) << "first name" << "|"
				<< std::setw(10) << "last name" << "|"
				<< std::setw(10) << "nick name" << std::endl;
    while (++i < MAX_CONTACTS) {
        if (!_contacts[i].get_first_name().empty()) {
            std::cout << std::setw(10) << (i + 1) << "|";
			_contacts[i].display_phonebook();
        }
    }
	return (i);
}

void PhoneBook::search_contact() const {

	if (_contacts[0].get_first_name().empty())
	{
		std::cout << "There isn't any contacts !" << std::endl;
		return;
	}
	int i = print_contacts();
	std::string index_input;
	std::cout << "Enter the index of the contact you want to see :" << std::endl;
	std::getline(std::cin, index_input);
	if (index_input[0] > i + '0' || index_input.length() != 1 || index_input[0] < '1')
	{
		std::cout << "Please enter a valid index." << std::endl;
		return;
	}
	i = index_input[0] - 48;
	_contacts[i - 1].display_contact();
	return;
}

