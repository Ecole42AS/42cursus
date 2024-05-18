/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 10:49:18 by astutz            #+#    #+#             */
/*   Updated: 2024/05/18 21:56:09 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"
#include "Contact.hpp"

void Contact::add_contact_info(Contact &instance)
{
    std::cout << "Enter the contact first name: ";
    std::getline(std::cin >> std::ws, instance.first_name);
    std::cout << "Enter the contact last name: ";
    std::getline(std::cin >> std::ws, instance.last_name);
    std::cout << "Enter the contact nick name: ";
    std::getline(std::cin >> std::ws, instance.nick_name);
    std::cout << "Enter the contact phone number: ";
    std::getline(std::cin >> std::ws, instance.phone_number);
    std::cout << "Enter the contact darkest secret: ";
    std::getline(std::cin >> std::ws, instance.darkest_secret);

    
}
//il faut que je fasse un getter et un setter et que je mette les variables en privé