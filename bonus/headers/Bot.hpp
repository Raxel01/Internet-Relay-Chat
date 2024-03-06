#pragma once

# include	"Server.hpp"
# include	<cstdlib>

class Bot
{
	public:
		int		clientSocket;
		char	*buffer;
		Bot(int clientSocket, char *buffer);
		void	parseBuffer();
		void	randomFactsGenerator();
		void	mySend(const char *msg);
};
