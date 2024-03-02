/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MessageRecognizer.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ta <abait-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 12:25:08 by abait-ta          #+#    #+#             */
/*   Updated: 2024/03/02 03:38:55 by abait-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include   "ReforMessage.hpp"
# include   "JoinRequest.hpp"
# include   "ChatRoom.hpp"
# include   "GlobalException.hpp"
# include  "KickRequest.hpp"
# include   "PartRequest.hpp"

std::string    NumericReplies(std::string Prefix, std::string CODEREPLY, std::string NICKNAME, std::string CMD, std::string RAISON)
{
    std::string Reply;
    Reply = ":" + Prefix + " " + CODEREPLY + " " + NICKNAME + " " + CMD +" :" + RAISON + "\n";
    return (Reply);
}



std::string RegularUsers(std::string& cmd,std::string& clientMsg, int __fd){
    if (cmd.compare(JOIN) == 0){
        JoinMessage(clientMsg, __fd);
        return (JOIN);
    }
    else if (cmd.compare(PART) == 0)
    {
        PartMessage(clientMsg, __fd);
        return (PART);
    }
    else if (cmd.compare(PONG) != 0){
        std::string response(NumericReplies("localhost", "421", "canis_lupus", cmd, "Unknown command"));
        send (__fd, response.c_str(), response.length(), 0);
        return  UNKNOW;
    }
    return IGNORE;
}

std::string RecognizeCmd(std::string& cmd, std::string& clientMsg, int __fd)
{
         if (cmd.compare(KICK) == 0)
         {
            KickMessage(clientMsg, __fd);
                return KICK;
    }
    else if (cmd.compare(INVITE) == 0){
            // InviteMessage(clientMsg);
                return INVITE;
    }
    else if (cmd.compare(TOPIC)  == 0){
        // TopicMessage(clientMsg);
                return TOPIC;
    }
    else if (cmd.compare(MODE)   == 0){
        // ModeMessage(clientMsg);
                return (MODE);
    }
    return RegularUsers(cmd, clientMsg, __fd);
}

/*
    @ : * Get Line readed (After Being Reformed(Trimmed Epured))=>FullMessage
        * Extract the first Field From The Message
        * Transform it to ::upper
        * Recognize which Cmd is !
*/

void    MediatorCommand(std::string &FullMessage, int __fd)
{
    std::stringstream stream(FullMessage);
    std::string       ExtractCmd("");
    
    if (std::getline(stream, ExtractCmd, ' ')){
        std::transform(ExtractCmd.begin(), ExtractCmd.end(), ExtractCmd.begin(), ::toupper);
        RecognizeCmd(ExtractCmd, FullMessage, __fd);
    }
}
