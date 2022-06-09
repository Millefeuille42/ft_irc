#ifndef USER_HPP
#define USER_HPP

#include <iostream>
#include <unistd.h>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>

class User {
	public:
		User();
		User(int& fd);
		~User();
		User(const User& src);
		User& operator=(const User& src);

		const std::string& getName() const;
		void setName(std::string n);
		bool getFirst() const;

	private:
		int _fd;
		bool _first;
		std::string _name;

};

#endif //USER_HPP
