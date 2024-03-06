/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ta <abait-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 20:30:32 by abait-ta          #+#    #+#             */
/*   Updated: 2024/03/06 10:51:08 by abait-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include <deque>

// std::string ascii_art =
//     "\033[33;1m"
//     "                     ::::::::::: :::::::::   ::::::::              ::::::::  :::::::::: :::::::::  :::     ::: :::::::::: :::::::::  \n"
//     "                         :+:     :+:    :+: :+:    :+:            :+:    :+: :+:        :+:    :+: :+:     :+: :+:        :+:    :+: \n"
//     "                         +:+     +:+    +:+ +:+                   +:+        +:+        +:+    +:+ +:+     +:+ +:+        +:+    +:+ \n"
//     "                         +#+     +#++:++#:  +#+                   +#++:++#++ +#++:++#   +#++:++#:  +#+     +:+ +#++:++#   +#++:++#:  \n"
//     "                         +#+     +#+    +#+ +#+                          +#+ +#+        +#+    +#+  +#+   +#+  +#+        +#+    +#+ \n"
//     "                         #+#     #+#    #+# #+#    #+#            #+#    #+# #+#        #+#    #+#   #+#+#+#   #+#        #+#    #+# \n"
//     "                     ########### ###    ###  ########  ##########  ########  ########## ###    ###     ###     ########## ###    ### "
//     "\033[0m";

/******************************************************************/
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <sstream>
#include <list>
#include "ReforMessage.hpp"
#include "ChatRoom.hpp"


// #include "MessageRecognizer.cpp"

// const char *CMD[] ={ "KICK", "INVITE", "MODE", "TOPIC", "JOIN", "PART", "PONG", "UNKNOW", "IGNORE"};

// :adrift.sg.quakenet.org 421 OK LOL :Unknown command

//Container deque

//Message Grammar ==> |:Prefix cmd param_lis<...>|

std::map<int, Client> Server::ServerClients;
/******************************************************************/
Client::Client()
{
	this->isconnected = false;
	this->is_pass = false;
	this->isKeySet = false;
	this->isUsrnameSet = false;
}

Client::~Client()
{

}

Client::Client(const Client &client)
{
    this->nickname = client.nickname;
    this->username = client.username;
    this->isconnected = client.isconnected;
    this->is_pass = client.is_pass;
    this->isKeySet = client.isKeySet;
    this->isUsrnameSet = client.isUsrnameSet;
}

std::string Client::getNick()
{
	return this->nickname;
}

void Client::setNick(string nickname)
{
	this->nickname = nickname;
}

void Client::setUsername(std::string username){
	this->username = username;
}

std::string Client::getUserName() {
	return this->username;
}

std::string& Client::toLower(std::string &str){
	size_t i;

	i = -1;
	while ( ++i < str.size())
		str[i] = std::tolower(str[i]);
	return str;
}

 Client &Client::operator=(const Client &client)
 {
	 this->nickname = client.nickname;
	 this->username = client.username;
	 this->isconnected = client.isconnected;
	 this->is_pass = client.is_pass;
	 this->isKeySet = client.isKeySet;
	 this->isUsrnameSet = client.isUsrnameSet;
	 this->client_fd = client.client_fd;
	 this->client_ip = client.client_ip;
	 return *this;
}

bool check_port(std::string port)
{
    for (size_t i = 0; i < port.size(); i++)
    {
        if (!std::isdigit(port[i]))
            return false;
    }
    std::stringstream ss(port);
    int portNum;
    ss >> portNum;
    if (portNum < 1024 || portNum > 65535)
        return false;
    return true;
}

Server::Server() : port(5000)
{
    std::cout << "Server created" << std::endl;
    is_pass = false;
}

Server::Server(int port, std::string password) : port(port), password(password)
{
    std::cout << "Server created" << std::endl;
}

Server::~Server()
{
    std::cout << "Server destroyed" << std::endl;
}

void Server::create_server()
{
    struct sockaddr_in server_addr;
    struct pollfd fd;
    int opt = 1;
    std::memset(&fd, 0, sizeof(fd));
    std::memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0)
        throw std::runtime_error("socket error");
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)))
        throw std::runtime_error("setsockopt error");
    if (fcntl(server_fd, F_SETFL, O_NONBLOCK) < 0)
        throw std::runtime_error("fcntl error");
    if (bind(server_fd, reinterpret_cast<struct sockaddr *>(&server_addr), sizeof(server_addr)) < 0)
        throw std::runtime_error("bind error");
    if (listen(server_fd, SOMAXCONN) < 0)
        throw std::runtime_error("listen error");
    fd.fd = server_fd;
    fd.events = POLLIN | POLLHUP;
    pollfds.push_back(fd);
}

