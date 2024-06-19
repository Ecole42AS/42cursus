/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Olaf.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 15:04:41 by astutz            #+#    #+#             */
/*   Updated: 2024/06/19 15:12:01 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

class Olaf {
private:
    // Private members here
public:
    Olaf();
    ~Olaf();
    Olaf(const Olaf &src);
    Olaf &operator=(const Olaf &rhs);
};
