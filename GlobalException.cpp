/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GlobalException.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ta <abait-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 18:16:11 by abait-ta          #+#    #+#             */
/*   Updated: 2024/03/03 11:33:29 by abait-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GlobalException.hpp"

const char* Ex_NOSUCHCHANNEL::what() const throw(){
    return "";
}

const char* Ex_CHANOPRIVSNEEDED::what() const throw(){
    return "";
}

const char* EX_NOTONCHANNEL::what() const throw(){
    return "";
}

const char* EX_USERNOTINCHANNEL::what() const throw(){
    return "";
}

const char * EX_NOSUCHNICK::what() const throw(){
    return "";
}

const char * SELF_KICK::what() const throw(){
    return "";
}

const char * EX_ALREADYINCHANNEL::what() const throw(){
    return "";
}

const char * EX_DUPLICATE_INVITE::what() const throw(){
    return "";
}
