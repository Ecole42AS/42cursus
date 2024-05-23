/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:15:58 by astutz            #+#    #+#             */
/*   Updated: 2024/05/23 13:15:59 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include <string>
#include <limits>
#include <iomanip>

class Contact
{
private:
    std::string first_name;
    std::string last_name;
    std::string nickname;
    std::string phone_number;
    std::string darkest_secret;

    Contact(std::string& first_name, std::string& last_name,
            std::string& nickname, std::string& phone_number,
            std::string& darkest_secret);

    static std::string _enter_contact_info(const std::string& prompt);

public:
	Contact();

    static Contact create_contact();


    std::string get_first_name() const;

    void display_phonebook() const;
	void display_contact() const;
	static void truncate(std::string &str);


};
