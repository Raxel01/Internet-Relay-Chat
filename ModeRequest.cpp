/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ModeRequest.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ta <abait-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 17:34:44 by abait-ta          #+#    #+#             */
/*   Updated: 2024/03/10 02:02:40 by abait-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

void    TypeD(char mode, Roomiter& RoomObj, enum MODETYPE CMODETYPE)
{
    if (CMODETYPE == ADD_MODE){
        if (mode == 'i'){
            if ((*RoomObj)._Acces_isInviteOnly == false){
                (*RoomObj).ModeReply += "i";
                (*RoomObj)._Acces_isInviteOnly = true;
            }
        }
        else if (mode == 't'){
            if ((*RoomObj).TopicRestriction == false){
                (*RoomObj).ModeReply += "t";
                (*RoomObj).TopicRestriction = true;
            }
        }
    }
    else if (CMODETYPE == REMOVE_MODE){ // Remove Mode
        if (mode == 'i'){
            if ((*RoomObj)._Acces_isInviteOnly == true){
                (*RoomObj).ModeReply += "i";
                (*RoomObj)._Acces_isInviteOnly = false;
            }
        }
        else if (mode == 't'){
            if ((*RoomObj).TopicRestriction == true){
                (*RoomObj).ModeReply += "t";
                (*RoomObj).TopicRestriction = false;
            }
        } 
    }
}

void    TypeB(int __fd, Roomiter& RoomObj, enum MODETYPE CMODETYPE, std::string AddAsChanop, std::string& response){
    if (IsVictimInServer(AddAsChanop) == false){
        response = ":" + MYhost::GetHost() + " 401 " + Server::ServerClients.at(__fd).nickname + " " + AddAsChanop + " : NO USER WITH THIS NAME IN SERVER\n";
            throw EX_NOSUCHNICK();
     }
     
    if ((*RoomObj).IsalreadyMember(AddAsChanop) == false){
        response = NumericReplies(MYhost::GetHost(), "442", Server::ServerClients.at(__fd).nickname, (*RoomObj)._RoomName , "The user is n't on this channel");
            throw EX_NOTONCHANNEL();
    }
    
    if (CMODETYPE == ADD_MODE){
     if ((*RoomObj).IsMediator(AddAsChanop) == true){
            response = NumericReplies(MYhost::GetHost(), " 999 ", Server::ServerClients.at(__fd).nickname, (*RoomObj)._RoomName , "Unaccepted +o To Already Chanop");
                throw EX_ALREADYCHANOP();
     }
    (*RoomObj).UpgradeToChanoP(AddAsChanop);/*Add The User as channop*/
    (*RoomObj).ModeReply += "o";
    (*RoomObj).ModeArgs+= " " + AddAsChanop + " ";
    }
    
    else if (CMODETYPE == REMOVE_MODE){ 
         if ((*RoomObj).IsMediator(AddAsChanop) == false){
            response = NumericReplies(MYhost::GetHost(), " 999 ", Server::ServerClients.at(__fd).nickname, (*RoomObj)._RoomName , "Unaccepted -o To Non Chanop User");
                throw EX_ALREADYCHANOP();
     }
     /*****STOPED HERE*****/
    (*RoomObj).ToRegularUser(AddAsChanop);
    (*RoomObj).ModeReply += "o";
    (*RoomObj).ModeArgs+= " " + AddAsChanop + " ";
    }
}

void    ExtractArgs(std::string& argString, DEQUE& args){
    
    std::stringstream stream(argString);
    std::string ArgPortion;
    while (std::getline(stream, ArgPortion, ',')){
        args.push_back(ArgPortion);
    }
}

bool    LimitChecker(std::string Argument, int ActiveUser)
{
    size_t NonValidelem = Argument.find_first_not_of("0123456789");
    double Argdouble;
    
    if (NonValidelem != std::string::npos) 
        return false; // There is an element diff to diggits

    Argdouble = std::strtod(Argument.c_str(), NULL);
    if (Argdouble < ActiveUser || Argdouble > 900)
        return false;
    return true;
}

