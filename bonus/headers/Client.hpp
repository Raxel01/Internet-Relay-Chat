#pragma once

# include	"Server.hpp"

# define	RESET	"\x1b[0m"
# define	GREEN	"\x1b[1;32m"
# define	RED		"\x1b[1;31m"
# define	ORANGE	"\x1b[1;38;5;208m"
# define	PURPLE	"\x1b[1;38;5;93m"

class Client
{
	public:
		int			clientSocket;
		std::string	buffer_str;
		std::string	client_ip;
		std::string	password;
		std::string	username;
		std::string	nickname;
		bool		isusername;
		bool		isnickname;
		bool		isRegistred;
		Client();
};
