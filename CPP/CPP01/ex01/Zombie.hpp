/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 12:02:06 by astutz            #+#    #+#             */
/*   Updated: 2024/05/24 18:55:46 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include <string>

class Zombie {
private:
    std::string _name;

public:
    Zombie();
    ~Zombie();

    void announce();
    void set_name(std::string name);
};

Zombie* zombie_horde(int N, std::string name);