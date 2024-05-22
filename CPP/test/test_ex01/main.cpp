#include "PhoneBook.hpp"

int main() {
	std::string input;
    int _current_index = 0; // Déclaration de la variable _current_index

	while (input != "ADD" && input != "EXIT" && input != "SEARCH")
	{
		std::cout << "Choose ADD, SEARCH or EXIT: " << std::endl;
		std::getline(std::cin, input);
		if (input == "ADD")
		{
			PhoneBook phonebook; // Création d'une instance de PhoneBook
			phonebook.add_phonebook_contact(_current_index); // Appel de la méthode add_phonebook_contact()
		}
		else if (input == "SEARCH")
			return (1);
		else if (input == "EXIT")
			break;
		else
			std::cout << "Invalid choice: please choose between ADD, SEARCH and EXIT" << std::endl;

	}
	return (0);
}
