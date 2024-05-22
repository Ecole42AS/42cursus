#pragma once
#include "Contact.hpp"
#include <iomanip>

#define MAX_CONTACTS 8

class PhoneBook
{
private:
	Contact	_contacts[MAX_CONTACTS];
    int _current_index;
public:
	PhoneBook();
	void add_phonebook_contact(int &_current_index);
	void print_tab(Contact _contacts);
};