#pragma once

# include	"Server.hpp"
# include	<cstdlib>

class Bot
{
	public:
		int			clientSocket;
		std::string	buffer;
		std::string	clientIP;
		Bot(int clientSocket, std::string buffer, std::string	clientIP);
		void	parseBuffer();
		void	randomFactsGenerator();
		void	mySend(const char *msg);
};
