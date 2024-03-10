/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbachar <mbachar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 19:37:37 by abait-ta          #+#    #+#             */
/*   Updated: 2024/03/09 22:49:14 by mbachar          ###   ########.fr       */
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

# define	RESET	"\x1b[0m"
# define	GREEN	"\x1b[1;32m"
# define	RED		"\x1b[1;31m"
# define	ORANGE	"\x1b[1;38;5;208m"
# define	PURPLE	"\x1b[1;38;5;93m"

class	Client;
class Server
{
	public:
		// Attributes
		std::string	_port;
		std::string	_password;
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
