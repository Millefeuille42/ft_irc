//
// Created by mlabouri on 6/8/22.
//

#ifndef SOCKSERVER_HPP
#define SOCKSERVER_HPP

#include "ft_irc.hpp"
#include "SockAddress.hpp"
#include "errors.hpp"


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
		void transmit(const User& user, std::string message, std::basic_ostream<char> & otp);
		void transmitServ(const std::string& message);
		static void transmitToChannel(Channels &chan, const User &user, const std::string& message);
		static void transmitToChannelFromServ(Channels &chan, const std::string& message);
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
		static std::vector<User *> getUsersByNick(SockServer &, const std::string &nick);
		static std::vector<User *> getUsersByRealName(SockServer &, const std::string &realname);
		static std::vector<User *> getUsersByUsername(SockServer &, const std::string &username);

		fdIterator begin();
		fdIterator end();

		static void sendMessage(int target, const std::string & message, std::basic_ostream<char> & otp);
		static void sendMessage(int target, const std::string & message);

		static void welcome(SockServer &srv, const std::vector<std::string>&, User& user);
		static void pass(SockServer &srv, std::vector<std::string>& args, User& user);
		static void user(SockServer &srv, std::vector<std::string>& args, User& user);
		static void ping(SockServer &srv, std::vector<std::string>& args, User& user);
		static void kick(SockServer &srv, std::vector<std::string>& args, User& user);
		static void kill(SockServer &srv, std::vector<std::string>& args, User& user);
		static void nick(SockServer &srv, std::vector<std::string>& args, User& user);
		static void quit(SockServer &srv, std::vector<std::string>& args, User& user);
		static void oper(SockServer &srv, std::vector<std::string>& args, User& user);
		static void time(SockServer &srv, std::vector<std::string> &, User& user);
		static void version(SockServer &srv, std::vector<std::string> &, User& user);
		static void info(SockServer &srv, std::vector<std::string> &, User& user);
		static void who(SockServer &srv, std::vector<std::string> &, User& user);
		static void privmsg(SockServer &srv, std::vector<std::string> &, User& user);
		static void join(SockServer &srv, std::vector<std::string>& args, User& user);
		static void mode(SockServer &srv, std::vector<std::string> &, User& user);
		static void part(SockServer &srv, std::vector<std::string> &, User& user);
		static void topic(SockServer &srv, std::vector<std::string> &, User& user);
		static void names(SockServer &srv, std::vector<std::string> & args, User&);
		static void list(SockServer &srv, std::vector<std::string> & args, User&);
		static void invite(SockServer &srv, std::vector<std::string> &, User& user);
		static void error(const std::string& reason, User& user);

	std::string password;
};

#endif //SOCKSERVER_HPP
