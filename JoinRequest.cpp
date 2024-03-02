/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JoinRequest.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ta <abait-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 06:38:37 by abait-ta          #+#    #+#             */
/*   Updated: 2024/03/02 01:36:14 by abait-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "JoinRequest.hpp"
# include "ChatRoom.hpp"
# include "MessageRecognizer.hpp"


std::vector<ChatRoom>   GlobalServerData::ServerChannels; // all serverchannel

std::string MYhost::GetHost()
{
        char TheHost[256];
        int status;

        status = gethostname(TheHost, sizeof(TheHost));
        if (status == -1){
            std::cout << strerror(errno) << std::endl;
            // exit(1);
            throw std::runtime_error("Trouble when Getting your hostname");
        }
    return (TheHost);
}

void     ExtractChannels(std::string& ClientMsg, Myvector& Channels){
        
        std::stringstream channelstream(ClientMsg);
        std::string channelHolder;

        channelstream >> channelHolder;//Ignore the join command;
        channelHolder.clear();
        channelstream >> channelHolder;//GetchannelsList

        std::stringstream stream(channelHolder); /*<Give My channelList to a stream to Display it>*/
        std::string SingleChannel;

        while (std::getline(stream, SingleChannel, ',')){ //Make Vector of channels;
            Channels.push_back(SingleChannel);
        }
}

void     ExtractKeys(std::string& ClientMsg, Myvector& keys)
{
        std::stringstream keystream(ClientMsg);
        std::string keyHolder;

        keystream >> keyHolder >> keyHolder ; //ignore join and channelList
        keyHolder.clear();
        keystream >>  keyHolder ; //GetKeyList;
        
        std::stringstream stream(keyHolder);
        std::string SingleKey; /*<catch every single key with this >*/

          while (std::getline(stream, SingleKey, ',')){ //Make Vector of keys;
            keys.push_back(SingleKey);
        }
}

//ChatRoom.hpp->MessageRecognizer->joinRequst.hpp->joinRequest.cpp->join.cpp
bool FollowGrammar(std::string &channel)
{
    if (channel.at(0) == '#')
        return true;
    return false;
}

std::string ToUpper(std::string channel)
{
    std::transform(channel.begin(), channel.end(), channel.begin(), ::toupper);
    return (channel);
}

enum ChannelStatus     FindInGlobalChannel(const std::string& SearchFor)
{
    Roomiter iter = GlobalServerData::ServerChannels.begin(); // replace by GlobalServerData::ServerChannels

    while (iter != GlobalServerData::ServerChannels.end()){
        if (ToUpper((*iter).GetRoomname()) == ToUpper(SearchFor))
            return TOBE_JOINED;
        iter++;
    }
    return TOBE_BUILDED;
}

Roomiter FindUsingName(std::string& channelName)
{
    Roomiter it = GlobalServerData::ServerChannels.begin();
    while (it != GlobalServerData::ServerChannels.end())
    {
        if (ToUpper((*it).GetRoomname()) == ToUpper(channelName)){
            return it ;
        }
        it++;
    }
    //Be careful With this return ... // it's ok Because To be Here th channel should be flaged 
    //as Tobejoined so it's finded ;
    return (GlobalServerData::ServerChannels.end());
}

void    BroadcastMessage(std::string user, std::string ChannelName, Roomiter& iter, std::string response){
    // std::map<int ,Client>::iterator GlobaLiter = Server::ServerClients.begin();
    // while (GlobaLiter !=  Server::ServerClients.end()){
        // if ((*iter).IsalreadyMember(GlobaLiter->second.nickname) == true && GlobaLiter->second.nickname != user ){
                // send(GlobaLiter->first, response.c_str(), response.length(), 0);
        // }
        // GlobaLiter++;
    // }
}

