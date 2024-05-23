#include "PhoneBook.hpp"

PhoneBook::PhoneBook() : _current_index(0) {}

void PhoneBook::add_phonebook_contact(int &_current_index) {
    Contact contact = Contact::create_contact();
    _contacts[_current_index] = contact;
    _current_index = (_current_index + 1) % MAX_CONTACTS;

    std::cout << "Contact added successfully." << std::endl;
}


// void display_contacts(Contact &_contacts)
// {

// 	for(int i = 0; i < MAX_CONTACTS; i++)
// 	{
// 		std::cout << _contacts[i] << std::endl;
// 	}
// }

void PhoneBook::print_contacts() const {
	std::cout	<< std::setw(10) << "index" << "|"
				<< std::setw(10) << "first name" << "|"
				<< std::setw(10) << "last name" << "|"
				<< std::setw(10) << "nick name" << std::endl;
    for (int i = 0; i < MAX_CONTACTS; ++i) {
        if (!_contacts[i].get_first_name().empty()) {
            std::cout << std::setw(10) << (i + 1) << "|";
            _contacts[i].display_phonebook();
        }
    }
}

