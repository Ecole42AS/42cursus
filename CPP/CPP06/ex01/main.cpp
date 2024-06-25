/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 08:47:26 by astutz            #+#    #+#             */
/*   Updated: 2024/06/25 09:46:35 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Serializer.hpp"
#include "Data.hpp"

int main()
{
	Data myData = {"Rudolph", 10};
	Data *dataPTR = &myData;
	uintptr_t raw = Serializer::serialize(dataPTR);
	Data *returnPTR = Serializer::deserialize(raw);
	returnPTR->age = 11;
	std::cout << "adress of PTR in hexadecimal: " << dataPTR << std::endl;
	std::cout << "adress of return PTR in hexadecimal: " << returnPTR << std::endl;
	std::cout << "value of PTR in uintptr_t: " << raw << std::endl;
	std::cout << "data age returnPTR: " << returnPTR->age << std::endl;
	std::cout << "data age of the instance of Data: " << myData.age << std::endl;
}