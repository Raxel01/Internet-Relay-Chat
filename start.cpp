/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ta <abait-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 11:28:15 by abait-ta          #+#    #+#             */
/*   Updated: 2024/02/23 15:12:49 by abait-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <sstream>


#define    KICK       "KICK"
#define    INVITE     "INVITE"
#define    TOPIC      "TOPIC"
#define    MODE       "MODE"
#define    JOIN       "JOIN"
#define    CONTINUE   "CONTINUE"
#define    PART       "PART"

// const char *CMD[] ={ "KICK", "JOIN", "INVITE", "TOPIC", "CONTINUE"};

class ReforMessage
{
    private:
        static size_t   start;
        static size_t   end;
        static int      flag;
        static int      i;
    public :
        static std::string     FinalMessage;
        static void   GlobalReform(std::string Message);
        static void   TriMessage(std::string &Message);
        static void   CleanMessage(std::string &Message);
};


size_t            ReforMessage::start = 0;
size_t            ReforMessage::end = 0;
int               ReforMessage::flag = 0;
int               ReforMessage::i = -1;
std::string       ReforMessage::FinalMessage;

void    ReforMessage::CleanMessage(std::string &Message){


	std::stringstream ss;
    
    while (Message[++i])
	{
		if (Message[i] == ' ')
			flag = 1;
		if (!(Message[i] == ' '))
		{
			if (flag)
				ss << " ";
			flag = 0;
			ss << Message[i];
			}
		}
    Message = ss.str();
}


void    ReforMessage::TriMessage(std::string &Message){
    start = Message.find_first_not_of(" ");
    end = Message.find_last_not_of(" ");
    
    if (start != std::string::npos && end != std::string::npos){
        Message = Message.substr(start, end - start +1);
    }
}

void    ReforMessage::GlobalReform(std::string Message){
        FinalMessage = Message;
        TriMessage(FinalMessage);
        CleanMessage(FinalMessage);
}

std::string RecognizeCmd(std::string& cmd)
{
         if (cmd.compare(KICK)   == 0)
                return KICK;
    else if (cmd.compare(INVITE) == 0)
                return INVITE;
    else if (cmd.compare(TOPIC)  == 0)
                return TOPIC;
    else if (cmd.compare(MODE)   == 0)
                return (MODE);
        return CONTINUE;
}

void    ChanopCommand(std::string &FullMessage)
{
    std::stringstream stream(FullMessage);
    std::string       ExtractCmd("");
    
    if (std::getline(stream, ExtractCmd, ' ')){
        std::transform(ExtractCmd.begin(), ExtractCmd.end(), ExtractCmd.begin(), ::toupper);
        std::cout << "The command : |" << ExtractCmd << "|";
        // => Recognize the operator  4 CommandS:
        std::cout <<  "==> : " << RecognizeCmd(ExtractCmd) << " :<=="<<std::endl;
    }
}

//Message Grammar ==> |:Prefix cmd param_lis<...>|

#include <unistd.h>

int main (int ac, char **av)
{   
    (void)ac;
    ReforMessage::GlobalReform(av[1]);
    ChanopCommand(ReforMessage::FinalMessage);
    
}