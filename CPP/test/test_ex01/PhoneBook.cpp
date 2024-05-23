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
    for (int i = 0; i < MAX_CONTACTS; ++i) {
        if (!_contacts[i].get_first_name().empty()) {
            std::cout << setw((i + 1)) << std::endl;
            _contacts[i].afficher();
            std::cout << std::endl;
        }
    }
}
