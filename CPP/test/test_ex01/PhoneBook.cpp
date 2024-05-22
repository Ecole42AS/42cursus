#include <PhoneBook.hpp>
	
PhoneBook::PhoneBook() : _current_index(0) {}

// void	PhoneBook::add_phonebook_contact(Contact &contact)
// {
// }



void PhoneBook::add_phonebook_contact(const std::string& first_name, const std::string& last_name, const std::string& nickname, const std::string& phone_number, const std::string& darkest_secret) {
    // Créer un nouvel objet Contact en utilisant le constructeur privé de Contact
	Contact new_contact = Contact::create_contact();
    // Ajouter le nouvel objet Contact à votre répertoire
    _contacts[_current_index] = new_contact;
    _current_index = (_current_index + 1) % MAX_CONTACTS;

    std::cout << "Contact added successfully." << std::endl;
}
