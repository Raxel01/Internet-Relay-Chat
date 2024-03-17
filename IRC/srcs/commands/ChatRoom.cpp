/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChatRoom.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ta <abait-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 12:30:51 by abait-ta          #+#    #+#             */
/*   Updated: 2024/03/17 21:54:56 by abait-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/ChatRoom.hpp"

std::vector<ChatRoom>   GlobalServerData::ServerChannels; // all serverchannel

std::string MYhost::GetHost()
{
        char TheHost[256];
        int status;

        status = gethostname(TheHost, sizeof(TheHost));
        if (status == -1){
            std::cout << strerror(errno) << std::endl;
            throw std::runtime_error("Trouble when Getting your hostname"); //Pay attention
        }
    return (TheHost);
}

ChatRoom::ChatRoom(){}

int GlobalServerData::LastChannelUser = -1;

ChatRoom::ChatRoom(std::string& Creator, std::string& SetRoomName): _RoomName(SetRoomName), _ChatKey(""){
    // _Members.push_back("@" + Creator);
    _Mediators.push_back("@" + Creator);
    _AllowedUsers = LIMITUSERS;
    TopicStatus = false;
    
    HaveLimitUser = false;//issue Here
    keyStatus = false;
    _Acces_isInviteOnly = false;
    TopicRestriction = true; // Only Admin can set the  Channel Topic
}

/*Don't Forget That IF NO MEDIATOR THE CHANNEL wILL BE DESTROYEED*/
ChatRoom::~ChatRoom(){
    if (GlobalServerData::LastChannelUser != -1){
        time_t theTime = time(NULL);
        std::string response =":" + MYhost::GetHost() + " 999 " + "SaHit ~Good By :> Last Warrior / No Admin ..." + this->_RoomName + "\n";
            response += ":" + MYhost::GetHost() + " 999 " + "Channel Destroyed RIP : " + \
                ctime(&theTime);
                    send(GlobalServerData::LastChannelUser, response.c_str(), response.length(), 0);
                        GlobalServerData::LastChannelUser = -1;
    }
}
void            ChatRoom::getelems(){
    std::cout << "*************************************************************"<< std::endl;
    DEQUE::iterator it = _Mediators.begin();
    
    while (it != _Mediators.end()){
        std::cout << "Mediator : " << *it<< std::endl;
        it++;
    }
    
    std::cout << "^^^^^^^^^^^Mediator^^^^^^^^^" << std::endl;
    
    it = _Members.begin();
    while (it != _Members.end()){
        std::cout << "Members : " << *it << std::endl;
        it++;
    }
    
    std::cout << "^^^^^^^^^^^Members^^^^^^^^^" << std::endl;
    
    it = _BannedUsers.begin();
    while (it != _BannedUsers.end())
    {
        std::cout << "Banned : " << *it << std::endl;
        it++;
    }
    std::cout << "^^^^^^^^^^^^^Banned Users^^^^^^^^^^^^^^"<< std::endl;
    
      it = _InviteList.begin();
    while (it != _InviteList.end())
    {
        std::cout << "INVITED : " << *it<< std::endl;
        it++;
    }
    std::cout << "^^^^^^^^^^^INVITED USERS^^^^^^^^^" << std::endl;
    std::cout << "RoomNAME => " << _RoomName << std::endl;
    
    std::cout << "Keysstatus : ";
    if (keyStatus == true)
        std::cout << " TRUE kEY :|" << _ChatKey << "|"<< std::endl;
    else
        std::cout << "False"<< std::endl;
        
    std::cout << "Users Joined Channel " << _Mediators.size() + _Members.size() << std::endl;
    std::cout << "Acces with Invitation : ";
    if (_Acces_isInviteOnly == true)
        std::cout << "Yes inviteOnly "<< std::endl;
    else
        std::cout << "NO no invitation "<<std::endl;
    std::cout << "tOPICRESTRICTION : ";
        if (TopicRestriction == true)
            std::cout << "true  : Only admin can change Topic"<< std::endl;
        else
            std::cout << "False : All Users can Change topic"<< std::endl;
    std::cout << "LiMITUSERS :";
    if (HaveLimitUser == true)
        std::cout << "True limit Is " << _AllowedUsers << std::endl;
    else
        std::cout << "Default limit " << LIMITUSERS << std::endl;
    std::cout << "*************************************************************"<< std::endl;
}


std::string     ChatRoom::MembersList(){
    
    std::string list(":");
    size_t i = -1;
    while (++i < _Mediators.size()){
        list+= _Mediators.at(i) + " "; 
    }
    i = -1;
    while (++i < _Members.size()){
        list+= _Members.at(i) + " ";
    }
    return list;
}

void    ChatRoom::Addasmember(std::string& newMember){
    this->_Members.push_back(newMember);
}

void    ChatRoom::AddasMediator(std::string &NewMediator){
    this->_Mediators.push_back("@" + NewMediator);
}

bool    ChatRoom::IsInviteList(std::string& TargetUser)
{
    size_t i = -1;
    while (++i < _InviteList.size())
    {
        if (_InviteList.at(i) == TargetUser)
            return true;
    }
    return false;
}

