#include "Contact.hpp"

// Default constructor
Contact::Contact() {}

// Constructeur privé prenant toutes les valeurs nécessaires
Contact::Contact(std::string& first_name, std::string& last_name,
                std::string& nickname, std::string& phone_number,
                std::string& darkest_secret)
    : first_name(first_name), last_name(last_name),
      nickname(nickname), phone_number(phone_number),
      darkest_secret(darkest_secret) {}

// Méthode privée pour saisir les informations de contact
std::string Contact::_enter_contact_info(const std::string& prompt)
{
    std::string input;
    std::cout << prompt << std::endl;
    std::getline(std::cin, input);
    if (input.empty()) {
        std::cout << "Input cannot be empty. Please enter a valid input." << std::endl;
        return _enter_contact_info(prompt); // Rappel récursif si la saisie est vide
    }
    return input;
}

// Méthode de classe statique pour créer une nouvelle instance de contact
Contact Contact::create_contact()
{
    std::string first_name = _enter_contact_info("Enter contact first name:");
    std::string last_name = _enter_contact_info("Enter contact last name:");
    std::string nickname = _enter_contact_info("Enter contact nickname:");
    std::string phone_number = _enter_contact_info("Enter contact phone number:");
    std::string darkest_secret = _enter_contact_info("Enter contact darkest secret:");

    return Contact(first_name, last_name, nickname, phone_number, darkest_secret);
}

// Méthodes d'accès pour les membres de données const
std::string Contact::get_first_name() const { return first_name; }
std::string Contact::get_last_name() const { return last_name; }
std::string Contact::get_nickname() const { return nickname; }
std::string Contact::get_phone_number() const { return phone_number; }
std::string Contact::get_darkest_secret() const { return darkest_secret; }

// Méthode pour afficher les informations du contact
void Contact::afficher() const
{
    std::cout << "First Name: " << first_name << std::endl;
    std::cout << "Last Name: " << last_name << std::endl;
    std::cout << "Nickname: " << nickname << std::endl;
    // std::cout << "Phone Number: " << phone_number << std::endl;
    // std::cout << "Darkest Secret: " << darkest_secret << std::endl;
}
