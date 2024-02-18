/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChatRoom.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ta <abait-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 17:33:50 by abait-ta          #+#    #+#             */
/*   Updated: 2024/02/18 20:44:39 by abait-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <map>
#include <fstream>
#include <sstream>

typedef std::map<std::string, std::string> Bref;

class Chatroom
{
        static Bref ChannelDatabase;
        static Bref StoreJoinRequest;
    public :
        static void    fullMap();
        static void    ProcessCmd(std::string& command);
        static void    ComBinePasswordTochannel(std::string& channeLine, std::string& passwordLine);
        static void    Channelmatcher();
        static void    ShowJoinrequest();   
};

Bref Chatroom::StoreJoinRequest;

void    Chatroom::ShowJoinrequest()
{
    Bref::iterator it = StoreJoinRequest.begin();
    while (it != StoreJoinRequest.end()){
        std::cout << "channel : " << it->first << " it Password : " << it->second << std::endl;
        it++;
    }
}

void    Chatroom::ComBinePasswordTochannel(std::string& channeLine, std::string& passwordLine)
{
    std::string getchannel;
    std::string getpass;
    
    std::stringstream channelstream(channeLine);
    std::stringstream passtream(passwordLine);
    
    while (std::getline(channelstream,getchannel,  ',') && std::getline(passtream,getpass, ',')){
        StoreJoinRequest.insert(std::pair<std::string, std::string>(getchannel, getpass));
    }
    
}

Bref Chatroom::ChannelDatabase;

void    Chatroom::fullMap()
{
    ChannelDatabase.insert(std::pair<std::string, std::string>("#roomphilo",   "philo2016"));
    ChannelDatabase.insert(std::pair<std::string, std::string>("#roomGame",    "Game2016"));
    ChannelDatabase.insert(std::pair<std::string, std::string>("#roompSex",    "sex2016"));
    ChannelDatabase.insert(std::pair<std::string, std::string>("#roomtalk",    "talk2016"));
    ChannelDatabase.insert(std::pair<std::string, std::string>("#roomguitar",  "guitar2016"));
    ChannelDatabase.insert(std::pair<std::string, std::string>("#roomFotbal",  "fotball2016"));
    ChannelDatabase.insert(std::pair<std::string, std::string>("#roombillard", "Billard2016"));
    ChannelDatabase.insert(std::pair<std::string, std::string>("#roomWomenhh", "Womenhh2016"));
}

void    Chatroom::Channelmatcher(){
    // Bref::iterator baseIt = ChannelDatabase.begin();
    Bref::iterator Joinit;
    Bref::iterator Finder;
    
    Joinit = StoreJoinRequest.begin();
    while (Joinit != StoreJoinRequest.end()){
        
        Finder = ChannelDatabase.find(Joinit->first);
        if (Finder != ChannelDatabase.end())
        {
            if ( Finder->second.compare(Joinit->second) == 0)
            {
                std::cout << "Name an password Match"<< std::endl;
                std::cout << "Welcome Member and Fuck You "<< std::endl;
            }
            else
                std::cout << "Channel Name Match but Password No "<< std::endl;
                
        }
        else
            std::cout << " Don't Matches " << std::endl;
        
        Joinit++;
    }

}

/* COOMMmMmmMmMMMMME BACK TO HEREEEEEEE */
void    Chatroom::ProcessCmd(std::string& command)
{
        std::string CatchLine;
        std::stringstream ss(command);
        size_t e = 0;
        std::string channelsGroup;
        std::string Passwordschaine;
        
        while(ss >> CatchLine){
            
            if (e == 3)
                break;
            e++;
            if (e == 2)
                channelsGroup = CatchLine;
            if (e == 3)
                Passwordschaine = CatchLine;
        }
        ComBinePasswordTochannel(channelsGroup, Passwordschaine);
        Channelmatcher();
        // ShowJoinrequest();
}

int main ()
{

    std::string command;
    Chatroom::fullMap();
    
    while(1){
        if(!std::getline(std::cin,command))
            break;
        Chatroom::ProcessCmd(command);
    }
    return 0;
}