/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MessageRecognizer.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ta <abait-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 12:25:08 by abait-ta          #+#    #+#             */
/*   Updated: 2024/03/12 07:28:24 by abait-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include   "ReforMessage.hpp"
# include   "Commands.hpp" 

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
    else if (cmd.compare(PRIVMSG) == 0){
    std::cout << "Yes Paaaart "<< std::endl;
        PRIVMessage(clientMsg, __fd);
        return (PRIVMSG);
    }
    else if (cmd.compare(QUIT) == 0){
        
        QUITmessage(__fd);
        
    }
    else if (cmd.compare(PONG) != 0){
        std::string response(NumericReplies(MYhost::GetHost(), "421", Server::ServerClients.at(__fd).nickname, cmd, "Unknown command"));
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
            InviteMessage(clientMsg, __fd);
                return INVITE;
    }
    else if (cmd.compare(TOPIC)  == 0){
        TOPICmessage(clientMsg, __fd);
                return TOPIC;
    }
    else if (cmd.compare(MODE)   == 0){
        ModeMessage(clientMsg, __fd);
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
