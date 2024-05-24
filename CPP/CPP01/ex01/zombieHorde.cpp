/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zombieHorde.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 12:09:46 by astutz            #+#    #+#             */
/*   Updated: 2024/05/24 13:33:41 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

Zombie** zombieHorde(int N, std::string name)
{
    if (N < 1)
        return nullptr;

    // Crée un tableau dynamique de pointeurs vers des zombies
    Zombie** zombie_horde = new Zombie*[N];

    // Crée un zombie pour chaque élément du tableau
    for (int i = 0; i < N; i++)
    {
        // Crée un nouveau zombie avec le nom donné
        zombie_horde[i] = new Zombie(name);
    }

    // Retourne le tableau dynamique de pointeurs vers des zombies
    return zombie_horde;
}


// Zombie** zombieHorde(int N, std::string name)
// {
//     if (N < 1)
//         return nullptr;

//     // Crée un tableau dynamique de pointeurs vers des zombies
//     Zombie** zombie_horde = new Zombie*[N];

//     // Crée un zombie pour chaque élément du tableau
//     for (int i = 0; i < N; i++)
//     {
//         // Crée un nouveau zombie avec le nom donné
//         zombie_horde[i] = new Zombie(name);
//     }

//     // Retourne le tableau dynamique de pointeurs vers des zombies
//     return zombie_horde;
// }
