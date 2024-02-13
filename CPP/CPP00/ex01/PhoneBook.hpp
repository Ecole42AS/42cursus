#pragma once
#ifndef __PHONEBOOK_HPP__
#define __PHONEBOOK_HPP__

#include <iostream>
#include <string>


// class PhoneBook
// {
// private:
//     /* data */
// public:
//     std::string first_name;
//     std::string last_name;
//     std::string nick_name;
//     int         phone_number;
//     std::string darkest_secret;

//     PhoneBook(first_name, last_name, nick_name, phone_number, darkest_secret);
//     ~PhoneBook();
// };

// PhoneBook::PhoneBook(first_name, last_name, nick_name, phone_number, darkest_secret) :  first_name(a), 
//                                                                                         last_name(b),
//                                                                                         nick_name(c),
//                                                                                         phone_number(d),
//                                                                                         darkest_secret(e)
// {
//     std::cout << "ceci est un constructeur" << std::endl;
// }

// PhoneBook::~PhoneBook()
// {
//     std::cout << "ceci est un destructeur" << std::endl;
// }




// template <typename T, typename U>
// class PhoneBook
// {
// private:

// public:
//     T first_name;
//     T last_name;
//     T nick_name;
//     U phone_number;
//     T darkest_secret;

//     PhoneBook(T a, T b, T c, U d, T e)
//         : first_name(a),
//           last_name(b),
//           nick_name(c),
//           phone_number(d),
//           darkest_secret(e)
//     {
//         std::cout << "ceci est un constructeur" << std::endl;
//     }

//     ~PhoneBook()
//     {
//         //Code pour libérer la mémoire (p. ex si new a été utiliser)
//         std::cout << "ceci est un destructeur" << std::endl;
//     }


// };



class PhoneBook
{
    private:

    public:
        std::string contacts[8];
};


#endif
