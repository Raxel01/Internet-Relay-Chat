#include "../../headers/Server.hpp"
#include "../../headers/Commands.hpp" 

std::map<int, Client> Server::ServerClients;

Server::Server(std::string port, std::string password)
{
	this->_port = port;
	this->_password = password;
	this->_ipaddress = "";
}

int	Server::parseInput()
{
	// Parsing Port
	if (_port.length() > 5)
		return (error("port length should be either 4 or 5."), 1);
	for (size_t i = 0; i < _port.length(); i++)
		if (!std::isdigit(_port[i]))
			return (error("port should contain only digits."), 1);
	if (std::atoi(_port.c_str()) < 1024 || std::atoi(_port.c_str()) > 65565)
		return (error("port should be between 1024 and 65565."), 1);

	// Parsing Password
	if (_password.empty())
			return (error("password is empty."), 1);
	for (size_t i = 0; i < _password.length(); i++)
		if (_password[i] == ' ' || _password[i] == '\t')
			return (error("password should not contain whitespaces."), 1);

	return 0;
}

void	Server::start()
{
	signal(SIGPIPE, SIG_IGN);
	char 		hostbuffer[256];
	struct sockaddr_in	server_address;
	int			opt		= 1;
	bzero(&server_address, sizeof(sockaddr_in));

	server_address.sin_family		= AF_INET;
	server_address.sin_addr.s_addr	= INADDR_ANY;
	server_address.sin_port			= htons(std::atoi(_port.c_str()));

	// Get the hostname
    if (gethostname(hostbuffer, sizeof(hostbuffer)) == -1)
        error("failed to return host name of the current process.");

    // Function's name points to it's functionality :D
    struct hostent *host_entry;
    host_entry = gethostbyname(hostbuffer);
    if (host_entry == NULL)
        error("could not get host by name.");

    // Convert IPv4 address from binary to text form
    Server::_ipaddress = inet_ntoa(*((struct in_addr *)host_entry->h_addr_list[0]));

	// Create a socket node for the server
	int	serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (serverSocket == -1)
		error("socket function couldn't create an endpoint for communication.");

	// Set socket opt so we can re-use it in case of abort
	if (setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1)
		error("socket was unable to reuse the ip address.");

	// Bind the socket to ip adress and port number
	if (bind(serverSocket, (sockaddr *)&server_address, sizeof(server_address)) == -1)
		error("socket was unable to bind to ip adress and port number.");

	// Set socket to non-blocking mode
	if (fcntl(serverSocket, F_SETFL, O_NONBLOCK) == -1)
		error("failed to set the socket to non-blocking mode.");

	// Listen to incoming connections
	if (listen(serverSocket, 128) == -1)
		error("socket could not listen to incoming connections.");

	std::cout << GREEN << " * Server started, listening on port " << PURPLE << _port << GREEN << " for any incoming connections." << RESET << std::endl;

	// Polling and other stuff
	std::vector<pollfd>	sockets;
	sockaddr_in			client_address;
	socklen_t			client_address_len = sizeof(client_address);
	char				*client_ip;
	int					clientSocket;
	size_t				i = 0;

	sockets.push_back((pollfd){.fd = serverSocket, .events = POLLIN, .revents = 0});
	std::map<int, Client>::iterator	it;
	while (true) {
		try {
			if (poll(sockets.begin().base(), sockets.size(), 0) == -1)
				exit (1);
			i = 0;
			while (i < sockets.size()) {
				if (POLLIN & sockets[i].revents) {
					if (sockets[i].fd == serverSocket) {
						bzero(&client_address, sizeof(sockaddr_in));
						clientSocket = accept(serverSocket, (sockaddr *)&client_address, &client_address_len);
						sockets.push_back((pollfd){.fd = clientSocket, .events = POLLIN, .revents = 0});
						i = sockets.size() - 1;
						client_ip = inet_ntoa(client_address.sin_addr);
						std::string	ip_str(client_ip);
						addClient(sockets[i].fd, ip_str);
						it = findSocket(sockets[i].fd);
						std::cout << GREEN << " * Client " << PURPLE << it->second.client_ip << RESET << " connected successfuly." << std::endl;
					}
					else {
						char buffer[1024] = {0};
						ssize_t	rcvlen = recv(sockets[i].fd, buffer, 1024, 0);
						// Max line length (Limechat policy)
						if (rcvlen > 512) {
							it = findSocket(sockets[i].fd);
							std::string format;
							format = ":" + it->second.client_ip + " 417 " + " " + tostring(it->first) + " :Line too long\r\n";
							mySend(format.c_str(), it->first);
						}
						// In case recv() fails, delete client socket from everywhere
						// Or QUIT command entered by client
						else if (rcvlen <= 0 || strncmp(buffer, "QUIT", 4) == 0) {//ADD : may add if the buffer = to "QUIT" in first Field
							it = findSocket(sockets[i].fd);
							std::cout << RED << " * Client " << PURPLE << it->second.client_ip << RESET << " has disconnected." << std::endl;
							std::vector<pollfd>::iterator it_;
							for (it_ = sockets.begin(); it_ != sockets.end(); it_++) {
								if (it_->fd == sockets[i].fd)
									break ;
							}
							QUITmessage(sockets[i].fd);// Function added Here;
							close(sockets[i].fd);
							sockets.erase(it_);
							Server::ServerClients.erase(it->first);
							break;
						}
						// If everything goes as planned
						else {
							it = findSocket(sockets[i].fd);
							int	flag = 0;
							// Handling CTRL + D in the middle of a cmd
							for (size_t i = 0; i < std::strlen(buffer); i++) {
								if (buffer[i] == '\n') {
									flag++;
									break;
								}
							}
							it->second.buffer_str.append(buffer);
							if (flag == 1) {
								processClientData(it->second.buffer_str, it);
								it->second.buffer_str.clear();
							}
							else {
								if (it->second.buffer_str != "") {
									it->second.buffer_str.erase(it->second.buffer_str.length());
								}
								if (it->second.buffer_str.find('\n') != std::string::npos) {
									processClientData(it->second.buffer_str, it);
									it->second.buffer_str.clear();
								}
							}
						}
					}
				}
				i++;
			}
		}
		catch (std::exception &e) {
			error(e.what());
		}
	}
}

