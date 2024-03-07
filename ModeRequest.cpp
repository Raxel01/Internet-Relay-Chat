/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ModeRequest.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ta <abait-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 17:34:44 by abait-ta          #+#    #+#             */
/*   Updated: 2024/03/07 22:23:07 by abait-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ModeRequest.hpp"
#include "JoinRequest.hpp"
#include "MessageRecognizer.hpp"
#include "GlobalException.hpp"
#include "KickRequest.hpp"

void    ModeProcessor(size_t& OccurSpace, int __fd, std::string& CHANNEL, std::string& ModeArgument, \
        short requiredArgs, std::string& UnknowFlags, std::string& CleanMode, enum MODETYPE CMODETYPE){
        
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
        //Stop Here 10:23
        if (OccurSpace == 1)//Getthe channel mode when [MODE #channel] is seet
            (*RoomObj).ChannelMode(__fd);
        else{
            if ((*RoomObj).IsMediator(Server::ServerClients.at(__fd).nickname))
            {
                
            }
            else
            {
                response = NumericReplies(MYhost::GetHost(), "482", Server::ServerClients.at(__fd).nickname, CHANNEL, "You are not CHANNEL CHANOP");
                    throw Ex_CHANOPRIVSNEEDED();
            }
            std::cout << "Go To set add or remove mode"<< std::endl;
        }
        //Stoped Here/***** * *****/
        
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
    @:  Here is Le3jinna 
*/

void      DataCleaner(short& requiredArgs, std::string& MODE, std::string& UnknowFlags, std::string& CleanMode, enum MODETYPE& CMODETYPE)
{
    short i = -1;
    char  c ;
    std::string Already;
    
    if (MODE[0] == '+' || MODE[0] == '-') // Get The modestring 
    {
        CMODETYPE = (MODE[0] == '+') ? ADD_MODE : REMOVE_MODE;
        i++;
    }
    while (MODE[++i])
    {
        c = MODE[i];
        if (c == 'k' || c == 'l' || c == 'o') {
            if (Already.find(c) == std::string::npos){
                Already.push_back(c);
                requiredArgs++;
            }
        }
        if (validFlags(c) == false && UnknowFlags.find(c) == std::string::npos)
            UnknowFlags.push_back(c);
        if (validFlags(c) == true && CleanMode.find(c) == std::string::npos)
            CleanMode.push_back(c);
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
        /* Tooon of Variables **************/
        std::stringstream stream(clientMsg);
        std::string       component;
        std::string       CHANNEL;
        std::string       MODE;
        std::string       ModeArgument;
        short             requiredArgs (0);
        std::string       UnknowFlags;
        std::string       CleanMode;
        enum              MODETYPE CMODETYPE = ERROR_MODE;
        short index = 0;
        /***************************************************/
        
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
        DataCleaner(requiredArgs, MODE, \
        UnknowFlags, CleanMode, CMODETYPE);
        
        /*Hooolyshiiiiiiit*/
        
        ModeProcessor(OccurSpace, __fd, CHANNEL, ModeArgument,\
               requiredArgs, UnknowFlags, CleanMode, CMODETYPE);
    }
}