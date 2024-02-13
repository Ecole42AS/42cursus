/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 08:43:56 by astutz            #+#    #+#             */
/*   Updated: 2024/02/08 14:08:20 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"
#include <iostream>
// void add_contact(PhoneBook::Phonebook(first_name, b, c, d, e))
// {
//     Contact instance;
    

    
    
// }

int main(int ac, char **av)
{
    std::string action;
    
    while (action != "EXIT")
    {
        std::cout << "Please choose an action: ADD / SEARCH / EXIT : ";
        std::cin >> action;
        std::cout << action;
        if (action == "ADD")
        {
            Contact 
        }
        else if (action == "SEARCH")
        {
            
        }
    }
    
    
    
}

on recupere des donnée de l utilisateur sous forme de variables et je veux que ces données soient des valeurs const d une instance de contact


ce contact doit ensuite etre répertorier dans le Phonebook avec un index(je dois donc ajouter les 8 instance de la classe contact dans Phone book et si il y en a un 9 eme il remplace le premier)

Si l utilisateur tape SEARCH on lui demande le n de l index et on affiche le contact correspondant