void	Server::processClientData(std::string buffer, std::map<int, Client>::iterator &it)
{
	std::string	password;
	std::string	nickname;
	std::string	username;
	std::string	format;
	std::string asString;

	if (!std::strncmp(buffer.c_str(), "PASS ", 5) || !std::strncmp(buffer.c_str(), "PASS\t", 5)) {
		if (it->second.isRegistred) {
			format = ":" + it->second.client_ip + " 462 " + " " + tostring(it->first) + " :You are already registred\r\n";
			mySend(format.c_str(), it->first);
			return ;
		}
		if (std::strlen(buffer.c_str()) == 4 || std::strlen(buffer.c_str()) == 5) {
			format = ":" + it->second.client_ip + " 461 " + " " + tostring(it->first) + " :Missing password\r\n";
			mySend(format.c_str(), it->first);
			return ;
		}
		password = extractKey(buffer.c_str());
		if (password != _password) {
			format = ":" + it->second.client_ip + " 464 " + " " + tostring(it->first) + " :Incorrect password\r\n";
			mySend(format.c_str(), it->first);
			return ;
		}
		if (password == _password) {
			it->second.isRegistred = true;
		}
	}
	else if (!std::strncmp(buffer.c_str(), "NICK ", 5) || !std::strncmp(buffer.c_str(), "NICK\t", 5)) {
		if (!it->second.isRegistred) {
			format = ":" + it->second.client_ip + " 451 " + " " + tostring(it->first) + " :You need to enter the server's password first\r\n";
			mySend(format.c_str(), it->first);
			return ;
		}
		if (it->second.isnickname) {
			format = ":" + it->second.client_ip + " 462 " + " " + tostring(it->first) + " :You already have a nickname\r\n";
			mySend(format.c_str(), it->first);
			return ;
		}
		if (std::strlen(buffer.c_str()) == 4 || std::strlen(buffer.c_str()) == 5) {
			format = ":" + it->second.client_ip + " 431 " + " " + tostring(it->first) + " :Missing nickname\r\n";
			mySend(format.c_str(), it->first);
			return ;
		}
		nickname = extractKey(buffer.c_str());
		if (nickname.length() > 9) {
			format = ":" + it->second.client_ip + " 432 " + " " + tostring(it->first) + " :Nickname length must be less or equal to 9 characters\r\n";
			mySend(format.c_str(), it->first);
			return ;
		}
		if (nickname[0] == '&' || nickname[0] == '#' || nickname[0] == ':' || nickname[0] == '@' || std::isdigit(nickname[0])) {
			format = ":" + it->second.client_ip + " 432 " + " " + tostring(it->first) + " :Nickname musn't contain '#' or '&' or ':' as trailing characters\r\n";
			mySend(format.c_str(), it->first);
			return ;
		}
		for (size_t i = 0; i < nickname.size(); i++) {
			if (nickname[i] == ' ' || nickname[i] == '\t') {
				format = ":" + it->second.client_ip + " 432 " + " " + tostring(it->first) + " :Nickname musn't contain whitespaces\r\n";
				mySend(format.c_str(), it->first);
				return ;
			}
		}
		for (std::map<int, Client>::iterator it_ = Server::ServerClients.begin(); it_ != Server::ServerClients.end(); it_++) {
			if (nickname == it_->second.nickname) {
				format = ":" + it->second.client_ip + " 433 " + " " + tostring(it->first) + " :Someone in the server is already using that nickname\r\n";
				mySend(format.c_str(), it->first);
				return ;
			}
		}
		it->second.nickname = nickname;
		it->second.isnickname = true;
	}
	else if (!std::strncmp(buffer.c_str(), "USER ", 5) || !std::strncmp(buffer.c_str(), "USER\t", 5)) {
		if (!it->second.isRegistred) {
			format = ":" + it->second.client_ip + " 451 " + " " + tostring(it->first) + " :You need to enter the server's password first\r\n";
			mySend(format.c_str(), it->first);
			return ;
		}
		if (!it->second.isnickname) {
			format = ":" + it->second.client_ip + " 451 " + " " + tostring(it->first) + " :You need to set yourself a nickname first\r\n";
			mySend(format.c_str(), it->first);
			return ;
		}
		if (it->second.isusername) {
			format = ":" + it->second.client_ip + " 462 " + " " + tostring(it->first) + " :You already have a username\r\n";
			mySend(format.c_str(), it->first);
			return ;
		}
		bool status = false;
		int	i = 0;
		int	words_count = 0;
		while (buffer[i]) {
			if (buffer[i] == ' ' || buffer[i] == '\t')
				status = true;
			else if (status) {
				status = false;
				words_count++;
			}
			i++;
		}
		size_t j = 0;
		i = buffer.length() - 1;
		std::string	rev_username;
		if (words_count == 4) {
			// Put this chunk of code in a separate function
			while (i > 0 && buffer[i] != ' ' && buffer[i] != '\t') {
				rev_username.resize(j + 1);
				rev_username[j] = buffer.c_str()[i];
				j++;
				i--;
			}
			j = 0;
			i = rev_username.length() - 1;
			while (i > 0) {
				username.resize(j + 1);
				username[j] = rev_username[i];
				j++;
				i--;
			}
			if (username.empty()) {
				format = ":" + it->second.client_ip + " 431 " + " " + tostring(it->first) + " :Missing username\r\n";
				mySend(format.c_str(), it->first);
				return ;
			}
			size_t n_pos = username.find('\n');
			if (n_pos != std::string::npos)
				username.resize(n_pos);
			size_t r_pos = username.find('\r');
			if (r_pos != std::string::npos)
				username.resize(r_pos);
			for (std::map<int, Client>::iterator it_ = Server::ServerClients.begin(); it_ != Server::ServerClients.end(); it_++) {
				if (username == it_->second.username) {
					format = ":" + it->second.client_ip + " 433 " + " " + tostring(it->first) + " :Someone in the server is already using that username\r\n";
					mySend(format.c_str(), it->first);
					return ;
				}
			}
			it->second.username = username;
			it->second.isusername = true; // Welcome message
			format = RPL_WELCOME(it->second.nickname, it->second.client_ip);
			mySend(format.c_str(), it->first);
			format = RPL_YOURHOST(it->second.nickname, it->second.client_ip);
			mySend(format.c_str(), it->first);
			format = RPL_CREATED(it->second.nickname, it->second.client_ip);
			mySend(format.c_str(), it->first);
			format = RPL_MYINFO(it->second.nickname, it->second.client_ip);
			mySend(format.c_str(), it->first);
		}
		else {
			format = ":" + it->second.client_ip + " 461 " + " " + tostring(it->first) + " :Missing or too many arguments\r\n";
			mySend(format.c_str(), it->first);
			return ;
		}
	}
	else if (!std::strncmp(buffer.c_str(), "HELP", 4)) {
		if (!it->second.isRegistred || !it->second.isnickname || !it->second.isusername) {
			format = ":" + it->second.client_ip + " 451 " + " " + tostring(it->first) + " :You need to be authenticated before using this command\r\n";
			mySend(format.c_str(), it->first);
			return ;
		}
		format = ":" + it->second.client_ip + " 005 " + " " + tostring(it->first) + " :* KICK    - Ejects a client from the channel.\r\n";
		mySend(format.c_str(), it->first);
		format = ":" + it->second.client_ip + " 005 " + " " + tostring(it->first) + " :* INVITE  - Invites a client to a channel.\r\n";
		mySend(format.c_str(), it->first);
		format = ":" + it->second.client_ip + " 005 " + " " + tostring(it->first) + " :* TOPIC   - Changes or view the channel topic.\r\n";
		mySend(format.c_str(), it->first);
		format = ":" + it->second.client_ip + " 005 " + " " + tostring(it->first) + " :* JOIN    - Creates a channel if it doesn't exit or join an existing one.\r\n";
		mySend(format.c_str(), it->first);
		format = ":" + it->second.client_ip + " 005 " + " " + tostring(it->first) + " :* PRIVMSG - Sends a private message to a client or a channel.\r\n";
		mySend(format.c_str(), it->first);
		format = ":" + Server::_ipaddress + " 005 " + " " + tostring(it->first) + " :* BOT     - Interacts with a silly bot.\r\n";
		mySend(format.c_str(), it->first);
		format = ":" + it->second.client_ip + " 005 " + " " + tostring(it->first) + " :\t1. fact : tells you a random fact that you probably didn't know.\r\n";
		mySend(format.c_str(), it->first);
		format = ":" + it->second.client_ip + " 005 " + " " + tostring(it->first) + " :\t2. weather : tells you today's weather.\r\n";
		mySend(format.c_str(), it->first);
		format = ":" + it->second.client_ip + " 005 " + " " + tostring(it->first) + " :* MODE    - Changes the channel's mode :\r\n";
		mySend(format.c_str(), it->first);
		format = ":" + it->second.client_ip + " 005 " + " " + tostring(it->first) + " :\t1. +/- i: Sets/removes Invite-only channel.\r\n";
		mySend(format.c_str(), it->first);
		format = ":" + it->second.client_ip + " 005 " + " " + tostring(it->first) + " :\t2. +/- t: Sets/removes the restrictions of the TOPIC command to channel operators.\r\n";
		mySend(format.c_str(), it->first);
		format = ":" + it->second.client_ip + " 005 " + " " + tostring(it->first) + " :\t3. +/- k: Sets/removes the channel key (password).\r\n";
		mySend(format.c_str(), it->first);
		format = ":" + it->second.client_ip + " 005 " + " " + tostring(it->first) + " :\t4. +/- k: Gives/takes channel operator privilege.\r\n";
		mySend(format.c_str(), it->first);
		format = ":" + it->second.client_ip + " 005 " + " " + tostring(it->first) + " :\t5. +/- o: Gives/takes channel operator privilege.\r\n";
		mySend(format.c_str(), it->first);
		format = ":" + it->second.client_ip + " 005 " + " " + tostring(it->first) + " :\t6. +/- l: Sets/removes the user limit to channel.\r\n";
		mySend(format.c_str(), it->first);
	}
	else if (!std::strncmp(buffer.c_str(), "BOT ", 4)) {
		if (!it->second.isRegistred || !it->second.isnickname || !it->second.isusername) {
			format = ":" + Server::_ipaddress + " 461 " + " " + tostring(it->first) + " :You need to be authenticated before using this command\r\n";
			mySend(format.c_str(), it->first);
			return ;
		}
		Bot	emmet(it->first, buffer.c_str(), it->second.client_ip);
	}
	else {
		if (!it->second.isRegistred || !it->second.isnickname || !it->second.isusername) {
			format = ":" + it->second.client_ip + " 451 " + " " + tostring(it->first) + " :You need to be authenticated before using this command\r\n";
			mySend(format.c_str(), it->first);
			return ;
		}
		asString = buffer;
        ReforMessage::GlobalReform(asString);
        MediatorCommand(ReforMessage::FinalMessage, it->first);
	}
}

void	Server::mySend(const char *msg, int clientSocket) { send(clientSocket, msg, strlen(msg), 0); }

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