void    TypeC(char mode, int __fd, Roomiter& RoomObj, enum MODETYPE CMODETYPE, std::string Argument, std::string& response)
{
    if (CMODETYPE == ADD_MODE){
        if (mode == 'k'){
            if ((*RoomObj).keyStatus == false ) // add for first time ==> then Go Change
                (*RoomObj).keyStatus = true;
            (*RoomObj)._ChatKey.clear()   ;
            (*RoomObj)._ChatKey = Argument;
            (*RoomObj).ModeReply += "k"   ;
            (*RoomObj).ModeArgs+= " *** " ; // Stoped Here When Addin Key to channel
        }
        else if (mode == 'l'){
            if (LimitChecker( Argument, (*RoomObj).Roomsize() ) == true ){
                if ((*RoomObj).HaveLimitUser == false)
                    (*RoomObj).HaveLimitUser = true;
                  (*RoomObj)._AllowedUsers = std::atoi(Argument.c_str());
                (*RoomObj).ModeReply += "l"   ;
            (*RoomObj).ModeArgs+= " " + Argument + " ";
            }
            else
                {
                    response = ":" + MYhost::GetHost() + " 696 " + Server::ServerClients.at(__fd).nickname + " " + (*RoomObj)._RoomName + " l " + ":Invalid User Limit " + Argument  + " \n";
                        throw EX_INVALIDLIMITUSER();
                    }
        }
    }
    
    else if (CMODETYPE == REMOVE_MODE){
        std::cout << " : : : WA HANNI HENAAA AZAMEEEEEEEL : : : "<< std::endl;
        if (mode == 'k'){
            if ((*RoomObj).keyStatus == true){
            (*RoomObj).keyStatus = false;
            (*RoomObj)._ChatKey.clear();
            (*RoomObj).ModeReply += "k";
            (*RoomObj).ModeArgs+= " *** " ; // Stoped Here When Addin Key to channel
            }
        }
        else if (mode == 'l'){
             if ((*RoomObj).HaveLimitUser == true){
                (*RoomObj).HaveLimitUser = false;
                (*RoomObj).ModeReply += "l"   ;
                (*RoomObj).ModeArgs+= " " + std::to_string((*RoomObj)._AllowedUsers) + " ";
                (*RoomObj)._AllowedUsers = LIMITUSERS;
             }
        } 
    }
}

void    AddChannelMode(Roomiter& RoomObj, int __fd, std::string& CleanMode, std::string& ModeArgument, enum MODETYPE CMODETYPE)
{
    short flag = -1;
    DEQUE   args;
    std::string response;
    
    ExtractArgs(ModeArgument, args);
    while (CleanMode[++flag])
    {
        if (CleanMode[flag] == 'i' || CleanMode[flag] == 't')
            TypeD(CleanMode[flag], RoomObj, CMODETYPE);
        else if (CleanMode[flag] == 'o')
        {
            if (args.size() >= 1){ // there is an argument for o mode
                std::string AddAsChanop = args.at(0);
                try{
                    TypeB(__fd, RoomObj, CMODETYPE, AddAsChanop, response);
                       }catch(std::exception& e)
                       {send(__fd, response.c_str(), response.length(), 0);
                            e.what();
                       }
                args.erase(args.begin());
            }
            else{ // There is not args For required Mode 'o'
                std::string response = ":" + MYhost::GetHost() + " 696 " + Server::ServerClients.at(__fd).nickname + " " + (*RoomObj)._RoomName + " o " + ":Please Specify an arg For 'o' mode"  + " \n";
                    send(__fd, response.c_str(), response.length(), 0);
            }
        }
        else if (CleanMode[flag] == 'k' || CleanMode[flag] == 'l'){
            if (args.size() >= 1){
                response.clear();
                try{
                    TypeC(CleanMode[flag], __fd, RoomObj, CMODETYPE, args.at(0), response);
                }catch(std::exception& e){
                    send(__fd, response.c_str(), response.length(), 0);
                            e.what();
                }
                args.erase(args.begin());
            }
            else{ // There is not args For required Mode 'o'
                std::string response = ":" + MYhost::GetHost() + " 696 " + Server::ServerClients.at(__fd).nickname + " " + (*RoomObj)._RoomName + " "+CleanMode[flag] + " :Please Specify an arg For '" + CleanMode[flag] +"' mode"  + " \n";
                    send(__fd, response.c_str(), response.length(), 0);
            }
        }
    }
}

