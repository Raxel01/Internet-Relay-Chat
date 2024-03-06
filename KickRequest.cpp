/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   KickRequest.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ta <abait-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 01:18:41 by abait-ta          #+#    #+#             */
/*   Updated: 2024/03/04 09:18:19 by abait-ta         ###   ########.fr       */
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
    return (true);//Remove IT
    // std::map<int, Client>::iterator iter = Server::ServerClient.begin();
    
    // while (iter != Server::ServerClient.end())
    // {
    //     if (iter->second.nickname == Name)
    //         return (true);
    //     iter++;
    // }
    // return (false);

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
    std::string owner("abdelali"); // remove after;
    std::string response;
    while (++i < Victims.size()){
        /*[[[*/
        if (i != 0)//remove this shiit
            (*iter).Addasmember(Victims.at(i)); // tOREMOVE;
        /*]]]*/
        try{
            if (IsVictimInServer(Victims.at(i)) == true)
            {
                if ((*iter).IsalreadyMember(Victims.at(i)) == true)
                {
                    if (SelfKick(owner, Victims.at(i)) == false) //Change owner By Server::ServerClient.at(fd).nickname it After;
                    {
                        // response = Server::ServerClient.at(__fd).nickname +"!~" + MYhost::GetHost() + " KICK " + channelName + Victims.at(i) + Server::ServerClient.at(__fd).nickname;
                        // BroadcastMessage(Server::ServerClient.at(__fd), channelName, iter, response + reason);
                        (*iter).BanThisUser(Victims.at(i));
                    }else
                    {
                        response = NumericReplies(MYhost::GetHost(), "999", "NickName", Victims.at(i), "An Operator Can't Kick it Self");
                        throw SELF_KICK();
                    }
                }
                else {
                    response = NumericReplies(MYhost::GetHost(), "441", "NickName", Victims.at(i), "This Client Is Not in " + channelName);
                    throw EX_USERNOTINCHANNEL();
                } 
            }
            else{
                response = NumericReplies(MYhost::GetHost(), "401", "NickName", Victims.at(i), "No Client named as follow In Server");
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
    std::string owner("abdellai"); //To Remove
        try{
        Roomiter iter = FindUsingName(channelName);
        if (iter != GlobalServerData::ServerChannels.end()) {
            try{
                if ((*iter).IsalreadyMember(owner) == true) // change Here Server::ServerClient.at(__fd);
                {
                    try
                    {
                        if((*iter).IsMediator(owner) == true)//change this shiiit Server::ServerClient.at(__fd)
                        {
                             std::vector<std::string> Victims;
                             ExtractVictims(userList, Victims);
                             KickExecutor(channelName ,iter, __fd, Victims,Reason);
                        }
                        else
                            throw Ex_CHANOPRIVSNEEDED();
                    }
                    catch (Ex_CHANOPRIVSNEEDED& e){
                        std::string response (NumericReplies(MYhost::GetHost(), "482", "NICKNAME", channelName, "You are not CHANNEL CHANOP"));
                            send(__fd, response.c_str(), response.length(), 0);
                                e.what();
                    }
                }
                else
                    throw EX_NOTONCHANNEL();
            }
            catch(EX_NOTONCHANNEL& e){
                std::string response (NumericReplies(MYhost::GetHost(), "442", "NICKNAME", channelName, "Bad Request Your are Not a part of this channel"));
                    send(__fd, response.c_str(), response.length(), 0);
                         e.what();
            }
    }
    else
        throw Ex_NOSUCHCHANNEL();
    }catch(Ex_NOSUCHCHANNEL& e){
        std::string response (NumericReplies(MYhost::GetHost(), "403", "NICKNAME", channelName, "No such channel"));
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
        /***********************ADD FOR TEST***************************/
        std::string owner("abdelali");
        ChatRoom OBJON(owner, channelName);
        // OBJON.AddasMediator("Flan");
        std::string notAdmin("bolan");
        // std::string noton
        GlobalServerData::ServerChannels.push_back(OBJON);
        /****************************************************/
        KickProcessor(channelName, userList, __fd, Reason);
    }
}

