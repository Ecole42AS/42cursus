/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Harl.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 11:53:37 by astutz            #+#    #+#             */
/*   Updated: 2024/05/26 12:13:38 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Harl.hpp"

Harl::Harl() {}

Harl::~Harl() {}

void Harl::debug( void )
{
	std::cout << "I love having extra bacon for my 7XL-double-cheese-triple-pickle-specialketchup burger. I really do!" << std::endl;
}

void Harl::info( void )
{
	std::cout << "I cannot believe adding extra bacon costs more money. You didn’t put enough bacon in my burger! If you did, I wouldn’t be asking for more!" << std::endl;
}

void Harl::warning( void )
{
	std::cout << "I think I deserve to have some extra bacon for free. I’ve been coming for years whereas you started working here since last month." << std::endl;
}

void Harl::error( void )
{
	std::cout << "This is unacceptable! I want to speak to the manager now." << std::endl;	
}

//Comprendre cette ligne : (this->*levels[i].method)(); // Appel de la méthode via le pointeur

void Harl::complain(std::string level) {
    // Tableau ou structure de pointeurs vers les méthodes membres
    struct LevelMethod {
        std::string levelName;
        void (Harl::*method)();
    };

    LevelMethod levels[] = {
        {"DEBUG", &Harl::debug},
        {"INFO", &Harl::info},
        {"WARNING", &Harl::warning},
        {"ERROR", &Harl::error}
    };

    // Recherche du niveau correspondant et appel de la méthode
    for (int i = 0; i < 4; ++i) {
        if (levels[i].levelName == level) {
            (this->*levels[i].method)(); // Appel de la méthode via le pointeur
            return;
        }
    }

    std::cout << "Unknown level: " << level << std::endl;
}