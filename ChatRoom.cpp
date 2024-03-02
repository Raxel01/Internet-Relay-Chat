/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChatRoom.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ta <abait-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 12:30:51 by abait-ta          #+#    #+#             */
/*   Updated: 2024/03/02 03:57:12 by abait-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ChatRoom.hpp"


ChatRoom::ChatRoom(){}

ChatRoom::~ChatRoom(){}

ChatRoom::ChatRoom(std::string& Creator, std::string& SetRoomName): _RoomName(SetRoomName), _ChatKey(""){
    // _Members.push_back("@" + Creator);
    _Mediators.push_back("@" + Creator);
    _AllowedUsers = 150;
    keyStatus = false;
    _Acces_isInviteOnly = false;
}

void            ChatRoom::getelems(){
    DEQUE::iterator it = _Mediators.begin();
    
    while (it != _Mediators.end()){
        std::cout << "Mediator : " << *it<< std::endl;
        it++;
    }
    
    std::cout << "^^^^^^^^^^^Mediator^^^^^^^^^" << std::endl;
    
    it = _Members.begin();
    while (it != _Members.end()){
        std::cout << "Members : " << *it<< std::endl;
        it++;
    }
    
    std::cout << "^^^^^^^^^^^Members^^^^^^^^^" << std::endl;
    
    it = _BannedUsers.begin();
    while (it != _BannedUsers.end())
    {
        std::cout << "Banned : " << *it<< std::endl;
        it++;
    }
    std::cout << "^^^^^^^^^^^^^Banned Users^^^^^^^^^^^^^^"<< std::endl;
    std::cout << "RoomNAME => " << _RoomName << std::endl;
    std::cout << "Keysstatus : " << keyStatus << std::endl;  
    std::cout << "Users Joined Channel " << _Mediators.size() + _Members.size() << std::endl;
    std::cout << "_____________________________________________________________"<< std::endl;
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

const std::string&    ChatRoom::GetRoomname(){
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
        while (OPFINDER != _Mediators.end())
        {
            if ((*OPFINDER) == User)
                break;
            OPFINDER++;
        }
        _Mediators.erase(OPFINDER);
        _BannedUsers.push_back(User);
    }
}