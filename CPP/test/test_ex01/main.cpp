#include "Contact.hpp"

int main() {
	std::string input;

	while (input != "ADD" && input != "EXIT" && input != "SEARCH")
	{
		std::cout << "Choose ADD, SEARCH or EXIT: " << std::endl;
		std::getline(std::cin, input);
		if (input == "ADD")
		{
			Contact::create_contact().afficher();
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