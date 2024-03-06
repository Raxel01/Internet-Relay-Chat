/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   KickRequest.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ta <abait-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 01:18:43 by abait-ta          #+#    #+#             */
/*   Updated: 2024/03/06 04:14:17 by abait-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include "JoinRequest.hpp"
#include "ChatRoom.hpp"

void                ExtractVictims(std::string& userList, std::vector<std::string>& Victims);
void                KickExecutor(std::string&channelName , Roomiter& iter, int __fd, \
                    std::vector<std::string>& Victims, std::string& reason);
bool                IsVictimInServer(std::string Name);
bool                SelfKick(std::string& Mediator, std::string& Victim);
void                KickMessage(std::string& clientMsg, int __fd);
void                KickProcessor(std::string& channelName, std::string& userList, \
                    int __fd, std::string& Reason);