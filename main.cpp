#include "./headers/Server.hpp"

int	main(int ac, char *av[])
{
	if (ac != 3)
		return (error("invalid arguments count."), 1);
	Server	srvr;

	srvr.portSetter(av[1]);
	srvr.passSetter(av[2]);
	if (srvr.parseInput())
		return 1;
	// socket() - creates an endpoint for communication
	// socket() params -
	int	socketID = socket(AF_INET, SOCK_STREAM, 0);
	if (socketID == -1) {
		std::cerr << RED << " * Error : " << RESET << "socket function couldn't create an endpoint for communication." << std::endl;
		return 1;
	}
	// setsockopt() - manipulates options for socket referred to by the file description socketFD
	// setsockopt() helps in reusing the ip adress and port and prevents errors such as "address already in use"
	// int	sockoptID = setsockopt(socketID, SOL_SOCKET, );
	return 0;
}