void    ModeRemover(Roomiter& RoomObj, int __fd, std::string& CleanMode, std::string& ModeArgument, enum MODETYPE CMODETYPE)
{
    short flag = -1;
    DEQUE   args;
    std::string response;

    ExtractArgs(ModeArgument, args);
    while (CleanMode[++flag])
    {
        if (CleanMode[flag] == 'i' || CleanMode[flag] == 't')
            TypeD(CleanMode[flag], RoomObj, CMODETYPE);
        else if (CleanMode[flag] == 'o'){
            if (args.size() >= 1){ // there is an argument for o mode
                std::string RemoveChanop = args.at(0);
                try{
                    TypeB(__fd, RoomObj, CMODETYPE, RemoveChanop, response);
                       }catch(std::exception& e)
                       {send(__fd, response.c_str(), response.length(), 0);
                            e.what();
                       }
                args.erase(args.begin());
            }
            else{ // There is not args For required Mode 'o'
                std::string response = ":" + MYhost::GetHost() + " 696 " + Server::ServerClients.at(__fd).nickname + " " + (*RoomObj)._RoomName + " o " + ":Please Specify an arg For 'o' mode"  + " \n";
                    send(__fd, response.c_str(), response.length(), 0);
            }
        }
        else if (CleanMode[flag] == 'k' || CleanMode[flag] == 'l'){
                response.clear();
                try{
                    TypeC(CleanMode[flag], __fd, RoomObj, CMODETYPE, "", response);
                }catch(std::exception& e){
                    send(__fd, response.c_str(), response.length(), 0);
                            std::cout << e.what() << std::endl;
                }
        }
    }

}

void    ModeProcessor(size_t& OccurSpace, int __fd, std::string& CHANNEL, std::string& ModeArgument, \
         std::string& UnknowFlags, std::string& CleanMode, enum MODETYPE CMODETYPE){
        
    Roomiter    RoomObj;
    std::string response;
    
    RoomObj = FindUsingName( CHANNEL );
    try{
        if (RoomObj == GlobalServerData::ServerChannels.end()){
            response = NumericReplies(MYhost::GetHost(), "403", Server::ServerClients.at(__fd).nickname, CHANNEL, "No such channel");
                throw Ex_NOSUCHCHANNEL();
        }
        if ((*RoomObj).IsalreadyMember(Server::ServerClients.at(__fd).nickname) == false){// check if the command writer is a member on this channel
            response = NumericReplies(MYhost::GetHost(), "442", Server::ServerClients.at(__fd).nickname, CHANNEL, "You are not on this channel");
                throw EX_NOTONCHANNEL();
        }
        //Stop Here 10:23
        if (OccurSpace == 1)//Get the channel mode when [MODE #channel] is seet
            (*RoomObj).ChannelMode(__fd);
        else{
            if ((*RoomObj).IsMediator(Server::ServerClients.at(__fd).nickname) == true)
            {
                switch (CMODETYPE)
                {
                case ADD_MODE:
                    if (UnknowFlags.size() != 0){
                        response = ":" + MYhost::GetHost() + " 472 " +  Server::ServerClients.at(__fd).nickname + " " + UnknowFlags +" :Non Recognized Flags [+/-]{k,l,o,t,i}\n";
                            send(__fd, response.c_str(), response.length(), 0);
                                response.clear();
                    }
                    if (CleanMode.size()){ // IF NO VALID MODESTRING JUST GO OUT
                        AddChannelMode(RoomObj, __fd, CleanMode, ModeArgument, ADD_MODE);
                    }
                    if ((*RoomObj).ModeReply.size())
                    {
                        std::string brcast =":" + Server::ServerClients.at(__fd).nickname + "!~" + Server::ServerClients.at(__fd).username + "@"
                        + Server::ServerClients.at(__fd).client_ip + " MODE " + (*RoomObj)._RoomName + " +" + (*RoomObj).ModeReply + " "+ (*RoomObj).ModeArgs + " \n";
                        BroadcastMessage("", "", RoomObj, brcast);
                        (*RoomObj).ModeReply.clear(); (*RoomObj).ModeArgs.clear();
                    }
                    break;
                case REMOVE_MODE:
                  if (UnknowFlags.size() != 0){
                        response = ":" + MYhost::GetHost() + " 472 " +  Server::ServerClients.at(__fd).nickname + " " + UnknowFlags +" :Non Recognized Flags [+/-]{k,l,o,t,i}\n";
                            send(__fd, response.c_str(), response.length(), 0);
                                response.clear();
                    }//Didn't throw because I should process the CleanMode string
                    if (CleanMode.size()){
                        ModeRemover(RoomObj, __fd, CleanMode, ModeArgument, REMOVE_MODE);  
                    }
                    if ((*RoomObj).ModeReply.size())
                    {
                        std::string brcast =":" + Server::ServerClients.at(__fd).nickname  + "!~" + Server::ServerClients.at(__fd).username + "@"
                        + Server::ServerClients.at(__fd).client_ip + " MODE " + (*RoomObj)._RoomName + " -" + (*RoomObj).ModeReply + " " +(*RoomObj).ModeArgs + " \n";
                        BroadcastMessage("", "", RoomObj, brcast);
                        (*RoomObj).ModeReply.clear(); (*RoomObj).ModeArgs.clear();
                    }
                    break;
                default:
                    response = ":" + MYhost::GetHost() + " 472 " +  Server::ServerClients.at(__fd).nickname + " " + CleanMode + UnknowFlags +" :<modestring> Grammar is not accepted [+/-] First\n";
                    throw   UNKNOW_FLAGS();
                    break;
                }
            //Broadcast hEREEE
            }
            else {
                response = NumericReplies(MYhost::GetHost(), "482", Server::ServerClients.at(__fd).nickname, CHANNEL, "You are not CHANNEL CHANOP");
                    throw Ex_CHANOPRIVSNEEDED();
            }
        }        
    }
    catch (std::exception& e)
    { send(__fd, response.c_str(), response.length(), 0);
         response.clear();
            e.what();
    }
}

