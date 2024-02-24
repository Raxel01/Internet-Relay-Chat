#include "../../headers/Server.hpp"

void	error(std::string errorMessage) {std::cerr << RED << " * Error : " << RESET << errorMessage << std::endl;}

int	Server::parseInput()
{
	// Parsing Port
	if (port.length() > 5)
		return (error("port length should be either 4 or 5."), 1);
	for (size_t i = 0; i < port.length(); i++)
		if (!std::isdigit(port[i]))
			return (error("port should contain only digits."), 1);
	if (std::atoi(port.c_str()) < 1024 || std::atoi(port.c_str()) > 49151)
		return (error("port should be between 1024 and 49151 for server applications."), 1);

	// Parsing Password
	for (size_t i = 0; i < pass.length(); i++)
		if (pass[i] == ' ' || pass[i] == '\t')
			return (error("password should not contain whitespaces."), 1);

	return 0;
}

void	Server::passSetter(std::string pass) {this->pass = pass;}

void	Server::portSetter(std::string port) {this->port = port;}

std::string	Server::passGetter() {return this->pass;}

std::string	Server::portGetter() {return this->port;}