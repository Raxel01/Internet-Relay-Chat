#include "../../headers/Server.hpp"

void	error(std::string errorMessage) {std::cerr << RED << " * Error : " << RESET << errorMessage << std::endl;}

std::string	extractKey(char	*buffer)
{
	std::string	key;
	size_t i = 4;
	size_t j = 0;
	while (buffer[i]) {
		if (buffer[i] && buffer[i] != ' ' && buffer[i] != '\t') {
			key.resize(j + 1);
			key[j] = buffer[i];
			j++;
			i++;
		}
		else
			i++;
	}
	key.resize(j - 1);
	return key;
}
