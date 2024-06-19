/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Test2.hpp                               			:+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 15:37:49 by astutz            #+#    #+#             */
/*   Updated: 2024/06/19 15:37:49 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>

class Test2 {
private:
    // Private members here
public:
    Test2();
    ~Test2();
    Test2(const Test2 &src);
    Test2 &operator=(const Test2 &rhs);
};

