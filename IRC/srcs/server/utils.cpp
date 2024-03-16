#include "../../headers/Server.hpp"

void	error(std::string errorMessage) {std::cerr << RED << " * Error : " << RESET << errorMessage << std::endl;}

std::string	extractKey(const char	*buffer)
{
	std::string	key;
	int			i = 4;
	int			j = 0;

	while (buffer[i] && (buffer[i] == '\t' || buffer[i] == ' '))
		i++;
	while (buffer[i]) {
		key.resize(j + 1);
		key[j] = buffer[i];
		j++;
		i++;
	}
	size_t n_pos = key.find('\n');
	if (n_pos != std::string::npos)
		key.resize(n_pos);
	size_t r_pos = key.find('\r');
	if (r_pos != std::string::npos)
		key.resize(r_pos);
	return key;
}

std::string tostring(int value) {
    std::stringstream ss;
    ss << value;
    return ss.str();
}
