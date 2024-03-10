/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PRIVmsgRequest.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ta <abait-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 02:56:00 by abait-ta          #+#    #+#             */
/*   Updated: 2024/03/10 07:35:32 by abait-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

void        FullTargetList(std::string& TargetList, DEQUE& Targets)
{
    std::stringstream stream(TargetList);
    std::string Holder;
    
    while(std::getline(stream, Holder, ',')){
        Targets.push_back(Holder);
    }
}

void    MessageDelivery(DEQUE& Targets, int __fd, std::string& Message)
{
    size_t i (0);
    Roomiter Finder;
    std::string response;
    
    while (i < Targets.size())
    {
        std::string Elem = Targets.at(i);
        if (Elem.at(0) == '#'){ // oPERATE CHANNEL
            Finder = FindUsingName(Targets.at(i));
            try
            {
                if (Finder == GlobalServerData::ServerChannels.end()){
                    response = NumericReplies(MYhost::GetHost(), "403", Server::ServerClients.at(__fd).nickname, Targets.at(i), "No such channel");
                        throw Ex_NOSUCHCHANNEL();
                }
                if ((*Finder).IsalreadyMember(Server::ServerClients.at(__fd).nickname) == false){// check if the command writer is a member on this channel first
                    response = NumericReplies(MYhost::GetHost(), "442", Server::ServerClients.at(__fd).nickname, Targets.at(i), "Can't sent to channel (+n)");
                        throw EX_NOTONCHANNEL();
                }
            response = ":"+ Server::ServerClients.at(__fd).nickname + "!~" + Server::ServerClients.at(__fd).username + "@" +
            Server::ServerClients.at(__fd).client_ip + " PRIVMSG " + Targets.at(i) + " :" + Message + " \n";
            BroadcastMessage( Server::ServerClients.at(__fd).nickname ,"", Finder, response);
            response.clear();   
            }
            catch(const std::exception& e)
            { send(__fd, response.c_str(), response.length(), 0);
                    response.clear();
                        e.what();
            }
            
        }
        else{ // operate with User
            
            std::cout << "From " << __fd << " TO USER :  "<< Message << std::endl;
        }
        
        i++;
    }       
}
        
void        PRIVMessage(std::string& clientMsg, int __fd)
{
      size_t OccurSpace = std::count(clientMsg.begin(), clientMsg.end(), ' ');
    
    if (OccurSpace == 0){
        std::string response = ":" + MYhost::GetHost() + " 411 " + Server::ServerClients.at(__fd).nickname + " PRIVMSG " + ": NO RECIPIENT GIVEN" + "\n" +
            NumericReplies(MYhost::GetHost(), "999", Server::ServerClients.at(__fd).nickname, "PRIVMSG", "<target[channel,USER]...> [<Message>]");
            send(__fd, response.c_str(), response.length(), 0);
    }
    else if (OccurSpace == 1){
        std::string response = ":" + MYhost::GetHost() + " 412 " + Server::ServerClients.at(__fd).nickname + " PRIVMSG " + ": no text to send" + "\n" +
            NumericReplies(MYhost::GetHost(), "999", Server::ServerClients.at(__fd).nickname, "PRIVMSG", "<target[channel,|,USER]...> [<Message>]");
                send(__fd, response.c_str(), response.length(), 0);
    }
    else
    {
        std::stringstream stream(clientMsg);
        std::string       component;
        std::string       TargetList;
        std::string       Message;
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
                TargetList = component;
                break;
            default:
                Message += component + " ";
                break;
            }
        index++;
        }
        DEQUE Targets;
        FullTargetList(TargetList, Targets);
        /*Used to call it processor :)*/
        MessageDelivery(Targets, __fd, Message);
    }
    
}