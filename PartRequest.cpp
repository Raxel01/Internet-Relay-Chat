/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PartRequest.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ta <abait-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 03:17:08 by abait-ta          #+#    #+#             */
/*   Updated: 2024/03/02 08:36:25 by abait-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PartRequest.hpp"
#include "JoinRequest.hpp"
#include "MessageRecognizer.hpp"
#include "GlobalException.hpp"
#include "ChatRoom.hpp"

void    FullChannelList(std::string& channelList, std::deque<std::string>& channelVector)
{
    std::stringstream stream(channelList);
    std::string Holder;
    
    while(std::getline(stream, Holder, ',')){
        channelVector.push_back(Holder);
    }
}

//STOP IN 02/03/ :8 : 36
void    PartProcessor(std::deque<std::string>& Channels, int __fd, std::string& Reason)
{
    size_t i = -1;
    std::string owner("abdelali");
    std::vector<ChatRoom>::iterator Finder;
    std::string response;
    
    while (++i < Channels.size())
    {
        
        Finder = FindUsingName(Channels.at(i));
        try{
        if (Finder != GlobalServerData::ServerChannels.end())
        {
            if ((*Finder).IsalreadyMember(owner) == true)//Server::ServerClient.at(__fd).nickname;
            {
                if ((*Finder).IsMediator(owner) == true)
                {
                    std::cout << " Mediator "<< std::endl;
                }
                else if ((*Finder).IsRegularUser(owner) != (*Finder)._Members.end())
                {
                    //obj._Members.erase((obj).ISregularUser(owner)) nickname of The User
                        BroadcastMessage("", "" , Finder, response);
                        (*Finder)._Members.erase((*Finder).IsRegularUser(owner));
                        std::cout << "Not Mediator"<< std::endl;
                }
                
            }
            else{
                response = NumericReplies(MYhost::GetHost(), "442", "NICKNAME", Channels.at(i), "You are not on this channel");
                throw EX_NOTONCHANNEL();
            }
        }
        else
        {
            response = NumericReplies(MYhost::GetHost(), "403", "NICKNAME", Channels.at(i), "No such channel");
            throw Ex_NOSUCHCHANNEL();
        }
        }
        catch (std::exception& e){
            send(__fd, response.c_str(), response.length(), 0);
            response.clear();
            e.what();
        }
        
    }
}

void    PartMessage(std::string& clientMsg, int __fd)
{
    
    size_t OccurSpace = std::count(clientMsg.begin(), clientMsg.end(), ' ');
    
    if (OccurSpace == 0 || clientMsg.compare("PART :") == 0){
        std::string response = ":" + MYhost::GetHost() + " 461 " + " NICKNAME " + " PART " + ": NO ENOUGH PARAMETERS" + "\n" +
        NumericReplies(MYhost::GetHost(), "999", "NICKNAME", "PART", ":<channel,channel1,...> [<reason>]");
        send(__fd, response.c_str(), response.length(), 0);
    }
    else
    {
        std::stringstream stream(clientMsg);
        std::string       component;
        std::string       channelList;
        std::string       Reason;
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
                channelList = component;
                break;
            default:
                Reason += component + " ";
                break;
            }
        index++;
        }
        if (Reason.empty())
            Reason = "Just Leaving...";
        std::deque<std::string> Channels;
        FullChannelList(channelList, Channels);
        PartProcessor(Channels, __fd, Reason);
    }
}