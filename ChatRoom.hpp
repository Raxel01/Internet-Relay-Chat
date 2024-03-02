/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChatRoom.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ta <abait-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 12:29:36 by abait-ta          #+#    #+#             */
/*   Updated: 2024/03/01 23:29:24 by abait-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <sstream>
#include <deque>
#include <map>


// class Clients; need it to Store 
typedef std::deque<std::string> DEQUE ;

class ChatRoom
{
    public :
        const std::string     _RoomName         ;
        std::string           _ChatTopic        ;
        DEQUE                _Members           ;
        DEQUE                _BannedUsers       ;
        DEQUE                _Mediators         ;
        DEQUE                _InviteList        ;
        std::string           _ChatKey          ;
        size_t               _AllowedUsers      ; //Limit Setted;
        bool                 _Acces_isInviteOnly;
        bool                 keyStatus          ; //+k if the key is setted or not 
        bool                 HaveLimitUser      ; //+l
        bool                 TopicRestriction   ;   //+t [+t] seTtoknow Who will seet the Topic
    public :
        ChatRoom();
        ChatRoom(std::string& Creator,std::string& SetRoomName);
        
        void            Addasmember(std::string& newMember);
        void            AddasMediator(std::string& NewMediator);
        void            BanThisUser(std::string User);
        
        void            removeMember(std::string& tobeRemoved);
        void            removeMediator(std::string& toBeremoved);

        bool            IsalreadyMember(std::string& MayUser);
        bool            IsMediator(std::string& MayMediator);
        bool            IsBanned(std::string& MayBanned);
        DEQUE::iterator IsRegularUser(std::string User);
        bool            IsInviteList(std::string& TargetUser);
        std::string     MembersList();
        void            getelems();
        const std::string&    GetRoomname();    
        ~ChatRoom(); 
};

class GlobalServerData{
    public :
        static std::vector<ChatRoom>   ServerChannels; // all serverchannel
};


