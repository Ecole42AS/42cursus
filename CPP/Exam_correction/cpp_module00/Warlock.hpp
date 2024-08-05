#ifndef WARLOCK_HPP
# define WARLOCK_HPP

#include <iostream>
#include <string>

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
		// Warlock(const std::string name, const std::string title);
		Warlock(const std::string &name, const std::string &title);
		const std::string &getName() const;
		const std::string &getTitle() const;
		void setTitle(const std::string &title);
		void introduce() const;
};

#endif