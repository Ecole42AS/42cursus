#pragma once
#include <Contact.hpp>
#include <iomanip>

#define MAX_CONTACTS 8

class PhoneBook
{
private:
	Contact	_contacts[MAX_CONTACTS];
public:
	PhoneBook();
	void add_phonebook_contact(Contact	_contacts);
	void print_tab(Contact _contacts);
};