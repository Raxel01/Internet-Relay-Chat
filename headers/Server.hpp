#pragma once

# include	<iostream>
# include	<sys/types.h>
# include	<sys/socket.h>
# include	<cstdlib>

# define	RESET	"\x1b[0m"
# define	GREEN	"\x1b[1;32m"
# define	RED		"\x1b[1;31m"
# define	ORANGE	"\x1b[1;38;5;208m"
# define	PURPLE	"\x1b[1;38;5;93m"

class Server
{
	private:
		std::string	port;
		std::string	pass;
	public:
		int			parseInput();
		void		portSetter(std::string port);
		std::string	portGetter();
		void		passSetter(std::string pass);
		std::string	passGetter();
};

void		error(std::string errorMessage);