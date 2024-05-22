#include "PhoneBook.hpp"

PhoneBook::PhoneBook() : _current_index(0) {}

void PhoneBook::add_phonebook_contact(int &_current_index) {
    Contact contact = Contact::create_contact();
    _contacts[_current_index] = contact;
    _current_index = (_current_index + 1) % MAX_CONTACTS;

    std::cout << "Contact added successfully." << std::endl;
}