bool validFlags(char c){
    return (c == 'o' || c == 'l' || c == 'k' || c == 'i' || c == 't');
}
/*
    @ : Extract Unknow flags in MODE string
    @:  Here is Le3jinna 
*/

void      DataCleaner(std::string& MODE, std::string& UnknowFlags, std::string& CleanMode, enum MODETYPE& CMODETYPE)
{
    short i = -1;
    char  c ;
    std::string Already;
    
    if (MODE[0] == '+' || MODE[0] == '-'){ // Get The modestring 
        CMODETYPE = (MODE[0] == '+') ? ADD_MODE : REMOVE_MODE;
        i++;
    }
    while (MODE[++i])
    {
        c = MODE[i];
        if (c == 'k' || c == 'l' || c == 'o') {
            if (Already.find(c) == std::string::npos){
                Already.push_back(c);
            }
        }
        if (validFlags(c) == false && UnknowFlags.find(c) == std::string::npos)
            UnknowFlags.push_back(c);
        if (validFlags(c) == true && CleanMode.find(c) == std::string::npos)
            CleanMode.push_back(c);
    }
}

void    ModeMessage(std::string& clientMsg, int __fd)
{
    size_t OccurSpace = std::count(clientMsg.begin(), clientMsg.end(), ' ');
    
    if (OccurSpace == 0){
        std::string response = ":" + MYhost::GetHost() + " 461 " + Server::ServerClients.at(__fd).nickname + " MODE " + ": NO ENOUGH PARAMETERS" + "\n" +
            NumericReplies(MYhost::GetHost(), "999", Server::ServerClients.at(__fd).nickname, "MODE", "<CHANNEL> + [+/-]{i|o|t|k|l}");
                send(__fd, response.c_str(), response.length(), 0);
    }
    else
    {
        /* Tooon of Variables **************/
        std::stringstream stream(clientMsg);
        std::string       component;
        std::string       CHANNEL;
        std::string       MODE;
        std::string       ModeArgument;
        std::string       UnknowFlags;
        std::string       CleanMode;
        enum              MODETYPE CMODETYPE = ERROR_MODE;
        short             index = 0;
        /***************************************************/
        
        while (std::getline(stream, component, ' '))
        {
            switch (index){
            case 0:
                component.clear();
                break;
            case 1:
                CHANNEL = component;
                component.clear();
                break;
            case 2:
                MODE = component;
                component.clear();
                break;
            default:
                ModeArgument += component + ",";
                break;
            }
        index++;
        }
        DataCleaner( MODE, \
        UnknowFlags, CleanMode, CMODETYPE);
        
        ModeProcessor(OccurSpace, __fd, CHANNEL, ModeArgument,\
                UnknowFlags, CleanMode, CMODETYPE);
    }
}