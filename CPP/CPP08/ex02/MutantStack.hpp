/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MutantStack.hpp                               			:+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 18:42:39 by astutz            #+#    #+#             */
/*   Updated: 2024/07/03 18:42:39 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>

class MutantStack {
private:
    // Private members here
public:
    MutantStack();
    ~MutantStack();
    MutantStack(const MutantStack &src);
    MutantStack &operator=(const MutantStack &rhs);
};

