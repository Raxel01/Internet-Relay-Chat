/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   InviteRequest.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ta <abait-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 09:57:31 by abait-ta          #+#    #+#             */
/*   Updated: 2024/03/04 05:43:57 by abait-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "InviteRequest.hpp"
#include "JoinRequest.hpp"
#include "MessageRecognizer.hpp"
#include "GlobalException.hpp"
#include "ChatRoom.hpp"

#define NOTICE_INVITED 1
#define DONT_NOTICE    0

void    InviteProcessor(std::string& USER, std::string& CHANNEL, int __fd)
{
    Roomiter    RoomObj;
    std::string response;
    std::string owner("abdelali");
    size_t notice = DONT_NOTICE;
    RoomObj = FindUsingName(CHANNEL);
    try
    {
        if (RoomObj == GlobalServerData::ServerChannels.end()){
            response = NumericReplies(MYhost::GetHost(), "403", "NICKNAME", CHANNEL, "No such channel");
            throw Ex_NOSUCHCHANNEL();
        }
        if ((*RoomObj).IsalreadyMember(owner) == false){// check if the command writer is a member on this channel first
            response = NumericReplies(MYhost::GetHost(), "442", "NICKNAME", CHANNEL, "You are not on this channel");
                throw EX_NOTONCHANNEL();
        }
        if ((*RoomObj).IsMediator(owner) == false){//chek if this wrtter(CLIENT) is a Mediator
            response = (NumericReplies(MYhost::GetHost(), "482", "NICKNAME", CHANNEL, "You are not CHANNEL CHANOP"));
                throw Ex_CHANOPRIVSNEEDED();
        }
        if ((*RoomObj).IsalreadyMember(USER) == true){
            response = MYhost::GetHost() + " " + "443" + " " + " NIVKNAME " + CHANNEL + " :User already on channel";
                throw EX_ALREADYINCHANNEL();
        }
        if ((*RoomObj).IsInviteList(USER) == true){
            response = MYhost::GetHost() + " 999 " + " NIVKNAME " + CHANNEL + " :User already Invited To channel";
                throw EX_DUPLICATE_INVITE();
        }
        //if all process Passed the INVITE will be accepted;
        (*RoomObj).AddToInvited(USER);
        
        if ((*RoomObj).IsBanned(USER) == true){//My kick add The user to ban List so invite can Pardon it
            (*RoomObj).PardonUser(USER);
        }
        response = MYhost::GetHost() + " 341 " + " NICKNAME " + USER + CHANNEL;
        notice = NOTICE_INVITED;
    }
    catch(std::exception& e)
    {send(__fd, response.c_str(), response.length(), 0);
        response.clear();
            e.what();
        if (notice == NOTICE_INVITED) // SEND message to invited USER;asfollow
        {
            response.clear();
            // /*************************/ response form;
            // response = clinetnickname + "!~" + MYhost::Gethost()+ " INVITE " + USER + CHANNEL;
            /*************************/
            //get User fd
            /**************************/
            // send(USER_FD , response.c_str(), response.length(), 0);
            /**************************/
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