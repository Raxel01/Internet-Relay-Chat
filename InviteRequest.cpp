/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   InviteRequest.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ta <abait-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 09:57:31 by abait-ta          #+#    #+#             */
/*   Updated: 2024/03/11 17:46:28 by abait-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Commands.hpp"

int      GetInvitedFd(std::string USER)
{
    std::map<int, Client>::iterator iter = Server::ServerClients.begin();
    
    while (iter != Server::ServerClients.end())
    {
        if (iter->second.nickname == USER)
                    return (iter->first);
        iter++;
    }
    return (-1);
}

void    FilterRequest(std::string& response, int& __fd, std::string& CHANNEL, std::string&USER, Roomiter& RoomObj)
{
        if (RoomObj == GlobalServerData::ServerChannels.end()){
            response = NumericReplies(MYhost::GetHost(), "403", Server::ServerClients.at(__fd).nickname, CHANNEL, "No such channel");
                throw Ex_NOSUCHCHANNEL();
        }
        if (IsTargetInServer(USER) == false){
            response = ":" + MYhost::GetHost() + " 401 " + Server::ServerClients.at(__fd).nickname + " " + USER + " : NO USER WITH THIS NAME IN SERVER\n";
                throw EX_NOSUCHNICK();
        }
        if ((*RoomObj).IsalreadyMember(Server::ServerClients.at(__fd).nickname) == false){// check if the command writer is a member on this channel first
            response = NumericReplies(MYhost::GetHost(), "442", Server::ServerClients.at(__fd).nickname, CHANNEL, "You are not on this channel");
                throw EX_NOTONCHANNEL();
        }
        if ((*RoomObj).IsMediator(Server::ServerClients.at(__fd).nickname) == false){//chek if this wrtter(CLIENT) is a Mediator
            response = (NumericReplies(MYhost::GetHost(), "482", Server::ServerClients.at(__fd).nickname, CHANNEL, "You are not CHANNEL CHANOP"));
                throw Ex_CHANOPRIVSNEEDED();
        }
        if ((*RoomObj).IsalreadyMember(USER) == true){
            response = MYhost::GetHost() + " 443 " + Server::ServerClients.at(__fd).nickname + " " + CHANNEL + " :User already on channel\n";
                throw EX_ALREADYINCHANNEL();
        }
        if ((*RoomObj).IsInviteList(USER) == true){
            response = MYhost::GetHost() + " 999 " + Server::ServerClients.at(__fd).nickname + " " + CHANNEL + " :User already Invited To channel\n";
                throw EX_DUPLICATE_INVITE();
        }
}

void    InviteProcessor(std::string& USER, std::string& CHANNEL, int __fd)
{
    Roomiter    RoomObj;
    std::string response;
    short notice = DONT_NOTICE;
    
    RoomObj = FindUsingName(CHANNEL);
    try
    {
        FilterRequest(response, __fd, CHANNEL, USER, RoomObj);
        //INVITE REQUEST will be accepted;
        (*RoomObj).AddToInvited(USER);
        if ((*RoomObj).IsBanned(USER) == true){ //My kick add The user to ban List so invite can Pardon THIS USER [Banned 1]
            (*RoomObj).PardonUser(USER);
        }
        response = ":" + MYhost::GetHost() + " 341 " + Server::ServerClients.at(__fd).nickname + " " + USER + " "+CHANNEL + "\n";
            notice = NOTICE_INVITED;
                throw EX_VALIDINVITE();
    }
    catch(std::exception& e)
    { 
      send(__fd, response.c_str(), response.length(), 0);
         response.clear();
            e.what();
             if (notice == NOTICE_INVITED) // SEND message to invited USER;asfollow
             {   response.clear();
                   response = ":" + Server::ServerClients.at(__fd).nickname + "!~" + Server::ServerClients.at(__fd).username + "@" + Server::ServerClients.at(__fd).client_ip + " INVITE " + USER + " " + CHANNEL + "\n";
                    int USER_FD = GetInvitedFd(USER);
                        send(USER_FD , response.c_str(), response.length(), 0);
                            }
    }
}

void    InviteMessage(std::string& clientMsg, int __fd)
{
    size_t OccurSpace = std::count(clientMsg.begin(), clientMsg.end(), ' ');
    
    if (OccurSpace == 0 || OccurSpace == 1){
        std::string response = ":" + MYhost::GetHost() + " 461 " + " NICKNAME " + " INVITE " + ": NO ENOUGH PARAMETERS" + "\n" +
            NumericReplies(MYhost::GetHost(), "999", "NICKNAME", "INVITE", "<USER> <CHANNEL>");
                send(__fd, response.c_str(), response.length(), 0);
    }
    else
    {
        std::stringstream stream(clientMsg);
        std::string       component;
        std::string       USER;
        std::string       CHANNEL;
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
                USER = component;
                break;
            case 2:
                CHANNEL = component;
            default:
                break;
            }
            if (index == 2)
                break;
        index++;
        }
        InviteProcessor(USER, CHANNEL, __fd);
    }
}