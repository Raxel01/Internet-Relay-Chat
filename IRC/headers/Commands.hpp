/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ta <abait-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 23:35:47 by abait-ta          #+#    #+#             */
/*   Updated: 2024/03/13 20:46:52 by abait-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once


# include <iostream>
# include <vector>
# include <sstream>
# include <sys/socket.h>
# include <deque>
# include "ChatRoom.hpp"
# include "GlobalException.hpp"

/* 
    @: Join Function and all needed Stuffff ******************************************************* */

class ChatRoom;

typedef  std::vector<ChatRoom>::iterator Roomiter;

typedef  std::vector<std::string> Myvector;

enum    ChannelStatus{
    
    TOBE_JOINED = 0,
    TOBE_BUILDED,
};

enum KeyType
{
    KEY_PROVIDED,
    NO_KEY_PROVIDED,
};

void        ExtractChannels( std::string& ClientMsg, std::vector<std::string>& Channels );
void        ExtractKeys( std::string& ClientMsg, std::vector<std::string>& keys );
void        JoinStart( int __fd, std::string& clientMsg, Myvector&  Channels, Myvector& keys );
bool        FollowGrammar( std::string &channel );
Roomiter    FindUsingName( std::string& channelName );
std::string ToUpper( std::string channel );
void        BroadcastMessage( std::string user, std::string ChannelName, \
            Roomiter& iter, std::string response );
void        JoinMessage( std::string& clientMsg, int __fd );
void        JoinProcessor( std::string& clientMsg, int __fd );

/*****************************************************************************************/

/*
    @: KICK Function And All What it need  ************************************************************[
*/


void                ExtractVictims(std::string& userList, std::vector<std::string>& Victims);
void                KickExecutor(std::string&channelName , Roomiter& iter, int __fd, \
                    std::vector<std::string>& Victims, std::string& reason);
bool                IsTargetInServer(std::string Name);
bool                SelfKick(std::string& Mediator, std::string& Victim);
void                KickMessage(std::string& clientMsg, int __fd);
void                KickProcessor(std::string& channelName, std::string& userList, \
                    int __fd, std::string& Reason);
/*
    @*************************************************************************************************]
*/


/*
    @: PART Function And All What it need  ************************************************************[
*/
                void    PartMessage(std::string& clientMsg, int __fd);
/*
    @*************************************************************************************************]
*/

/*
    @: TOPIC Function And All What it need  ************************************************************[
*/
        void    TOPICmessage(std::string& clientMsg, int __fd);
/*
    @***************************************************************************************************]
*/

/*
    @: MODE Function And All What it need  ************************************************************[
*/

enum MODETYPE
{
    REMOVE_MODE = 0,
    ADD_MODE,
    ERROR_MODE,
};

void    ModeMessage(std::string& clientMsg, int __fd);

/*
    @***************************************************************************************************]
*/




/*
    @: INVITE Function And All What it need  ************************************************************[
*/
    #define NOTICE_INVITED 1
    #define DONT_NOTICE    0

    void     InviteMessage(std::string& clientMsg, int __fd);
    int      GetInvitedFd(std::string USER);
/*
    @***************************************************************************************************]
*/





/*
    @= PRIVVMESSAGE     *****************]]]]]]]]]]]]]
*/

void        PRIVMessage(std::string& clientMsg, int __fd);

/*****************************************************/

std::string    NumericReplies(std::string Prefix, std::string CODEREPLY, std::string NICKNAME, std::string CMD, std::string RAISON);


// **********************************// QUIT //************************* //
void    QUITmessage(int __fd);

//**********************************************************************//