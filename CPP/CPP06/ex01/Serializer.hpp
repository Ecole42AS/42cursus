/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Serializer.hpp                               			:+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 08:33:38 by astutz            #+#    #+#             */
/*   Updated: 2024/06/25 08:33:38 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include <stdint.h>
#include "Data.hpp"


class Serializer {
private:
    Serializer();
    ~Serializer();
    Serializer(const Serializer &src);
    Serializer &operator=(const Serializer &rhs);
public:
	static uintptr_t serialize(Data *ptr);
	static Data *deserialize(uintptr_t raw);
};

