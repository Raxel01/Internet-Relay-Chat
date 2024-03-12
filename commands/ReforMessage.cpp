/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ReforMessage.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ta <abait-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 12:16:29 by abait-ta          #+#    #+#             */
/*   Updated: 2024/03/12 13:47:07 by abait-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/ReforMessage.hpp"


size_t            ReforMessage::start = 0;
size_t            ReforMessage::end = 0;
int               ReforMessage::flag = 0;
int               ReforMessage::i = -1;
std::string       ReforMessage::FinalMessage;

void    ReforMessage::CleanMessage(){
	
    std::stringstream ss;
    
    while (FinalMessage[++i])
	{
		if (FinalMessage[i] == ' ')
			flag = 1;
		if (!(FinalMessage[i] == ' '))
		{
			if (flag)
				ss << " ";
			flag = 0;
			ss << FinalMessage[i];
			}
	}
    FinalMessage.clear();
    FinalMessage = ss.str();
    ss.clear();
}

void    ReforMessage::TriMessage(){
    
    start = FinalMessage.find_first_not_of(' ');
    end = FinalMessage.find_last_not_of(' ');
    
    if (start != std::string::npos && end != std::string::npos){
        FinalMessage = FinalMessage.substr(start, end - start + 1);
    }
}

void    ReforMessage::Reinitializer()
{
    start = 0;
    end = 0;
    flag = 0;
    i = -1;
    FinalMessage.clear();
}

void    ReforMessage::removeCRLF(){

    // LimeChat end message With //\r\n
    size_t newlinePos = FinalMessage.find('\n');
    if (newlinePos != std::string::npos){
        if (newlinePos != 0){ // == 0 When type Entrer in nc
          if (FinalMessage.at(newlinePos - 1) == '\r')
            FinalMessage.erase(newlinePos - 1);// this .....\r\n erase it => LimeChat;
          else
            FinalMessage.erase(newlinePos); //this .....\n erase it netcat;
        }
        else{
            FinalMessage.clear();
            FinalMessage = "";
        }
            
    }
}

void    ReforMessage::GlobalReform(std::string Message){
        Reinitializer();
        FinalMessage = Message;
        removeCRLF();
        TriMessage();
        CleanMessage();
}