void Server::accept_connection()
{
    struct sockaddr_in client_addr;
    struct pollfd fd;
    socklen_t client_addr_len = sizeof(client_addr);
    std::memset(&fd, 0, sizeof(fd));
    // std::memset(&client_addr, 0, sizeof(client_addr));
    client_fd = accept(server_fd, reinterpret_cast<struct sockaddr *>(&client_addr), &client_addr_len);
    if (client_fd < 0)
        throw std::runtime_error("accept error");
    if (fcntl(client_fd, F_SETFL, O_NONBLOCK) < 0)
        throw std::runtime_error("fcntl error");
    fd.fd = client_fd;
    fd.events = POLLIN | POLLHUP;
    char *ip;
    ip = inet_ntoa(client_addr.sin_addr);
    pollfds.push_back(fd);
    Client client;
    this->ServerClients[client_fd] = client;
    this->ServerClients[client_fd].client_fd = client_fd;
    this->ServerClients[client_fd].client_ip = ip;
}

void Server::main_loop()
{
   // std::cout << ascii_art << std::endl;
    std::string asString;
    signal(SIGPIPE, SIG_IGN);
    try
    {
        create_server();
        while (1)
        {
            is_pass = false;
            if (poll(&pollfds[0], pollfds.size(), -1) < 0)
            {
                std::cerr << "Error: poll failed" << std::endl;
                exit(1);
            }
            for (size_t i = 0; i < pollfds.size();)
            {
                if (pollfds[i].revents & POLLIN)
                {
                    if (pollfds[i].fd == server_fd)
                    {
                        std::cout << "-----------------New connection-----------------" << std::endl;
                        accept_connection();
                        break;
                    }
                    else
                    {
                        // std::cout << "-----------------Reading-----------------" << std::endl;
                        char buffer[BUFFER_SIZE];
                        std::memset(buffer, 0, sizeof(buffer));
                        int bytes_read = recv(pollfds[i].fd, buffer, sizeof(buffer), 0);
                        
                        if (bytes_read < 0)
                        {
                            std::cerr << "Error: recv failed" << std::endl;
                            close(pollfds[i].fd);
                            pollfds.erase(pollfds.begin() + i);
                            continue;
                        }
                        else if (bytes_read == 0)
                        {
                            std::cerr << "Connection closed" << std::endl;
                            close(pollfds[i].fd);
                            ServerClients.erase(pollfds[i].fd);
                            pollfds.erase(pollfds.begin() + i);
                            break;
                        }
                        else
                        {
                            //authenticate
                            // std::cout << "*" << bytes_read << "*" << std::endl;
                            // buffer[bytes_read] = '\0';
                            // I will add the parsing of the commands here : ahmed
                            try
                            {
                                if(!this->ServerClients[pollfds[i].fd].isconnected)
                                this->authenticate(buffer, pollfds[i].fd);
                                else
                                {
                                    //Buffer
                                    // //
                                    asString = buffer;
                                    ReforMessage::GlobalReform(asString);
                                    std::cout << ReforMessage::FinalMessage << std::endl;
                                    MediatorCommand(ReforMessage::FinalMessage, pollfds[i].fd);  //   
                                    
                                    // std::vector<ChatRoom>::iterator iter = GlobalServerData::ServerChannels.begin();
                                    // std::cout << "_____________________________________________"<< std::endl;
                                    // while (iter != GlobalServerData::ServerChannels.end()){
                                    //     std::cout << (*iter).GetRoomname()<< std::endl;
                                    //     iter++;
                                    // }                
                                    // std::cout << "_____________________________________________"<< std::endl;
                                }
                            }
                            catch(const std::exception& e)
                            {
                                std::cerr << e.what() << '\n';
                            }
                            break;
                        }
                    }
                }
                else if (pollfds[i].revents & (POLLHUP | POLLERR | POLLNVAL))
                {
                    close(pollfds[i].fd);
                    ServerClients.erase(pollfds[i].fd);
                    pollfds.erase(pollfds.begin() + i);
                    continue;
                }
                i++;
            }
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}

std::string  Client::messageGenerator(std::string prefix, std::string command, std::string params,std::string trail)
{
	std::string message;
	message = ":" + prefix + " " + command + " " + params + " " + ":" + trail + "\r\n";
	return message;
}

bool Client::checkRegNick(std::string nickname)
{
	size_t i = 0;
	std::string allowed = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_-";
	if(nickname.size() > 9 || nickname.size() < 1)
		return false;
	if(nickname.at(0) >= '0' && nickname.at(0) <= '9')
		return false;
	while (i < nickname.size())
	{
		if(allowed.find(nickname.at(i)) == std::string::npos)
			return false;
		i++;
	}
	return true;
}

void Server::authenticate(std::string buffer,int fd)
{
    std::string cmd;
    std::string key;
    stringstream ss;
   int pos;

    
    this->ServerClients[fd].msg.append(buffer);

    if(this->ServerClients[fd].msg.find("\n") == std::string::npos)
        return;
    ss << this->ServerClients[fd].msg;
    this->ServerClients[fd].msg.clear();
    ss >> cmd;
    ss >> key;

    if (cmd == "PASS" && !this->ServerClients[fd].is_pass)
    {
        pos  = buffer.find("\r\n") != std::string::npos ? 2 : 1;
        key  = buffer.substr(buffer.find(key), buffer.size() - buffer.find(key) - pos);
        if (key != this->password)
        {
            std::string msg = Client::messageGenerator("ERROUR",ERR_PASSWDMISMATCH,"*" ,"invalid password");
            send(fd, msg.c_str(), msg.size(), 0);
            return;
        }
        this->ServerClients[fd].is_pass= true;
    }
    if (cmd == "NICK" && !this->ServerClients[fd].isKeySet)
    {

        if (!this->ServerClients[fd].checkRegNick(key))
        {
            std::string msg = Client::messageGenerator("ERROUR",ERR_NICKNAMEINUSE,"*" ,"invalid nickname");
            send(fd, msg.c_str(), msg.size(), 0);
            return;
        }
        map<int, Client>::iterator it = this->ServerClients.begin();
        while (it != this->ServerClients.end())
        {
            if (it->second.getNick() == key)
            {
                std::string msg = Client::messageGenerator("ERROUR",ERR_ERRONEUSNICKNAME,"*" ,"already in use");
                send(fd, msg.c_str(), msg.size(), 0);
                return;
            }
            it++;
        }
        this->ServerClients[fd].setNick(key);
        this->ServerClients[fd].isKeySet = true;
    }
    if (cmd == "USER" && !this->ServerClients[fd].isUsrnameSet)
    {
        if (!this->ServerClients[fd].checkRegNick(key))
        {
            std::string msg = Client::messageGenerator("ERROUR",ERR_INVALIDUSERNAME,"*" ,"already in use");
            send(fd, msg.c_str(), msg.size(), 0);
            return;
        }
        this->ServerClients[fd].setUsername(key);
        this->ServerClients[fd].isUsrnameSet = true;
    }
    if (this->ServerClients[fd].isUsrnameSet && this->ServerClients[fd].isKeySet && this->ServerClients[fd].is_pass)
    {
        std::cout << "connected susccessfully\n";
        this->ServerClients[fd].isconnected = true;
        std::string msg = Client::messageGenerator("localhost",RPL_WELCOME,this->ServerClients[fd].getNick() ,"authenticated successfully");
        send(fd, msg.c_str(), msg.size(), 0);
        msg = Client::messageGenerator("localhost",RPL_WELCOME,this->ServerClients[fd].getNick() ,"Welcome to the server " + this->ServerClients[fd].getNick());
        send(fd, msg.c_str(), msg.size(), 0);
    }
    return;
}

// #include "../inc/server.hpp"

int main(int ac, char **av)
{
    std::stringstream ss;
    int port;
    if (ac != 3)
    {
        std::cerr << "\033[31;1m Usage: ./IRC <port> <password> \033[0m" << std::endl;
       return 1; 
    }
    if (check_port(av[1]) == false)
    {
        std::cerr << "\033[31;1m Invalid Port Number \033[0m" << std::endl;
        return 1;
    }
    ss << av[1];
    ss >> port;
     Server server(port, av[2]);
    // Server server(atoi(av[1]), av[2]);
    server.main_loop();
    return 0;
}