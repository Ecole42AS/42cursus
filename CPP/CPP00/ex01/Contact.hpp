/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 10:32:56 by astutz            #+#    #+#             */
/*   Updated: 2024/02/08 11:34:45 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef CONTACT_HPP
    #define CONTACT_HPP

#include "PhoneBook.hpp"
template <typename T>

class Contact
{
    private:
    
    public:
        T const first_name;
        T const last_name;
        T const nick_name;
        T const phone_number;
        T const darkest_secret;
        
        void add_contact_info(Contact &instance);
        
};



#endif // !CONTACT_HPP