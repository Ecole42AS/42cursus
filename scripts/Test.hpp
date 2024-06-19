/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Test.hpp                               			:+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 15:36:50 by astutz            #+#    #+#             */
/*   Updated: 2024/06/19 15:36:50 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>

class Test {
private:
    // Private members here
public:
    Test();
    ~Test();
    Test(const Test &src);
    Test &operator=(const Test &rhs);
};

