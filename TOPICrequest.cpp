/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TOPICrequest.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ta <abait-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 04:35:20 by abait-ta          #+#    #+#             */
/*   Updated: 2024/03/03 06:34:59 by abait-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "TOPICrequest.hpp"
#include "JoinRequest.hpp"
#include "MessageRecognizer.hpp"
#include "GlobalException.hpp"
#include "ChatRoom.hpp"

void            TOPICprocessor(size_t &OccurSpace, std::string& channelName ,std::string& clientMsg, int __fd, std::string& NEWTOPIC)
{
    Roomiter    RoomObj;
    std::string response;
    std::string owner("abdelali");
    
    // Pay Attention You should Change a lot of things in the Code
    RoomObj = FindUsingName(channelName);
    try
    {
        // (*RoomObj)._ChatTopic = "TOPIN HIYA L*** ASSAT"; //
        if (RoomObj != GlobalServerData::ServerChannels.end())
        {
            if((*RoomObj).IsalreadyMember(owner)){//change it;
                if(OccurSpace == 1) //Just Get channel Topic
                {// <-  :testnet.ergo.chat 331 oktal #toran :No topic is set
                    if ((*RoomObj)._ChatTopic.size() != 0)
                    {
                        std::cout << "Olaala" << std::endl;
                    response = NumericReplies(MYhost::GetHost(), "332", "USERNICKNAME", channelName , (*RoomObj).getTOPIC()); // Send Topic to user;
                        send(__fd, response.c_str(), response.length(), 0);
                            // <-  :testnet.ergo.chat 332 fort #BOLAS KolchiLeft
                    }
                    else{ // No topic is seet
                    // std::cout << " Seirr T9eweeeeed "<< std::endl;
                        response = NumericReplies(MYhost::GetHost(), "331", "USERNICKNAME", channelName, ":No Topic is set");
                        std::cout << __fd << std::endl;
                            ssize_t a = send(__fd, response.c_str(), response.length(), 0);
                            std::cout << "Send Status " << a << std::endl;
                    }
                }
                else//Try to set the [setTOPIC to this CHANNEL]
                {
                    if ((*RoomObj).TopicRestriction == true && (*RoomObj).IsMediator(owner) || (*RoomObj).TopicRestriction == false) // Change by user name
                    {
                        (*RoomObj).SetTOPIC(NEWTOPIC);
                        std::cout << " Yes Here Brooo "<< std::endl;
                        send(__fd, (*RoomObj)._ChatTopic.c_str(), (*RoomObj)._ChatTopic.length(), 0);
                        //|// Broadcastto All Users that new topic set as follow
                        //| <-  :fort!~u@qk3i8byd6tfyg.irc TOPIC #ola newTOPICACHABAB
                        //| 
                        //See What Will be Broadcasted Here
                    }
                    else
                    {
                        // <-  :testnet.ergo.chat 482 oktal #fortan :You're not a channel operator;
        std::string response (NumericReplies(MYhost::GetHost(), "482", "NICKNAME", channelName, "You are not CHANNEL CHANOP"));
                            send(__fd, response.c_str(), response.length(), 0);
                        // response = 
                    }
                    //TryToset the channelTopic . . .
                    
                }
                
            }else
            {
                response = NumericReplies(MYhost::GetHost(), "442", "NICKNAME", channelName, "You are not on this channel");
                throw EX_NOTONCHANNEL();
            }
            
        }
        else
        {   
            response = NumericReplies(MYhost::GetHost(), "403", "NICKNAME", channelName, "No such channel");
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
        std::string response = ":" + MYhost::GetHost() + " 461 " + " NICKNAME " + " TOPIC " + ": NO ENOUGH PARAMETERS" + "\n" +
            NumericReplies(MYhost::GetHost(), "999", "NICKNAME", "TOPIC", "<channel> +/-[<TOPIC>]");
                send(__fd, response.c_str(), response.length(), 0);
    }
    else{
        
        std::stringstream stream(clientMsg);
        std::string       component;
        std::string       channelName;
        std::string       TOPIC;
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
                TOPIC += component + " ";
                break;
            }
        index++;
        }
        
        TOPICprocessor(OccurSpace, channelName ,clientMsg, __fd, TOPIC);
    }
}