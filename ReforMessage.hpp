/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ReforMessage.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ta <abait-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 12:15:00 by abait-ta          #+#    #+#             */
/*   Updated: 2024/02/26 16:47:35 by abait-ta         ###   ########.fr       */
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