/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:15:55 by astutz            #+#    #+#             */
/*   Updated: 2024/05/23 13:15:56 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "Contact.hpp"

#define MAX_CONTACTS 8

class PhoneBook
{
private:
	Contact	_contacts[MAX_CONTACTS];
    int _current_index;
public:
	PhoneBook();
	void add_phonebook_contact(int &_current_index);
	int print_contacts() const;
	void print_index_contact () const;
	void search_contact() const;
};