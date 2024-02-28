/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChatRoom.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ta <abait-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 12:29:36 by abait-ta          #+#    #+#             */
/*   Updated: 2024/02/26 22:58:02 by abait-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <sstream>
#include <deque>


typedef std::deque<std::string> DEQUE ;

enum    ChannelStatus{
    ALREADY_EXIST = 0,
    TOBE_BUILDED,
};

class ChatRoom
{
    private:
        const std::string     _RoomName    ;
        std::string           _ChatKey     ;
        std::string           _ChatTopic   ;
        DEQUE                _Members     ;
        DEQUE                _BannedUsers ;
        DEQUE                _Mediators   ;
        size_t               _AllowedUsers;
        bool                 Acces_isInviteOnly;
        bool                 KeyState;
    public :
        ChatRoom();
        ChatRoom(std::string& Creator,std::string& SetRoomName);//Instanciat A Non existinGChannel
        // void    JoinRegularuser(std::string& Newmember);
        // void    AddAsMediator(std::string & NewMediator);
        void    BanThisUser(std::string);
        const std::string&    GetRoomname();
        bool                  GetKeyState();
        ~ChatRoom(); 
};


class GlobalServerData{
    public :
        static std::vector<ChatRoom>   ServerChannels;
        // static 
        // static std::vector<Clients> ServerClients;
};


