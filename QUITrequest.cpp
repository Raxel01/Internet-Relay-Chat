/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   QUITrequest.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ta <abait-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 19:00:53 by abait-ta          #+#    #+#             */
/*   Updated: 2024/03/11 20:57:26 by abait-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

// <-  :kort!~u@qk3i8byd6tfyg.irc QUIT Quit
void    QUITmessage(int __fd)
{
    Roomiter iter = GlobalServerData::ServerChannels.begin();
    std::string User = Server::ServerClients.at(__fd).nickname;
    
    std::string response = ":" + User + "!~" + "@" + Server::ServerClients.at(__fd).client_ip + " QUIT " + ": This User Quit \n";
    while (iter != GlobalServerData::ServerChannels.end())
    {
        if ((*iter).IsalreadyMember(Server::ServerClients.at(__fd).nickname) == true)
        {
            DEQUE::iterator Finder = (*iter).IsRegularUser(User);
            if (Finder != (*iter)._Members.end()){
                    BroadcastMessage("", "", iter, response);
                    (*iter)._Members.erase(Finder);
                }
            else if ((*iter).IsMediator(User) == true){
            DEQUE::iterator  OPFINDER = (*iter)._Mediators.begin();
            while (OPFINDER != (*iter)._Mediators.end()){
                if ((*OPFINDER) == User)
                    break;
                OPFINDER++;
            }
            BroadcastMessage("", "", iter, response);
            (*iter)._Mediators.erase(OPFINDER);
        }
        
        if ((*iter).Roomsize() == 0 || (*iter)._Mediators.size() == 0){// if no admin or no member the Channel Will be Destroyed
            GlobalServerData::LastChannelUser = __fd;
        if ((*iter)._Mediators.size() == 0){
            time_t theTime = time(NULL);
            std::string resp = ":" + MYhost::GetHost() + " 999 " + (*iter)._RoomName + " Destroyed RIP : " + ctime(&theTime);
                BroadcastMessage(Server::ServerClients.at(__fd).nickname, "", iter, resp);
        } 
            iter = GlobalServerData::ServerChannels.erase(iter);
            continue ;
        }
            
        }
    iter++;
    }
    //Put Your fucking Bachar Put changes Here
    // close(__fd);
}