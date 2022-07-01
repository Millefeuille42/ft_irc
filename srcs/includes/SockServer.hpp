//
// Created by mlabouri on 6/8/22.
//

#ifndef SOCKSERVER_HPP
#define SOCKSERVER_HPP

#include "ft_irc.hpp"
#include "SockAddress.hpp"
#include "_SockServer_Errors.hpp"


class SockServer {
	private:
		typedef void(*command)(SockServer &, std::vector<std::string>&, User&);
		std::string _port;
		t_pollfd _serverFd;
		fdVector _fds;
		userMap _users;
		stringVector _nicks;
		channelsMap _chans;
		std::map<std::string, command> _commands;

	public:
		SockServer();
		SockServer(const std::string & port);
		SockServer(const SockServer & src);

		~SockServer();

		SockServer &operator=(const SockServer & src);

		void initCommands();

		void deleteClient(const fdIterator &  client);
		int check();

		int acceptConnection(SockAddress & addr) const;
		void transmit(User& user, std::string message, std::basic_ostream<char> & otp);
		void transmitServ(std::string& message);
		void transmitToChannel(Channels &chan, User &user, const std::string& message);
		std::string readMessage(int fd, bool &err);

		void messageRouter( int fd, std::string &msg);

		void printStart();

		t_pollfd *getFds();
		size_t getSize();
		int getFd() const;
		stringVector& getNicks();
		User *getUserByNick(const std::string &nick);
		User *getUserByRealName(const std::string &realname);
		User *getUserByUsername(const std::string &username);

		fdIterator begin();
		fdIterator end();

		static void sendMessage(int target, const std::string & message, std::basic_ostream<char> & otp);
		static void sendMessage(int target, const std::string & message);

		static void welcome(SockServer &srv, const std::vector<std::string>&, User& user);
		static void pass(SockServer &srv, std::vector<std::string>& args, User& user);
		static void user(SockServer &srv, std::vector<std::string>& args, User& user);
		static void ping(SockServer &srv, std::vector<std::string>& args, User& user);
		static void kill(SockServer &srv, std::vector<std::string>& args, User& user);
		static void nick(SockServer &srv, std::vector<std::string>& args, User& user);
		static void quit(SockServer &srv, std::vector<std::string>& args, User& user);
		static void oper(SockServer &srv, std::vector<std::string>& args, User& user);
		static void time(SockServer &srv, std::vector<std::string> &, User& user);
		static void version(SockServer &srv, std::vector<std::string> &, User& user);
		static void info(SockServer &srv, std::vector<std::string> &, User& user);
		static void who(SockServer &srv, std::vector<std::string>& args, User& user);
		static void privmsg(SockServer &srv, std::vector<std::string> &, User& user);
		static void join(SockServer &srv, std::vector<std::string>& args, User& user);

		std::string password;
};

#endif //SOCKSERVER_HPP
