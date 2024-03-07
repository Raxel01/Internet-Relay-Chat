/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ModeRequest.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ta <abait-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 17:34:44 by abait-ta          #+#    #+#             */
/*   Updated: 2024/03/07 12:25:38 by abait-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ModeRequest.hpp"
#include "JoinRequest.hpp"
#include "MessageRecognizer.hpp"
#include "GlobalException.hpp"
#include "KickRequest.hpp"

void    ModeProcessor(std::string &clientMsg, int __fd, std::string& CHANNEL, std::string& MODE, std::string& ModeArgument){
        
    Roomiter    RoomObj;
    std::string response;
    
    RoomObj = FindUsingName( CHANNEL );
    try{
         if (RoomObj == GlobalServerData::ServerChannels.end()){
            response = NumericReplies(MYhost::GetHost(), "403", Server::ServerClients.at(__fd).nickname, CHANNEL, "No such channel");
                throw Ex_NOSUCHCHANNEL();
        }
        if ((*RoomObj).IsalreadyMember(Server::ServerClients.at(__fd).nickname) == false){// check if the command writer is a member on this channel first
            response = NumericReplies(MYhost::GetHost(), "442", Server::ServerClients.at(__fd).nickname, CHANNEL, "You are not on this channel");
                throw EX_NOTONCHANNEL();
        }
        //Stoped Here
        
    }
    catch (std::exception& e)
    { send(__fd, response.c_str(), response.length(), 0);
         response.clear();
            e.what();
    }
}

bool validFlags(char c){
    return (c == 'o' || c == 'l' || c == 'k' || c == 'i' || c == 't');
}
/*
    @ : Extract Unknow flags in MODE string 
*/

void      GetRequiredArgs(short& requiredArgs  , std::string& MODE, std::string& UnknowFlags)
{
    short i = -1;
    char  c ;
    if (MODE[0] == '+' || MODE[0] == '-')
        i++;
    while (MODE[++i])
    {
        c = MODE[i];
        if (c == 'k' || c == 'l' || c == 'o')
            requiredArgs++;
        if (validFlags(c) == false && UnknowFlags.find(c) == std::string::npos)
            UnknowFlags.push_back(c);
    }
}

void    ModeMessage(std::string& clientMsg, int __fd)
{
    size_t OccurSpace = std::count(clientMsg.begin(), clientMsg.end(), ' ');
    
    if (OccurSpace == 0){
        std::string response = ":" + MYhost::GetHost() + " 461 " + Server::ServerClients.at(__fd).nickname + " MODE " + ": NO ENOUGH PARAMETERS" + "\n" +
            NumericReplies(MYhost::GetHost(), "999", Server::ServerClients.at(__fd).nickname, "MODE", "<CHANNEL> + [+/-]{i|o|t|k|l}");
                send(__fd, response.c_str(), response.length(), 0);
    }
    else
    {
        std::stringstream stream(clientMsg);
        std::string       component;
        std::string       CHANNEL;
        std::string       MODE;
        std::string       ModeArgument;
        short            requiredArgs (0);
        std::string      UnknowFlags;
        
        
        short index;
        index = 0;
        
        while (std::getline(stream, component, ' '))
        {
            switch (index)
            {
            case 0:
                component.clear();
                break;
            case 1:
                CHANNEL = component;
                component.clear();
                break;
            case 2:
                MODE = component;
                component.clear();
                break;
            default:
                ModeArgument += component + ",";
                break;
            }
        index++;
        }
        GetRequiredArgs(requiredArgs, MODE, UnknowFlags);
        
        // ModeProcessor(clientMsg, __fd, CHANNEL, MODE, ModeArgument);
        std::cout << "****************************************"<< std::endl;
        std::cout << "* CHANNEL      : |" << CHANNEL      <<"*" << std::endl;
        std::cout << "* MODE         : |" << MODE         <<"*" << std::endl;
        std::cout << "* MODE ARGS    : |" << ModeArgument <<"*" << std::endl;
        std::cout << "* Required ARGS: |" << requiredArgs <<"*" << std::endl;
        std::cout << "* unknowFlags  : |" << UnknowFlags  <<"*" <<std::endl;
        std::cout << "****************************************"<< std::endl;
    }
    
}