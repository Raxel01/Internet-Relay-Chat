#include "./headers/Server.hpp"

int	main(int ac, char *av[])
{
	if (ac != 3)
		return (error("parameter format should be as follow (./ircserv <port> <password>)."), 1);

	Server	srvr(av[1], av[2]);
	if (srvr.parseInput())
		return 1;

	if (srvr.start())
		return 1;

	return 0;
}
