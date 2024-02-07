/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   megaphone.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 13:27:58 by astutz            #+#    #+#             */
/*   Updated: 2024/02/07 15:36:26 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

void megaphone(std::string input)
{    
    for (size_t i = 0; i < input.length(); i++)
        input[i] = toupper(input[i]);
    std::cout << input;
}

int main(int ac, char **av)
{
    
    if (ac != 1)
    {
        for (int i = 1; i < ac; i++)
            megaphone(av[i]);    
    }
    else
        std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *";
    return (0);
}