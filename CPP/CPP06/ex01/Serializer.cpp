/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Serializer.cpp                               			:+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 08:33:38 by astutz            #+#    #+#             */
/*   Updated: 2024/06/25 08:33:38 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Serializer.hpp"

Serializer::Serializer() {}

Serializer::~Serializer() {}

Serializer::Serializer(const Serializer &src)
{
    (void)src;
}

Serializer &Serializer::operator=(const Serializer &rhs)
{
	(void)rhs;
	return *this;
}

uintptr_t Serializer::serialize(Data *ptr)
{
	return (reinterpret_cast<uintptr_t>(ptr));
}

Data *Serializer::deserialize(uintptr_t raw)
{
	return (reinterpret_cast<Data *>(raw));
}
