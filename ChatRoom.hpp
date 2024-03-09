/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChatRoom.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ta <abait-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 12:29:36 by abait-ta          #+#    #+#             */
/*   Updated: 2024/03/09 21:33:23 by abait-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <iostream>
# include <sstream>
# include <deque>
# include <map>
# include <ctime>
# include <unistd.h>
# include <sys/socket.h>
# include <vector>
#include  "Server.hpp" // May need to change the path

#define LIMITUSERS 900
// class Clients; need it to Store 
typedef std::deque<std::string> DEQUE ;

class ChatRoom
{
    public :
        // clock_t               CreationTime      ;
        std::string          _RoomName         ;
        std::string          _ChatTopic        ;
        DEQUE                _Members           ;
        DEQUE                _BannedUsers       ;
        DEQUE                _Mediators         ;
        DEQUE                _InviteList        ;
        std::string          _ChatKey          ;
        size_t               _AllowedUsers      ; //Limit Setted;
        bool                 _Acces_isInviteOnly;
        bool                 keyStatus          ; //+k if the key is setted or not 
        bool                 HaveLimitUser      ; //+l
        bool                 TopicRestriction   ;   //+t [+t] seTtoknow Who will seet the Topic
        bool                 TopicStatus        ;
        std::string          ModeReply          ;
        std::string          ModeArgs           ;
        // clock_t              Destruction        ;
    public :
        ChatRoom();
        ChatRoom(std::string& Creator,std::string& SetRoomName);
        
        void            Addasmember(std::string& newMember);
        void            AddasMediator(std::string& NewMediator);
        void            AddToInvited(std::string& NewInvited);
        void            UpgradeToChanoP(std::string USER);
        void            ChannelMode(int __fd);
        void            BanThisUser(std::string User);
        void            PardonUser(std::string USER);//Remove FromBanList When invite
        std::string     getTOPIC();
        void            ToRegularUser (std::string USER);
        void            SetTOPIC(std::string Topic);
        void            eraseFromInvList(std::string Invited);
        // void            removeMember(std::string& tobeRemoved);
        void            PartMediator(std::string& toPart);
        bool            IsalreadyMember(std::string& MayUser);
        bool            IsMediator(std::string& MayMediator);
        bool            IsBanned(std::string& MayBanned);
        DEQUE::iterator IsRegularUser(std::string User);
        bool            IsInviteList(std::string& TargetUser);
        std::string     MembersList();
        void            getelems();
        std::string&    GetRoomname();
        size_t                Roomsize();
        ~ChatRoom(); 
};

class MYhost // GetTheHost
{
    public :
    static std::string GetHost();
};


class GlobalServerData{
    public :
        static std::vector<ChatRoom>   ServerChannels; // all serverchannel
        static int LastChannelUser;
};


