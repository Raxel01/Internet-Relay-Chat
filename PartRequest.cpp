/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PartRequest.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ta <abait-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 03:17:08 by abait-ta          #+#    #+#             */
/*   Updated: 2024/03/10 03:49:42 by abait-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

void    FullChannelList(std::string& channelList, DEQUE& channelVector)
{
    std::stringstream stream(channelList);
    std::string Holder;
    
    while(std::getline(stream, Holder, ',')){
        channelVector.push_back(Holder);
    }
}

//STOP IN 02/03/ :8 : 36

void    PartProcessor(DEQUE& Channels, int __fd, std::string& Reason)
{
    size_t i = -1;
    Roomiter Finder;
    std::string response;
    
    while (++i < Channels.size())
    {
        Finder = FindUsingName(Channels.at(i));
        try{
        if (Finder != GlobalServerData::ServerChannels.end())
        {
            if ((*Finder).IsalreadyMember(Server::ServerClients.at(__fd).nickname) == true)//Server::ServerClient.at(__fd).nickname;
            {
                response = ":" + Server::ServerClients.at(__fd).nickname + "!~" + Server::ServerClients.at(__fd).username +"@"+ Server::ServerClients.at(__fd).client_ip + " PART " + (*Finder)._RoomName + " :" + Reason + "\n";
                if ((*Finder).IsMediator(Server::ServerClients.at(__fd).nickname) == true){
                    BroadcastMessage("", "" , Finder, response);
                    (*Finder).PartMediator(Server::ServerClients.at(__fd).nickname); //  owner to Change
                }
                else if ((*Finder).IsRegularUser(Server::ServerClients.at(__fd).nickname) != (*Finder)._Members.end()){//User is a member
                        BroadcastMessage("", "" , Finder, response);
                        (*Finder)._Members.erase((*Finder).IsRegularUser(Server::ServerClients.at(__fd).nickname));
                }
                /* I think I'll Broadcast Here */
                if ((*Finder).Roomsize() == 0 || (*Finder)._Mediators.size() == 0){// if no admin or no member the Channel Will be Destroyed
                        GlobalServerData::LastChannelUser = __fd;
                        GlobalServerData::ServerChannels.erase(Finder);
                    }
            }
            else{
                response = NumericReplies(MYhost::GetHost(), "442", Server::ServerClients.at(__fd).nickname, Channels.at(i), "You are not on this channel");
                throw EX_NOTONCHANNEL();
            }
        }
        else{
            response = NumericReplies(MYhost::GetHost(), "403", Server::ServerClients.at(__fd).nickname, Channels.at(i), "No such channel");
            throw Ex_NOSUCHCHANNEL();
        }
        }catch (std::exception& e){
            send(__fd, response.c_str(), response.length(), 0);
               response.clear();
                  e.what();
        }
        
    }
}

/*
    @ -: This Message let a user Tobe out OfThe List of channels if he is a member
      - ofCours there is a lot of Conditions to Check
      -From abdelali use your mind :)
*/
void    PartMessage(std::string& clientMsg, int __fd)
{
    
    size_t OccurSpace = std::count(clientMsg.begin(), clientMsg.end(), ' ');
    
    if (OccurSpace == 0 || clientMsg.compare("PART :") == 0){
        std::string response = ":" + MYhost::GetHost() + " 461 " + Server::ServerClients.at(__fd).nickname + " PART " + ": NO ENOUGH PARAMETERS" + "\n" +
            NumericReplies(MYhost::GetHost(), "999", Server::ServerClients.at(__fd).nickname, "PART", "<channel,channel1,...> [<reason>]");
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
            Reason = " Just Leaving...";
        DEQUE Channels;
        FullChannelList(channelList, Channels);
        PartProcessor(Channels, __fd, Reason);
    }
}