# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbachar <mbachar@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/24 19:18:19 by abait-ta          #+#    #+#              #
#    Updated: 2024/03/05 05:00:01 by mbachar          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME         =   ircserv

SERVERPATH  =  ./srcs/server

CMDPATH     = ./srcs/commands

SRC         =   main.cpp \
                $(SERVERPATH)/Server.cpp \
                $(SERVERPATH)/Client.cpp \
                $(SERVERPATH)/utils.cpp

INCLUDE     =   ./headers/Server.hpp ./headers/Client.hpp

CXX         =   c++

OBJ = ${SRC:.cpp=.o}

CXXFLAGS    =   -std=c++98 -Wall -Wextra -Werror -g -fsanitize=address

all : $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(NAME)

%.o : %.cpp $(INCLUDE)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean :
	rm -fr $(OBJ)

fclean : clean
	rm -fr $(NAME)

re : fclean all

.PHONY : re fclean clean