#pragma once
#include <Contact.hpp>
#include <iomanip>

#define MAX_CONTACTS 8

class PhoneBook
{
private:
	Contact	_contacts[MAX_CONTACTS];
    int _current_index;
public:
	PhoneBook();
	void add_phonebook_contact(const std::string& first_name, const std::string& last_name, const std::string& nickname, const std::string& phone_number, const std::string& darkest_secret);
	void print_tab(Contact _contacts);
};