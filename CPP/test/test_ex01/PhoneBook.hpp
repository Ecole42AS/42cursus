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
	// void display_contacts(Contact &_contacts);
	void print_contacts() const; // Méthode pour imprimer les contacts

};