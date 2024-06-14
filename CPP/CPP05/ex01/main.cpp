/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 09:13:35 by astutz            #+#    #+#             */
/*   Updated: 2024/06/14 15:13:39 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "Form.hpp"

int main()
{
    // Test des constructeurs et des getters
    try
    {
        Bureaucrat defaultBureaucrat;
        Bureaucrat bob("Bob", 75);
        Form defaultForm;
        Form customForm("Custom Form", false, 50, 100);

        std::cout << defaultBureaucrat << std::endl;
        std::cout << bob << std::endl;
        std::cout << defaultForm << std::endl;
        std::cout << customForm << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Initialization error: " << e.what() << std::endl;
    }

    // Test des méthodes upGrade et downGrade
    try
    {
        Bureaucrat alice("Alice", 2);
        std::cout << alice << std::endl;
        alice.upGrade();
        std::cout << "Alice after upgrade: " << alice << std::endl;

        Bureaucrat charlie("Charlie", 149);
        std::cout << charlie << std::endl;
        charlie.downGrade();
        std::cout << "Charlie after downgrade: " << charlie << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Grade adjustment error: " << e.what() << std::endl;
    }

    // Test de la méthode beSigned et des exceptions de la classe Form
    try
    {
        Bureaucrat dave("Dave", 1);
        Form importantForm("Important Form", false, 1, 1);

        std::cout << "\nBefore signing: " << importantForm << std::endl;
        importantForm.beSigned(dave);
        std::cout << "After signing: " << importantForm << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Signing error: " << e.what() << std::endl;
    }

    // Test de la méthode signForm et des exceptions dans Bureaucrat
    try
    {
        Bureaucrat eve("Eve", 50);
        Form topSecretForm("Top Secret Form", false, 45, 45);

        std::cout << "Before Eve tries to sign: " << topSecretForm << std::endl;
        eve.signForm(topSecretForm);
        std::cout << "After Eve tries to sign: " << topSecretForm << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Form signing error: " << e.what() << std::endl;
    }

    // Test des exceptions pour des grades invalides
    try
    {
        Bureaucrat tooHigh("TooHigh", 0); // Devrait lancer une exception
    }
    catch (const std::exception& e)
    {
        std::cerr << "Caught GradeTooHighException: " << e.what() << std::endl;
    }

    try
    {
        Bureaucrat tooLow("TooLow", 151); // Devrait lancer une exception
    }
    catch (const std::exception& e)
    {
        std::cerr << "Caught GradeTooLowException: " << e.what() << std::endl;
    }

    try
    {
        Form invalidForm("Invalid Form", false, 200, 200); // Devrait lancer une exception
    }
    catch (const std::exception& e)
    {
        std::cerr << "Caught Form GradeTooLowException: " << e.what() << std::endl;
    }

    try
    {
        Form invalidForm("Invalid Form", false, -1, -1); // Devrait lancer une exception
    }
    catch (const std::exception& e)
    {
        std::cerr << "Caught Form GradeTooHighException: " << e.what() << std::endl;
    }

    return 0;
}
