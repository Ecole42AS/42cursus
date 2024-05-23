#include "PhoneBook.hpp"

int main() {
	std::string input;
    int _current_index = 0; // Déclaration de la variable _current_index
	PhoneBook phonebook; // Création d'une instance de PhoneBook

	while (1)
	{
		std::cout << "Choose ADD, SEARCH or EXIT: " << std::endl;
		std::getline(std::cin, input);
		if (input == "ADD")
		{
			phonebook.add_phonebook_contact(_current_index); // Appel de la méthode add_phonebook_contact()
		}
		else if (input == "SEARCH")
			phonebook.print_contacts();
		else if (input == "EXIT")
			break; //exit();
		else
			std::cout << "Invalid choice: please choose between ADD, SEARCH and EXIT" << std::endl;

	}
	return (0);
}
