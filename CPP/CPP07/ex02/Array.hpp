/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Array.hpp                               			:+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 10:45:01 by astutz            #+#    #+#             */
/*   Updated: 2024/06/27 10:45:01 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include <cstring>
#include <ctime>
#include <cstdlib>

template <typename T>
class Array {
private:
	T *_arr;
	unsigned int _size;
public:
    Array<T>();
    Array<T>(unsigned int size);
    ~Array<T>();
    Array<T>(const Array &src);
    Array<T> &operator=(const Array &rhs);
	T &operator[](unsigned int i);
	unsigned int getSize() const;
};

template <typename T>
Array<T>::Array() : _arr(NULL), _size(0) {}

template <typename T>
Array<T>::Array(unsigned int size) : _arr(new T[size]), _size(size) {}

template <typename T>
Array<T>::~Array()
{
	if (_arr)
		delete[] _arr;
}

template <typename T>
Array<T>::Array(const Array &src) : _arr(NULL), _size(src._size)
{
    if (src._arr) 
	{
        _arr = new T[_size];
		std::memcpy(_arr, src._arr, src._size * sizeof(T));
    }
}

template <typename T>
Array<T> &Array<T>::operator=(const Array &rhs)
{
	if (this != &rhs)
	{
		delete[] _arr;
		_size = rhs._size;
		_arr = new T[rhs._size];
		for (unsigned int i = 0; i < _size; i++)
		{
			_arr[i] = rhs._arr[i];
		}
	}
	return *this;
}

template <typename T>
T &Array<T>::operator[](unsigned int i)
{
	if (i >= _size)
		throw std::out_of_range("index out of range");
	return (_arr[i]);
}

template <typename T>
unsigned int Array<T>::getSize() const
{
	return _size;
}