/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ta <abait-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 19:37:37 by abait-ta          #+#    #+#             */
/*   Updated: 2024/03/15 16:54:45 by abait-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include	<iostream>
# include	<sys/types.h>
# include	<sys/socket.h>
# include	<cstdlib>
# include	<netinet/in.h>
# include	<unistd.h>
# include	<fcntl.h>
# include	<poll.h>
# include	<arpa/inet.h>
# include	<vector>
# include	<map>
# include	<sstream>
# include	"Client.hpp"
# include	<netdb.h>
# include	<arpa/inet.h>
# include	<signal.h>
# include	<cstring>
# include	<string>
# include	<sstream>
# include 	"ReforMessage.hpp"
# include 	"Bot.hpp"

# define	RESET	"\x1b[0m"
# define	GREEN	"\x1b[1;32m"
# define	RED		"\x1b[1;31m"
# define	ORANGE	"\x1b[1;38;5;208m"
# define	PURPLE	"\x1b[1;38;5;93m"

# define RPL_WELCOME(nick, hostname)                                         ":" + std::string(hostname) + " 001 " + nick + " :Welcome " + nick + " to the ft_irc network !\r\n"
# define RPL_YOURHOST(nick, hostname)                                        ":" + std::string(hostname) + " 002 " + nick + " :Your host is " + std::string(hostname) + " running version 1.1 !\r\n"
# define RPL_CREATED(nick, hostname)                                         ":" + std::string(hostname) + " 003 " + nick + " :This server was created on 2024-02-15 !\r\n"
# define RPL_MYINFO(nick, hostname)                                          ":" + std::string(hostname) + " 004 " + nick + " :Host: " + std::string(hostname) + ", Version: 1.1, User mode: none, Channel modes: o, t, k, i, l !\r\n"

class	Client;
class Server
{
	public:
		// Attributes
		std::string	_port;
		std::string	_password;
		std::string	_ipaddress;
		static std::map<int, Client> ServerClients;
		// Methods
		Server(std::string port, std::string password);
		int			parseInput();
		int			start();
		void		addClient(int clientSocket, std::string client_ip);
		void		processClientData(std::string buffer, std::map<int, Client>::iterator &it);
		std::map<int, Client>::iterator	findSocket(int clientSocket);
		void		mySend(const char *msg, int clientSocket);
};

void		error(std::string errorMessage);
std::string	extractKey(const char	*buffer);
std::string tostring(int value);
