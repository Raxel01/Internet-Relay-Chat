/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   KickRequest.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ta <abait-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 01:18:41 by abait-ta          #+#    #+#             */
/*   Updated: 2024/03/06 10:19:02 by abait-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "KickRequest.hpp"
#include "GlobalException.hpp"
#include "MessageRecognizer.hpp"
#include "JoinRequest.hpp"



void     ExtractVictims(std::string& userList, std::vector<std::string>& Victims)
{
    std::stringstream stream(userList);
    std::string Toban;
    while (std::getline(stream, Toban, ',')){
        Victims.push_back(Toban);
    }
}

bool    IsVictimInServer(std::string Name)
{
    std::map<int, Client>::iterator iter = Server::ServerClients.begin();
    
    while (iter != Server::ServerClients.end())
    {
        if (iter->second.nickname == Name)
            return (true);
        iter++;
    }
    return (false);
}

bool    SelfKick(std::string& Mediator, std::string& Victim)
{
    if (Mediator == Victim)
        return true;
    return false;
}
   
void    KickExecutor(std::string&channelName , Roomiter& iter, int __fd,std::vector<std::string>& Victims, std::string& reason)
{
    size_t i = -1;
    std::string response;
    
    while (++i < Victims.size()){
        try{
            if (IsVictimInServer(Victims.at(i)) == true)
            {
                if ((*iter).IsalreadyMember(Victims.at(i)) == true)
                {
                    if (SelfKick(Server::ServerClients.at(__fd).nickname, Victims.at(i)) == false) //Change owner By Server::ServerClient.at(fd).nickname it After;
                    {
                        // <-  :oflat!~u@qk3i8byd6tfyg.irc KICK #ola oltas oflat recheck Here
                        response = Server::ServerClients.at(__fd).nickname +"!~" + MYhost::GetHost() + " KICK " + channelName + " " + Victims.at(i)+ " " + Server::ServerClients.at(__fd).nickname + " :" + reason + "\n";
                        BroadcastMessage("", channelName, iter, response);
                        (*iter).BanThisUser(Victims.at(i));
                    }else
                    {
                        response = NumericReplies(MYhost::GetHost(), "999", Server::ServerClients.at(__fd).nickname, Victims.at(i), "An Operator Can't Kick it Self");
                            throw SELF_KICK();
                    }
                }
                else {
                    response = NumericReplies(MYhost::GetHost(), "441", Server::ServerClients.at(__fd).nickname, Victims.at(i), "This Client Is Not in " + (*iter)._RoomName);
                    throw EX_USERNOTINCHANNEL();
                } 
            }
            else{
                response = NumericReplies(MYhost::GetHost(), "401", Server::ServerClients.at(__fd).nickname, Victims.at(i), "No Client named as follow In Server");
                throw EX_NOSUCHNICK();
        }
        }catch(std::exception& e){
            send(__fd, response.c_str(), response.length(), 0);
            response.clear();
        }
    }
    (*iter).getelems();//To ~ Remove after :
}  

void    KickProcessor(std::string& channelName, std::string& userList, int __fd, std::string& Reason)
{
        try{
        Roomiter iter = FindUsingName(channelName);
        if (iter != GlobalServerData::ServerChannels.end()) {
            try{
                if ((*iter).IsalreadyMember(Server::ServerClients.at(__fd).nickname) == true) // Requester is in channel;
                {
                    try
                    {
                        if((*iter).IsMediator(Server::ServerClients.at(__fd).nickname) == true)//requester is a mediator(Admin);
                        {
                             std::vector<std::string> Victims;
                             ExtractVictims(userList, Victims);
                             KickExecutor(channelName ,iter, __fd, Victims,Reason);
                        }
                        else
                            throw Ex_CHANOPRIVSNEEDED();
                    }
                    catch (Ex_CHANOPRIVSNEEDED& e){
                        std::string response (NumericReplies(MYhost::GetHost(), "482", Server::ServerClients.at(__fd).nickname, channelName, "You are not CHANNEL CHANOP"));
                            send(__fd, response.c_str(), response.length(), 0);
                                e.what();
                    }
                }
                else
                    throw EX_NOTONCHANNEL();
            }
            catch(EX_NOTONCHANNEL& e){
                std::string response (NumericReplies(MYhost::GetHost(), "442", Server::ServerClients.at(__fd).nickname, channelName, "Bad Request Your are Not a part of this channel"));
                    send(__fd, response.c_str(), response.length(), 0);
                         e.what();
            }
    }
    else
        throw Ex_NOSUCHCHANNEL();
    }catch(Ex_NOSUCHCHANNEL& e){
        std::string response (NumericReplies(MYhost::GetHost(), "403", Server::ServerClients.at(__fd).nickname, channelName, "No such channel"));
        send(__fd, response.c_str(), response.length(), 0);
        e.what();
    }
}

void        KickMessage(std::string& clientMsg, int __fd)
{
    std::stringstream stream(clientMsg);
    
    size_t OcuurSpace = std::count(clientMsg.begin(), clientMsg.end(), ' ');
    
    if (OcuurSpace == 0 || OcuurSpace == 1){
        std::string response = (NumericReplies(MYhost::GetHost(), "461", "NICKNAME", "KICK", ":No enough parameters.")) + \
        NumericReplies(MYhost::GetHost(), "999", "NICKNAME", "KICK", ":<channel> [<nick>[,<nick>]] + [:<reason>]");
        send (__fd, response.c_str(), response.length(), 0);
    }
    else{
        std::stringstream stream(clientMsg);
        std::string component;
        std::string channelName;
        std::string userList;
        std::string Reason;
        
        short index = 0;
        while (std::getline(stream, component, ' ')){
            switch (index){
            case 0:
                component.clear();
                break;
            case 1:
                channelName = component;
                break;
            case 2:
                userList = component;
                break;
            default:
                Reason += component + " ";
                break;
            }     
            index++;
        }
        if (Reason.empty())
            Reason = "Admin is a Dictator";

        KickProcessor(channelName, userList, __fd, Reason);
    }
}