bool    ChatRoom::IsBanned(std::string& IfBanned){
    size_t i = -1;
    while (++i < _BannedUsers.size()){
        if (_BannedUsers.at(i) == IfBanned)
            return true;
    }
    return false;
}

bool    ChatRoom::IsMediator(std::string& MayMediator){
    
    std::string Searchfor("@" + MayMediator);

    size_t i = -1;
    while (++i < _Mediators.size()){
        if (_Mediators.at(i) == Searchfor)
            return true;
    }
    return false;
}

bool    ChatRoom::IsalreadyMember(std::string& MayUser){
    if (IsMediator(MayUser) == true)
        return true;
    size_t i = -1;
    while (++i < _Members.size()){
         if (MayUser.compare(_Members.at(i)) == 0)
            return true;
    }
    return false;
}

std::string&    ChatRoom::GetRoomname(){
       return _RoomName;
}

DEQUE::iterator            ChatRoom::IsRegularUser(std::string User){

    DEQUE::iterator iter = _Members.begin();
    while (iter != _Members.end())
    {
        if (*(iter) == User )
            return iter;
        iter++;
    }
    return _Members.end();
}

size_t          ChatRoom::Roomsize(){
    return (_Members.size() + _Mediators.size());
}


void    ChatRoom::PartMediator(std::string& toPart)
{
    DEQUE::iterator iter = _Mediators.begin();
    
    std::string Admin = "@" + toPart;
    while (iter < _Mediators.end()){
        if (Admin == *iter)
            break ;
        iter++;
    }
    _Mediators.erase(iter);// STOP HERE ... / **-** /
}

std::string    ChatRoom::getTOPIC(){
    return this->_ChatTopic;
}

void            ChatRoom::SetTOPIC(std::string Topic)
{
    _ChatTopic.clear();
    _ChatTopic = Topic;
    TopicStatus = true;
}

void    ChatRoom::BanThisUser(std::string User)
{
    DEQUE::iterator Finder = IsRegularUser(User); 
    if (Finder != _Members.end()){
        _Members.erase(Finder);
        _BannedUsers.push_back(User);
    }
    else if (IsMediator(User) == true)
    {
        DEQUE::iterator  OPFINDER = _Mediators.begin();
        std::string TOBAN("@" + User);
        
        while (OPFINDER != _Mediators.end()){
            if ((*OPFINDER) == TOBAN)
                break;
            OPFINDER++;
        }
        _Mediators.erase(OPFINDER);
        _BannedUsers.push_back(User);
    }
}
/*No check For duplicate Invite implement it on any CODE...*/
void            ChatRoom::AddToInvited(std::string& NewInvited)
{
    _InviteList.push_back(NewInvited);
}

void            ChatRoom::PardonUser(std::string USER){

    DEQUE::iterator  OPFINDER = _BannedUsers.begin(); //I changed Here _Mediator By _BannedUser
    while (OPFINDER != _BannedUsers.end())
    {
        if ((*OPFINDER) == USER)
            break;
        OPFINDER++;
    }
    _BannedUsers.erase(OPFINDER);//User debloqued
}

void            ChatRoom::eraseFromInvList(std::string Invited)
{
    if (this->IsInviteList(Invited) == true)
    {
        DEQUE::iterator iter = _InviteList.begin();
        while(iter != _InviteList.end())
        {
            if (*iter == Invited)
                break;
            iter++;
        }
        _InviteList.erase(iter);
    } 
}

void     ChatRoom::ChannelMode(int __fd){
    
    std::string mode("+n");
    std::string response;
    std::string modeArgs;
    
    if (HaveLimitUser == true){
        modeArgs += std::to_string(_AllowedUsers) + " ";
        mode.push_back('l');
    }
    if (keyStatus == true){
        if (IsMediator(Server::ServerClients.at(__fd).nickname) == true)
            modeArgs += _ChatKey + " ";
        else
            modeArgs += " *** ";
        mode.push_back('k');
    }
    if (_Acces_isInviteOnly == true)
        mode.push_back('i');
    if (TopicRestriction == true)
        mode.push_back('t');
    response = ":" + MYhost::GetHost() + " 324 " + Server::ServerClients.at(__fd).nickname + " " + _RoomName + " " + mode + " " + modeArgs + "\n";
    send (__fd, response.c_str(), response.length(), 0);
}

void           ChatRoom::UpgradeToChanoP(std::string USER)
{
    _Members.erase( IsRegularUser(USER)); // Already checked that the user is not a channop and exist in RegularUserList < = > List
    AddasMediator(USER);
}

//Make an Admin a normal User
void            ChatRoom::ToRegularUser (std::string USER){

    DEQUE::iterator Iter = _Mediators.begin();
    std::string Down("@" + USER);
    
    while (Iter != _Mediators.end()){
        if (*Iter == Down)
            break;
        Iter++;
    }
    if (Iter != _Mediators.end()){
        _Mediators.erase(Iter);
        Addasmember(USER);
    }
}
