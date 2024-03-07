/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ModeRequest.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ta <abait-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 17:33:07 by abait-ta          #+#    #+#             */
/*   Updated: 2024/03/07 18:17:33 by abait-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ChatRoom.hpp"

enum MODETYPE
{
    REMOVE_MODE = 0,
    ADD_MODE,
    ERROR_MODE,
};

void    ModeMessage(std::string& clientMsg, int __fd);