void    PassworMatcher(int __fd, std::vector<ChatRoom>::iterator& iter, std::string &user, \
                            std::string &ChannelName, std::string& Key, enum KeyType KeyFlag)
{
    // if ((*iter).keyStatus == true){
    //     if ((*iter)._ChatKey.compare(Key) == 0 && KeyFlag == KEY_PROVIDED){
    //         std::cout << "User added bECAUSE TH KEY match"<< std::endl;
    //             (*iter).Addasmember(user);
    //             /*Send to this user in it fd self*/
    //                 std::string response = ":" + user + "!" + MYhost::GetHost() + " JOIN " + ChannelName + "\n";
    //                 response += ":" + MYhost::GetHost() + " 353 " + user + " = " + ChannelName + " " + (*iter).MembersList() + "\n";
    //                     response += ":" + MYhost::GetHost() + " 366 " + user + " " + ChannelName + " :End of NAMES list";
    //                         // send(__fd, response.c_str(), response.length(), 0);
                            // response.clear();
            //          response = ":" + user + "!" + MYhost::GetHost() + " JOIN " + ChannelName + "\n";;;;;;;;;;;
    //                         BroadcastMessage(user, ChannelName, iter, response); //Broadcast  a new user is comming.
    // }
    //     else{ // Send wrong password
    //                 std::string response = MYhost::GetHost() + " " + "475" + " " + user + " " + ChannelName + ": Wrong Channel Password (+k)";
    //                     // send(__fd, response.c_str(), response.length(), 0);
    //                 }
    //     }
    //         else{
    //                 (*iter).Addasmember(user);
    //                     std::string response = ":" + user + "!" + MYhost::GetHost() + " JOIN " + ChannelName + "\n";
    //                         response += ":" + MYhost::GetHost() + " 353 " + user + " = " + ChannelName + " " + (*iter).MembersList() + "\n";
    //                             response += ":" + MYhost::GetHost() + " 366 " + user + " " + ChannelName + " :End of NAMES list";
    //                                 // send(__fd, response.c_str(), response.length(), 0);
                            // response.clear();
            //          response = ":" + user + "!" + MYhost::GetHost() + " JOIN " + ChannelName + "\n";;;;;;;;;;;
    //                         BroadcastMessage(user, ChannelName, iter, response); //Broadcast  a new user is comming.
    //                                 
    //                     }
    //channel is not invite only so we will acces it with the key
}



void    JoinWithKey(int __fd, std::string &user, std::string &ChannelName, std::string& Key, enum KeyType KeyFlag){   
    
    // //Extract the object with sameName of channel;
    // std::vector<ChatRoom>::iterator iter = FindUsingName(ChannelName);

    // if ((*iter).IsalreadyMember(user) == false){ // if user is current Member 
    //     if ((*iter).IsBanned(user) == false){ //ban or not 
    //         if ((*iter)._Mediators.size() + (*iter)._Members.size() < (*iter)._AllowedUsers){//channel is Full or not 
    //             if ((*iter)._Acces_isInviteOnly == true){    // channel +i avtived
    //                 if ((*iter).IsInviteList(user) == true){ // channel is invite only and User is invited also
    //                         (*iter).Addasmember(user);
    //                 std::string response = ":" + user + "!" + MYhost::GetHost() + " JOIN " + ChannelName + "\n";
    //             response += ":" + MYhost::GetHost() + " 353 " + user + " = " + ChannelName + " " + (*iter).MembersList() + "\n";
    //         response += ":" + MYhost::GetHost() + " 366 " + user + " " + ChannelName + " :End of NAMES list";
    //     // send(__fd, response.c_str(), response.length(), 0);
                    // response.clear();
            //          response = ":" + user + "!" + MYhost::GetHost() + " JOIN " + ChannelName + "\n";;;;;;;;;;;
    //                         BroadcastMessage(user, ChannelName, iter, response); //Broadcast  a new user is comming.
    //     }
    //     else{//1 INVITE ONLY
    //                 std::string response = MYhost::GetHost() + " " + "473" + " " + user + " " + ChannelName + " :Channel is Invite only (+i)" ;            
    //                         // send(__fd, response.c_str(), response.length(), 0);
    //                 }//1
    //     }
    //         else{//2 Password matching [PROVIDED, NOTPROVIDED];
    //                     PassworMatcher(__fd, iter, user, ChannelName, Key, KeyFlag);
    //                     }//2  
    //         }
    //             else{//3 Excedlimit :
    //                         std::string response = MYhost::GetHost() + " " + "471" + " " + user + " " + ChannelName + " :This channel exceeds limits";
    //                             // send(__fd, response.c_str(), response.length(), 0);
    //                         }// 3
    //             }
    //                 else{// 4Banned :
    //                             std::string response = MYhost::GetHost() + " " + "474" + " " + user + " " + ChannelName + " :You are an active ban on this channel";
    //                                 // send(__fd, response.c_str(), response.length(), 0);
    //                             }//4
    //                 }
    //                     else{ //5 alreadyMember :
    //                                 std::string response = MYhost::GetHost() + " " + "443" + " " + user + " " + ChannelName + " :You are already on channel";
    //                                     // send(__fd, response.c_str(), response.length(), 0);
    //                                 } //5
}

