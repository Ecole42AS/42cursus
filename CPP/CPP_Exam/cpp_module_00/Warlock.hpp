/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Warlock.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astutz <astutz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 16:55:28 by astutz            #+#    #+#             */
/*   Updated: 2024/08/03 17:35:25 by astutz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#pragma once
#include <iostream>

class Warlock
{
	private:
		Warlock();
		Warlock(const Warlock &src);
		Warlock &operator=(const Warlock &rhs);
		std::string _name;
		std::string _title;
	public:
		~Warlock();
		Warlock(const std::string name, const std::string title);
		const std::string &getName() const;
		const std::string &getTitle() const;
		void setTitle(const std::string &title);
		void introduce() const;
};