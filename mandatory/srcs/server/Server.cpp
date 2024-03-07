#include "../../headers/Server.hpp"

std::map<int, Client> Server::ServerClients;

Server::Server(std::string port, std::string password)
{
	this->_port = port;
	this->_password = password;
}

int	Server::parseInput()
{
	// Parsing Port
	if (_port.length() > 5)
		return (error("port length should be either 4 or 5."), 1);
	for (size_t i = 0; i < _port.length(); i++)
		if (!std::isdigit(_port[i]))
			return (error("port should contain only digits."), 1);
	if (std::atoi(_port.c_str()) < 1024 || std::atoi(_port.c_str()) > 49151)
		return (error("port should be between 1024 and 49151 for server applications."), 1);

	// Parsing Password
	for (size_t i = 0; i < _password.length(); i++)
		if (_password[i] == ' ' || _password[i] == '\t')
			return (error("password should not contain whitespaces."), 1);

	return 0;
}

int	Server::start()
{
	struct sockaddr_in	server_address;
	int			opt		= 1;
	bzero(&server_address, sizeof(sockaddr_in));

	server_address.sin_family		= AF_INET;
	server_address.sin_addr.s_addr	= INADDR_ANY;
	server_address.sin_port			= htons(std::atoi(_port.c_str()));

	int	serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (serverSocket == -1)
		return (error("socket function couldn't create an endpoint for communication."), 1);

	if (setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1)
		return (error("socket was unable to reuse the ip address."), 1);

	if (bind(serverSocket, (sockaddr *)&server_address, sizeof(server_address)) == -1)
		return (error("socket was unable to bind to ip adress and port number."), 1);

	if (fcntl(serverSocket, F_SETFL, O_NONBLOCK) == -1)
		return (error("failed to set the socket to non-blocking mode."), 1);

	if (listen(serverSocket, 128) == -1)
		return (error("socket could not listen to incoming connections."), 1);

	std::cout << GREEN << " * Server started, listening on port " << PURPLE << _port << GREEN << " for any incoming connections." << RESET << std::endl;

	// Polling and other stuff
	std::vector<pollfd>	sockets;
	sockaddr_in			client_address;
	socklen_t			client_address_len = sizeof(client_address);
	char				client_ip[INET_ADDRSTRLEN];
	int					clientSocket;
	size_t				i = 0;

	sockets.push_back((pollfd){.fd = serverSocket, .events = POLLIN, .revents = 0});
	std::map<int, Client>::iterator	it;
	while (true) {
		try {
			if (poll(sockets.begin().base(), sockets.size(), -1) == -1)
				exit (1);
			i = 0;
			while (i < sockets.size()) {
				if (POLLIN & sockets[i].revents) {
					if (sockets[i].fd == serverSocket) {
						bzero(&client_address, sizeof(sockaddr_in));
						clientSocket = accept(serverSocket, (sockaddr *)&client_address, &client_address_len);
						sockets.push_back((pollfd){.fd = clientSocket, .events = POLLIN, .revents = 0});
						i = sockets.size() - 1;
    					inet_ntop(AF_INET, &(client_address.sin_addr), client_ip, INET_ADDRSTRLEN);
						std::string	ip_str(client_ip);
						addClient(sockets[i].fd, ip_str);
						it = findSocket(sockets[i].fd);
						std::cout << GREEN << " * Client " << PURPLE << it->second.client_ip << RESET << " connected successfuly." << std::endl;
					}
					else {
						char buffer[1024] = {0};
						ssize_t	rcvlen = recv(sockets[i].fd, buffer, 1024, 0);
						if (rcvlen <= 0) {
							it = findSocket(sockets[i].fd);
							std::cout << RED << " * Client " << PURPLE << it->second.client_ip << RESET << " has disconnected." << std::endl;
							std::vector<pollfd>::iterator it_;
							for (it_ = sockets.begin(); it_ != sockets.end(); it_++) {
								if (it_->fd == sockets[i].fd)
									break ;
							}
							close(sockets[i].fd);
							sockets.erase(it_);
							Server::ServerClients.erase(it->first);
							break;
						}
						else {
							it = findSocket(sockets[i].fd);
							processClientData(buffer, it);
						}
					}
				}
				i++;
			}
		}
		catch (std::exception &e) {
			return (error(e.what()), 1);
		}
	}
    return 0;
}