void    JoinStart(int __fd, std::string& clientMsg, Myvector& Channels, Myvector& keys)
{
//         int i = -1;
//         while (++i < Channels.size()){
//         try{
//             if (FollowGrammar(Channels.at(i))){
//                 if(FindInGlobalChannel(Channels.at(i)) == TOBE_BUILDED ){
//                     // ChatRoom BuildRoom(Server::ServerClients.at(__fd).nickname, Channels.at(i));
//                         // std::string response = ":" + Server::ServerClients.at(__fd).nickname + "!" + MYhost::GetHost() + " JOIN " + BuildRoom._RoomName + "\n";
//                     // response += ":" + MYhost::GetHost() + " 353 " + Server::ServerClients.at(__fd).nickname + " = " + BuildRoom._RoomName + " " + BuildRoom.MembersList() + "\n";
//                 // response += ":" + MYhost::GetHost() + " 366 " + Server::ServerClients.at(__fd).nickname + " " + BuildRoom._RoomName + " :End of NAMES list";
//             // send(__fd, response.c_str(), response.length(), 0);
//         // GlobalServerData::ServerChannels.push_back(BuildRoom);//Will be changed By My GlobalSerer data attribut 
//     }
//     else{ // TO_BEJOINED With a key given ! Keystatus == 1(INSERT THE CODE GIVED, TRUE || False
//             if (i < keys.size())
//             {
//                 try{
//                         // JoinWithKey(__fd, Server::ServerClients.at(__fd).nickname, Channels.at(i), keys.at(i), KEY_PROVIDED);
//                 }
//                 catch (std::exception& e){
//                                 std::cout << "Exception Throwed and Catched Due to Reason : ";
//                                     std::cout << e.what() << std::endl;
//                 }
//             }
//             else {//a
//                     try{ // Keystatus == true just back you don't have the key 
//                             std::string EmptyPass("");
//                                 // JoinWithKey(__fd ,Server::ServerClients.at(__fd).nickname, Channels.at(i), EmptyPass , NO_KEY_PROVIDED);
//                 }
//                 catch(std::exception& e){
//                             std::cout << "Exception Throwed and Catched Due to Reason : ";
//                                 std::cout << e.what() << std::endl;
//                 }
//                                         }//!aa
//     }
//             }else
//                 throw InvalidChannelName();
//         }catch (InvalidChannelName& e){
//                 // std::string response =  MYhost::GetHost() + " 489 " +  Server::ServerClients.at(__fd).nickname + " " + Channels.at(i) + " :Invalid channel name";
//                     // std::cout << response << std::endl;
//                         e.what();    
//         }
// }
        
}

void    JoinProcessor( std::string& clientMsg, int __fd )
{
        std::vector<std::string> Channels;
        std::vector<std::string> keys;

        ExtractChannels(clientMsg, Channels);   //makeVector of channels
        ExtractKeys(clientMsg, keys);       //MakeVector of Keys
        JoinStart(__fd, clientMsg, Channels, keys);
}

void    JoinMessage(std::string& clientMsg, int __fd){
    
    std::stringstream stream(clientMsg);
    std::string params;
    
    size_t OcuurSpace = std::count(clientMsg.begin(), clientMsg.end(), ' ');
    if(OcuurSpace == 0){
        std::string response = (NumericReplies("localhost", "461", "NICKNAME", "JOIN", ":No enough parameters.")) + \
        NumericReplies("localhost", "999", "NICKNAME", "JOIN", ":<channel>[,<channel>]+ [<key>[,<key>]+]");
        send (__fd, response.c_str(), response.length(), 0);
        return ;
    }
    else {
        JoinProcessor(clientMsg, __fd);
    }
}

const char* InvalidChannelName::what() const throw(){
    return ("");
}