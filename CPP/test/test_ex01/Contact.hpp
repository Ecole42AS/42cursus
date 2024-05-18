#pragma once
#include <iostream>
#include <string>

class Contact
{
private:
    const std::string first_name;
    const std::string last_name;
    const std::string nickname;
    const std::string phone_number;
    const std::string darkest_secret;

    // Constructeur privé prenant toutes les valeurs nécessaires
    Contact(const std::string& first_name, const std::string& last_name,
            const std::string& nickname, const std::string& phone_number,
            const std::string& darkest_secret)
        : first_name(first_name), last_name(last_name),
          nickname(nickname), phone_number(phone_number),
          darkest_secret(darkest_secret) {}

    // Méthode privée pour saisir les informations de contact
    static std::string enter_contact_info(const std::string& prompt)
    {
        std::string input;
        std::cout << prompt << std::endl;
        std::getline(std::cin >> std::ws, input);
        return input;
    }

public:
    // Méthode de classe statique pour créer une nouvelle instance de contact
    static Contact create_contact()
    {
        std::string first_name = enter_contact_info("Enter contact first name:");
        std::string last_name = enter_contact_info("Enter contact last name:");
        std::string nickname = enter_contact_info("Enter contact nickname:");
        std::string phone_number = enter_contact_info("Enter contact phone number:");
        std::string darkest_secret = enter_contact_info("Enter contact darkest secret:");

        return Contact(first_name, last_name, nickname, phone_number, darkest_secret);
    }

    // Autres méthodes de la classe...
};
