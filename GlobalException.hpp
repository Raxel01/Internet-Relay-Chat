/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GlobalException.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abait-ta <abait-ta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 18:16:10 by abait-ta          #+#    #+#             */
/*   Updated: 2024/03/09 15:08:54 by abait-ta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>

class Ex_NOSUCHCHANNEL : public std::exception
{
    public :
        virtual const char* what() const throw();
};

class Ex_CHANOPRIVSNEEDED : public std::exception
{
    public :
        virtual const char* what() const throw();
};

class EX_NOTONCHANNEL : public std::exception
{
     public :
        virtual const char* what() const throw();
};

class EX_USERNOTINCHANNEL : public std::exception
{
    public :
        virtual const char* what() const throw();
    
};

class EX_NOSUCHNICK : public std::exception
{
    public :
        virtual const char *what() const throw();
};

class SELF_KICK :public std::exception
{
    public :
        virtual const char *what() const throw();
};

class EX_ALREADYINCHANNEL : public std::exception{
    public :
        virtual const char *what() const throw();
};

class EX_DUPLICATE_INVITE : public std::exception
{
     public :
        virtual const char *what() const throw();
};

class EX_VALIDINVITE : public std::exception
{
     public :
        virtual const char *what() const throw();
};

class UNKNOW_FLAGS : public std::exception
{
    public :
        virtual const char *what() const throw();
};

class EX_ALREADYCHANOP : public std::exception
{
    public :
        virtual const char *what() const throw();
};

class EX_INVALIDLIMITUSER : public std::exception
{
    public :
        virtual const char *what() const throw();
};