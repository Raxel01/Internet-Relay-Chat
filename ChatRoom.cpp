/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ChatRoom.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ta <abait-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 12:30:51 by abait-ta          #+#    #+#             */
/*   Updated: 2024/02/26 14:46:43 by abait-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ChatRoom.hpp"

ChatRoom::ChatRoom(){}

ChatRoom::~ChatRoom(){}

ChatRoom::ChatRoom(std::string& Creator, std::string& SetRoomName): _RoomName(SetRoomName){
     KeyState = false;
    _Members.push_back(Creator);
    _Mediators.push_back(Creator);
}

const std::string&    ChatRoom::GetRoomname(){
    return _RoomName;
}

bool                  ChatRoom::GetKeyState(){
    return KeyState;
}