/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:15:22 by astutz            #+#    #+#             */
/*   Updated: 2024/05/23 13:15:23 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Contact.hpp"

Contact::Contact() {}

Contact::Contact(std::string& first_name, std::string& last_name,
                std::string& nickname, std::string& phone_number,
                std::string& darkest_secret)
    : first_name(first_name), last_name(last_name),
      nickname(nickname), phone_number(phone_number),
      darkest_secret(darkest_secret) {}

std::string Contact::_enter_contact_info(const std::string& prompt)
{
    std::string input;
    std::cout << prompt << std::endl;
    std::getline(std::cin, input);
    if (input.empty()) {
        std::cout << "Input cannot be empty. Please enter a valid input." << std::endl;
        return _enter_contact_info(prompt);
    }
    return input;
}

Contact Contact::create_contact()
{
    std::string first_name = _enter_contact_info("Enter contact first name:");
    std::string last_name = _enter_contact_info("Enter contact last name:");
    std::string nickname = _enter_contact_info("Enter contact nickname:");
    std::string phone_number = _enter_contact_info("Enter contact phone number:");
    std::string darkest_secret = _enter_contact_info("Enter contact darkest secret:");

    return Contact(first_name, last_name, nickname, phone_number, darkest_secret);
}

std::string Contact::get_first_name() const { return first_name; }

void Contact::truncate(std::string& str)
{
    if (str.length() > 10)
        str = str.substr(0, 9) + '.';
}


void Contact::display_phonebook() const
{
	std::string tmp_first_name = first_name; 
	std::string tmp_last_name = last_name; 
	std::string tmp_nickname = nickname;

	truncate(tmp_first_name);
	truncate(tmp_last_name);
	truncate(tmp_nickname);

    std::cout << std::setw(10) << tmp_first_name << "|";
    std::cout << std::setw(10) << tmp_last_name << "|";
    std::cout << std::setw(10) << tmp_nickname << std::endl;
}

void Contact::display_contact() const
{
	std::cout << "First_name: " << first_name << std::endl;
	std::cout << "Last_name: " << last_name << std::endl;
	std::cout << "Nickname: " << nickname << std::endl;
	std::cout << "Phone Number: " << phone_number << std::endl;
    std::cout << "Darkest Secret: " << darkest_secret << std::endl;
}
