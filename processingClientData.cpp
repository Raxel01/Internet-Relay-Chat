else {
						char buffer[1024] = {0};
						ssize_t	rcvlen = recv(sockets[i].fd, buffer, 1024, 0);
						if (rcvlen == 0) {
							std::cout << RED << " * Client " << PURPLE << sockets[i].fd << RESET << " has disconnected." << std::endl;
							// If client disconnects, delete everything related to that client.
							close(sockets[i].fd);
						}
						else {
							if (!std::strncmp(buffer, "PASS", 4) && std::strlen(buffer) > 4 && !clientDB[i].isRegistred) {
								clientDB[i].password = extractKey(buffer);
								if (clientDB[i].password != this->_password) {
									clientDB[i].password = "";
									send(clientDB[i].clientSocket, " * Error : wrong password.\n", 28, 0);
								}
								else {
									send(clientDB[i].clientSocket, " * Success : You have entered the correct password.\n", 53, 0);
									send(clientDB[i].clientSocket, " * Hint    : Enter a username now using (USER your_username).\n", 63, 0);
									clientDB[i].isRegistred = true;
								}
							}
							else if (!std::strncmp(buffer, "USER", 4) && std::strlen(buffer) > 4 && clientDB[i].isRegistred && !clientDB[i].isNickName) {
								clientDB[i].nickName = extractKey(buffer);
								send(clientDB[i].clientSocket, " * Success : You have set yourself a username.\n", 48, 0);
								send(clientDB[i].clientSocket, " * Hint    : Enter a nickname now using (NICK your_nickname).\n", 63, 0);
								clientDB[i].isNickName = true;
							}
							else if (!std::strncmp(buffer, "NICK", 4) && std::strlen(buffer) > 4 && clientDB[i].isRegistred && clientDB[i].isNickName && !clientDB[i].isUserName) {
								clientDB[i].userName = extractKey(buffer);
								send(clientDB[i].clientSocket, " * Success : You have set yourself a nickname.\n", 48, 0);
								send(clientDB[i].clientSocket, " * Succes  : You have successfuly registred on Benito's Server.\n", 65, 0);
								send(clientDB[i].clientSocket, " * Hint    : Use (HELP) for more commands.\n", 44, 0);
								clientDB[i].isUserName = true;
							}
							else if (!std::strcmp(buffer, "HELP\n") && clientDB[i].isRegistred && clientDB[i].isNickName && clientDB[i].isUserName) {
								mySend(" * KICK    - Ejects a client from the channel.\n", 0);
								mySend(" * INVITE  - Invites a client to a channel.\n", 0);
								mySend(" * TOPIC   - Changes or view the channel topic.\n", 0);
								mySend(" * JOIN    - Creates a channel if it doesn't exit or join an existing one.\n", 0);
								mySend(" * PRIVMSG - Sends a private message to a client or a channel.\n", 0);
								mySend(" * MODE    - Changes the channel's mode :\n", 0);
								mySend("\t1. +/- i: Sets/removes Invite-only channel.\n", 0);
								mySend("\t2. +/- t: Sets/removes the restrictions of the TOPIC command to channel operators.\n", 0);
								mySend("\t3. +/- k: Sets/removes the channel key (password).\n", 0);
								mySend("\t4. +/- k: Gives/takes channel operator privilege.\n", 0);
								mySend("\t5. +/- o: Gives/takes channel operator privilege.\n", 0);
								mySend("\t6. +/- l: Sets/removes the user limit to channel.\n", 0);
							}
							// Put your function here, and pass client by reference :D
							// Also, Check if user is registred by checking the 3 bools :
							// clientDB[i].isRegistred; clientDB[i].isNickName; clientDB[i].isUserName
							else if (std::strcmp(buffer, "\n") && !(clientDB[i].isRegistred || clientDB[i].isNickName || clientDB[i].isUserName))
								send(clientDB[i].clientSocket, " * Error   : Make sure you are registred before entering any command.\n", 71, 0);
							else {
								send(clientDB[i].clientSocket, " * Error   : Command not found.\n", 33, 0);
								std::cout << " * Buffer = " << buffer << std::endl;
							}
						}
					}