/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ReforMessage.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ta <abait-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 12:15:00 by abait-ta          #+#    #+#             */
/*   Updated: 2024/03/10 03:40:36 by abait-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <iomanip>
#include <sstream>
#include <sys/socket.h>

/*
    @: Static memebers Class Constructor as Private  will never let the class Instanciated
*/

#define    KICK       "KICK"
#define    INVITE     "INVITE"
#define    MODE       "MODE"
#define    TOPIC      "TOPIC"
#define    JOIN       "JOIN"
#define    PART       "PART"
#define    PONG       "PONG"
#define    UNKNOW     "UNKNOW"
#define    IGNORE     "IGNORE"
#define    CONTINUE   "CONTINUE"
#define    QUIT       "QUIT"
#define    PRIVMSG    "PRIVMSG"


class ReforMessage
{
    private:
        static size_t   start;
        static size_t   end;
        static int      flag;
        static int      i;
        ReforMessage();
    public :
        static std::string     FinalMessage;
        static void   GlobalReform(std::string Message);
        static void   TriMessage();
        static void   CleanMessage();
        static void   removeCRLF();
        static void   Reinitializer();
};

/*
    @= This Part Is About Recognizing which Command The Client typed
*/

std::string         RegularUsers(std::string& cmd,std::string& clientMsg, int __fd);
std::string         RecognizeCmd(std::string& cmd, std::string& clientMsg, int __fd);
void                MediatorCommand(std::string &FullMessage, int __fd);
std::string       NumericReplies(std::string Prefix, std::string CODEREPLY, std::string NICKNAME, \
std::string CMD, std::string RAISON);
