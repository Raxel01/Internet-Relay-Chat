# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abait-ta <abait-ta@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/24 19:18:19 by abait-ta          #+#    #+#              #
#    Updated: 2024/02/24 19:59:01 by abait-ta         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME         =   ircserv

SERVERPATH  =  ./srcs/server

CMDPATH     = ./srcs/commands

SRC         =   Global_main.cpp \
                $(SERVERPATH)/Server.cpp

INCLUDE     =   ./headers/Server.hpp

CXX         =   c++

OBJ = ${SRC:.cpp=.o}

CXXFLAGS    =   -std=c++98 -Wall -Wextra -Werror

all : $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(NAME) && rm $(OBJ)

%.o : %.cpp $(INCLUDE)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean :
	rm -fr $(OBJ)

fclean : clean
	rm -fr $(NAME)

re : fclean all

.PHONY : re fclean clean