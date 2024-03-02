/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JoinRequest.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ta <abait-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 06:38:27 by abait-ta          #+#    #+#             */
/*   Updated: 2024/03/02 01:44:58 by abait-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <iostream>
# include <vector>
# include <sstream>
# include <unistd.h>
# include <sys/socket.h>



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

class InvalidChannelName : public std::exception{
    public :
            virtual const char* what() const throw(); 
};

class MYhost // GetTheHost
{
    public :
    static std::string GetHost();
};



void        ExtractChannels( std::string& ClientMsg, std::vector<std::string>& Channels );
void        ExtractKeys( std::string& ClientMsg, std::vector<std::string>& keys );
void        JoinStart( int __fd, std::string& clientMsg, Myvector&  Channels, Myvector& keys );
bool        FollowGrammar( std::string &channel );
Roomiter    FindUsingName( std::string& channelName );
std::string ToUpper( std::string channel );
void        BroadcastMessage( std::string user, std::string ChannelName, \
        Roomiter& iter, std::string response );
void    JoinMessage( std::string& clientMsg, int __fd );
void    JoinProcessor( std::string& clientMsg, int __fd );
