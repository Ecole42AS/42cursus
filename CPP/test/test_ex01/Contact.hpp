#pragma once
#include <iostream>
#include <string>
#include <limits>
#include <iomanip>

class Contact
{
private:
    std::string first_name;
    std::string last_name;
    std::string nickname;
    std::string phone_number;
    std::string darkest_secret;

    // Constructeur privé prenant toutes les valeurs nécessaires
    Contact(std::string& first_name, std::string& last_name,
            std::string& nickname, std::string& phone_number,
            std::string& darkest_secret);

    // Méthode privée pour saisir les informations de contact
    static std::string _enter_contact_info(const std::string& prompt);

public:
	Contact();

    // Méthode de classe statique pour créer une nouvelle instance de contact
    static Contact create_contact();


    // Méthodes d'accès pour les membres de données const
    std::string get_first_name() const;
    std::string get_last_name() const;
    std::string get_nickname() const;
    std::string get_phone_number() const;
    std::string get_darkest_secret() const;

    // Méthode pour display les informations du contact
    void display_phonebook() const;
	static void truncate(std::string &str);


};