void	Server::processClientData(char *buffer, std::map<int, Client>::iterator &it)
{
	std::string	password;
	std::string	nickname;
	std::string	username;

	if (!std::strncmp(buffer, "PASS ", 5) || !std::strncmp(buffer, "PASS\t", 5)) {
		if (it->second.isRegistred) {
			mySend(" * Error 462 : You are already registred.\n", it->first);
			return ;
		}
		if (std::strlen(buffer) == 4 || std::strlen(buffer) == 5) {
			mySend(" * Error 461 : Missing password, correct syntax is (PASS server_password).\n", it->first);
			return ;
		}
		password = extractKey(buffer);
		if (password != _password) {
			mySend(" * Error 464 : Incorrect password.\n", it->first);
			return ;
		}
		if (password == _password) {
			mySend(" * Success   : You have entered the correct password.\n", it->first);
			mySend(" * Hint      : Now you can set yourself a nickname by using (NICK your_nickname).\n", it->first);
			it->second.isRegistred = true;
		}
	}
	else if (!std::strncmp(buffer, "NICK ", 5) || !std::strncmp(buffer, "NICK\t", 5)) {
		if (!it->second.isRegistred) {
			mySend(" * Error 911 : You need to enter the server's password first using (PASS server_password).\n", it->first);
			return ;
		}
		if (it->second.isnickname) {
			mySend(" * Error 462 : You already have a nickname.\n", it->first);
			return ;
		}
		if (std::strlen(buffer) == 4 || std::strlen(buffer) == 5) {
			mySend(" * Error 431 : Missing nickname, correct syntax is (NICK your_nickname).\n", it->first);
			return ;
		}
		nickname = extractKey(buffer);
		if (nickname[0] == '&' || nickname[0] == '#' || nickname[0] == ':') {
			mySend(" * Error 432 : nickname musn't contain '#' or '&' or ':' as trailing characters.\n", it->first);
			return ;
		}
		for (size_t i = 0; i < nickname.size(); i++) {
			if (nickname[i] == ' ' || nickname[i] == '\t') {
				mySend(" * Error 432 : nickname musn't contain whitespaces.\n", it->first);
				return ;
			}
		}
		for (std::map<int, Client>::iterator it_ = Server::ServerClients.begin(); it_ != Server::ServerClients.end(); it_++) {
			if (nickname == it_->second.nickname) {
				mySend(" * Error 433 : Someone in the server is already using that nickname.\n", it->first);
				return ;
			}
		}
		it->second.nickname = nickname;
		it->second.isnickname = true;
		mySend(" * Success   : You have set yourself a nickname.\n", it->first);
		mySend(" * Hint      : Now you can set yourself a username by using (USER <username> 0 * <realname>).\n", it->first);
	}
	else if (!std::strncmp(buffer, "USER ", 5) || !std::strncmp(buffer, "USER\t", 5)) { // Some missing parsing here
		if (!it->second.isRegistred) {
			mySend(" * Error 911 : You need to enter the server's password first using (PASS server_password).\n", it->first);
			return ;
		}
		if (!it->second.isnickname) {
			mySend(" * Error 912 : You need to set yourself a nickname first using (NICK your_nickname).\n", it->first);
			return ;
		}
		if (it->second.isusername) {
			mySend(" * Error 462 : You already have a username.\n", it->first);
			return ;
		}
		int count_spaces = 0;
		size_t i = 0;
		for (i = 0; i < std::strlen(buffer); i++) {
			if (buffer[i] == ' ')
				count_spaces++;
			if (count_spaces == 4)
				break;
		}
		size_t j = 0;
		i++;
		if (count_spaces == 4) {
			while (buffer[i]) {
				username.resize(j + 1);
				username[j++] = buffer[i++];
			}
			for (std::map<int, Client>::iterator it_ = Server::ServerClients.begin(); it_ != Server::ServerClients.end(); it_++) {
				if (username == it_->second.username) {
					mySend(" * Error 433 : Someone in the server is already using that username.\n", it->first);
					return ;
				}
			}
			username.resize(j - 1);
			it->second.username = username;
			it->second.isusername = true;
			mySend(" * Success   : You have set yourself a username.\n", it->first);
			mySend(" * Hint      : For more commands, use (HELP).\n", it->first);
		}
		else {
			mySend(" * Error 913 : Missing arguments, syntax should be as follow (USER <username> 0 * <realname>).\n", it->first);
			return ;
		}
	}
	else if (!std::strcmp(buffer, "HELP\n")) {
		if (!it->second.isRegistred || !it->second.isnickname || !it->second.isusername) {
			mySend(" * Error 913 : You need to be authenticated before using this command.\n", it->first);
			return ;
		}
		mySend(" * KICK    - Ejects a client from the channel.\n", it->first);
		mySend(" * INVITE  - Invites a client to a channel.\n", it->first);
		mySend(" * TOPIC   - Changes or view the channel topic.\n", it->first);
		mySend(" * JOIN    - Creates a channel if it doesn't exit or join an existing one.\n", it->first);
		mySend(" * PRIVMSG - Sends a private message to a client or a channel.\n", it->first);
		mySend(" * MODE    - Changes the channel's mode :\n", it->first);
		mySend("\t1. +/- i: Sets/removes Invite-only channel.\n", it->first);
		mySend("\t2. +/- t: Sets/removes the restrictions of the TOPIC command to channel operators.\n", it->first);
		mySend("\t3. +/- k: Sets/removes the channel key (password).\n", it->first);
		mySend("\t4. +/- k: Gives/takes channel operator privilege.\n", it->first);
		mySend("\t5. +/- o: Gives/takes channel operator privilege.\n", it->first);
		mySend("\t6. +/- l: Sets/removes the user limit to channel.\n", it->first);
	}
	else if (!std::strcmp(buffer, "PRINT\n")) {
		for (std::map<int, Client>::iterator ite = ServerClients.begin(); ite != ServerClients.end(); ite++) {
			std::cout << PURPLE << "====================================================================" << RESET << std::endl;
			std::cout << GREEN << " * Client Socket   = " << RESET << ite->first << std::endl;
			std::cout << GREEN << " * Client IpAdress = " << RESET << ite->second.client_ip << std::endl;
			std::cout << GREEN << " * Client NickName = " << RESET << ite->second.nickname << std::endl;
			std::cout << GREEN << " * Client UserName = " << RESET << ite->second.username << std::endl;
			if (ite->second.isRegistred == true)
				std::cout << GREEN << " * Client Status   = " << RESET << "Registred" << std::endl;
			else
				std::cout << GREEN << " * Client Status   = " << RESET << "Not Registred" << std::endl;
			std::cout << PURPLE << "====================================================================" << RESET << std::endl;
		}
	}
	else {
		// You can put your functions here
		// if you want to send a message to a client use : mySend("Your Message", it->first)
		// Notice : dont change the second parameter of mySend() ==> it->first
		if (!it->second.isRegistred || !it->second.isnickname || !it->second.isusername) {
			mySend(" * Error 461 : You need to be authenticated before using this command.\n", it->first);
			return ;
		}
		mySend(" * Success   : Canis Lupus part here.\n", it->first);
	}
}

void	Server::mySend(const char *msg, int clientSocket) {send(clientSocket, msg, std::strlen(msg), 0);}

void	Server::addClient(int clientSocket, std::string	client_ip)
{
	Client	client;
	Server::ServerClients.insert(std::make_pair(clientSocket, client));
	std::map<int, Client>::iterator it = findSocket(clientSocket);
	it->second.client_ip = client_ip;
}

std::map<int, Client>::iterator	Server::findSocket(int clientSocket)
{
	std::map<int, Client>::iterator	it = Server::ServerClients.begin();
	while (it != Server::ServerClients.end()) {
		if (it->first == clientSocket)
			break;
		else
			it++;
	}
	return (it);
}