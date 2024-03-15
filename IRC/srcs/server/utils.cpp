#include "../../headers/Server.hpp"

void	error(std::string errorMessage) {std::cerr << RED << " * Error : " << RESET << errorMessage << std::endl;}

std::string	extractKey(const char	*buffer)
{
	std::string	key;
	int			i = 4;
	int			j = 0;

	while (buffer[i] && (buffer[i] == ' ' || buffer[i] == '\t'))
		i++;
	while (buffer[i]) {
		key.resize(j + 1);
		key[j] = buffer[i];
		j++;
		i++;
	}
	if (key[key.length() - 1] == '\n')
		key.resize(j - 1);
	if (key[key.length() - 1] == '\r')
		key.resize(j - 2);
	return key;
}

std::string tostring(int value) {
    std::stringstream ss;
    ss << value;
    return ss.str();
}
