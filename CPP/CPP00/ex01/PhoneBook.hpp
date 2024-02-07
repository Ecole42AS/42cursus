#pragma once
#ifndef __PHONEBOOK_HPP__
#define __PHONEBOOK_HPP__

class PhoneBook
{
private:
    /* data */
public:
    std::string first_name;
    std::string last_name;
    std::string nick_name;
    int         phone_number;
    std::string darkest_secret;

    PhoneBook(first_name, last_name, nick_name, phone_number, darkest_secret);
    ~PhoneBook();
};

PhoneBook::PhoneBook(/* args */)
{
}

PhoneBook::~PhoneBook()
{
}


#endif


template <typename T, typename U>
class PhoneBook
{
private:

public:
    T first_name;
    T last_name;
    T nick_name;
    U phone_number;
    T darkest_secret;

    PhoneBook(T a, T b, T c, U d, T e)
    {
        first_name =        a;
        last_name =         b;
        nick_name =         c;
        phone_number =      d;
        darkest_secret =    e;
    }
};
