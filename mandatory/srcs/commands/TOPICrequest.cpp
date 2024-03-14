/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TOPICrequest.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ta <abait-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 04:35:20 by abait-ta          #+#    #+#             */
/*   Updated: 2024/03/13 20:46:14 by abait-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/Commands.hpp"

// Pay Attention You should Change a lot of things in the Code
void            TOPICprocessor(size_t &OccurSpace, std::string& channelName ,std::string& clientMsg, int __fd, std::string& NEWTOPIC)
{
    Roomiter    RoomObj;
    std::string response;
    static_cast<void> (clientMsg);
    
    RoomObj = FindUsingName(channelName);
    try
    {
        if (RoomObj != GlobalServerData::ServerChannels.end()) // check if there is a channelwith this Name
        { if((*RoomObj).IsalreadyMember(Server::ServerClients.at(__fd).nickname) == true){ //Requester is a Member
                if(OccurSpace == 1) //Just Get channel Topic
                {
                    if ((*RoomObj)._ChatTopic.size() != 0) { // So Topic is set get it 
                        response = NumericReplies(MYhost::GetHost(), "332", Server::ServerClients.at(__fd).nickname, (*RoomObj)._RoomName , (*RoomObj).getTOPIC()); // Send Topic to user;
                            send(__fd, response.c_str(), response.length(), 0);
                    }
                    else{ // No topic is seet
                        response = NumericReplies(MYhost::GetHost(), "331", Server::ServerClients.at(__fd).nickname, (*RoomObj)._RoomName, ":No Topic is set");
                            send(__fd, response.c_str(), response.length(), 0);
                    }
                }
                else//Try to set the [setTOPIC to this CHANNEL]
                {
                    if (((*RoomObj).TopicRestriction == true && (*RoomObj).IsMediator(Server::ServerClients.at(__fd).nickname) ) || (*RoomObj).TopicRestriction == false) // Change by user name
                    {
                        (*RoomObj).SetTOPIC(NEWTOPIC);
                        response = ":" + Server::ServerClients.at(__fd).nickname + "!~" + Server::ServerClients.at(__fd).username + "@" +Server::ServerClients.at(__fd).client_ip +  " TOPIC " + (*RoomObj)._RoomName + " " +(*RoomObj)._ChatTopic + "\n";
                        BroadcastMessage("", "", RoomObj, response);
                    }
                    else{
                        std::string response (NumericReplies(MYhost::GetHost(), "482", Server::ServerClients.at(__fd).nickname, (*RoomObj)._RoomName, "You are not CHANNEL CHANOP"));
                            send(__fd, response.c_str(), response.length(), 0);
                    } //TryToset the channelTopic . . .
                } 
            } else{
                response = NumericReplies(MYhost::GetHost(), "442", Server::ServerClients.at(__fd).nickname, (*RoomObj)._RoomName, "You are not on this channel");
                throw EX_NOTONCHANNEL();
            }
        } else {   
            response = NumericReplies(MYhost::GetHost(), "403", Server::ServerClients.at(__fd).nickname, channelName, "No such channel");
                throw Ex_NOSUCHCHANNEL();
            }
    }
    catch(std::exception& e)
    {send(__fd, response.c_str(), response.length(), 0);
        response.clear();
            e.what();
    }
}

void    TOPICmessage(std::string& clientMsg, int __fd)
{
    size_t OccurSpace = std::count(clientMsg.begin(), clientMsg.end(), ' ');
    
    if (OccurSpace == 0 || clientMsg.compare("TOPIC :") == 0){
        std::string response = ":" + MYhost::GetHost() + " 461 " + Server::ServerClients.at(__fd).nickname + " TOPIC " + ": NO ENOUGH PARAMETERS" + "\n" +
            NumericReplies(MYhost::GetHost(), "999", Server::ServerClients.at(__fd).nickname, "TOPIC", "<channel> +/- [<TOPIC_TO_SET>]");
                send(__fd, response.c_str(), response.length(), 0);
    }
    else{
        
        std::stringstream stream(clientMsg);
        std::string       component;
        std::string       channelName;
        std::string       TOPIc;
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
                channelName = component;
                break;
            default:
                TOPIc += component + " ";
                break;
            }
        index++;
        }
        TOPICprocessor(OccurSpace, channelName ,clientMsg, __fd, TOPIc);
    }
}