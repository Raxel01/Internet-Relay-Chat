#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <fcntl.h>
#include <poll.h>
#include <vector>
#include <fstream>
#include <sstream>
#include <map>
#include <signal.h>
#include <dirent.h>
#include <sys/socket.h>
#include <algorithm>
#include <string>
#include "IrcReplies.hpp"

#define BUFFER_SIZE 512


using namespace std;
// Client::client_fd

class Client 
{
    public:
        string nickname;
        string username;
    public:
        char *client_ip;
        int client_fd;
        std::string msg;
        bool is_pass;
        bool isKeySet;
        bool isUsrnameSet;
        bool isconnected;
        std::string&  toLower(std::string &str);
        std::string getNick();
        void setNick(std::string nickname);
        void setUsername(std::string username);
        std::string getUserName();
        static std::string messageGenerator(std::string prefix, std::string command, std::string params,std::string trail);
        bool checkRegNick(std::string nickname);
        // void join(std::string buffer,std::map<std::string,Channel> &channels);
        // void priveMessage(std::string buffer,std::map<std::string, Channel> &channels, std::map<int, Client> &ServerClients);
        // static std::string  messageGenerator(std::string prefix, std::string command, std::string params,std::string trail);
        // bool checkChanReg(std::string channel);
        Client();
        Client(const Client &client);
        ~Client();
        void setNickname(string nickname);
        string getNickname();
        string getUsername();
         Client &operator=(const Client &client);
};

class Server 
{
    public:
    int port;
    std::string password;
    int server_fd;
    int client_fd;
    std::string msg;
    public:
    bool is_pass;
    Server();
    Server(int port, std::string password);
    ~Server();
    void main_loop();
    void create_server();
    void accept_connection();
    std::vector<struct pollfd> pollfds;
    std::map<int, Client> ServerClients;
    // hfjghjkhdfjk;hdf()
    // std::map<std::stringChannel> channels;
    void authenticate(std::string buffer, int fd);
};

bool check_port(std::string port);

#endif

