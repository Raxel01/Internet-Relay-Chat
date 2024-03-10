# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbachar <mbachar@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/24 19:18:19 by abait-ta          #+#    #+#              #
#    Updated: 2024/03/09 22:49:19 by mbachar          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#####################################################
#					Mandatory Part					#
#####################################################
MAN_NAME		=	ircserv

MAN_SERVERPATH	=	./mandatory/srcs/server

MAN_CMDPATH		=	./mandatory/srcs/commands

MAN_SRC			=	./mandatory/main.cpp \
					$(MAN_SERVERPATH)/Server.cpp \
					$(MAN_SERVERPATH)/Client.cpp \
					$(MAN_SERVERPATH)/utils.cpp

MAN_INCLUDE		=	./mandatory/headers/Server.hpp ./mandatory/headers/Client.hpp

MAN_OBJ			=	${MAN_SRC:.cpp=.o}

#####################################################
#					Bonus	Part					#
#####################################################
BONUS_NAME			=	ircserv_bonus

BONUS_SERVERPATH	=	./bonus/srcs/server

BONUS_BOTPATH		=	./bonus/srcs/bot

BONUS_CMDPATH		=	./bonus/srcs/commands

BONUS_SRC			=	./bonus/main.cpp \
						$(BONUS_SERVERPATH)/Server.cpp \
						$(BONUS_SERVERPATH)/Client.cpp \
						$(BONUS_SERVERPATH)/utils.cpp \
						$(BONUS_BOTPATH)/Bot.cpp

BONUS_INCLUDE		=	./bonus/headers/Server.hpp ./bonus/headers/Client.hpp ./bonus/headers/Bot.hpp

BONUS_OBJ			=	${BONUS_SRC:.cpp=.o}

#####################################################
CXX				=	c++

CXXFLAGS		=	-std=c++98 -Wall -Wextra -Werror -g -fsanitize=address

#####################################################
#					Mandatory Part					#
#####################################################
all : $(MAN_NAME)

$(MAN_NAME): $(MAN_OBJ)
	$(CXX) $(CXXFLAGS) $(MAN_OBJ) -o $(MAN_NAME)

%.o : %.cpp $(MAN_INCLUDE)
	$(CXX) $(CXXFLAGS) -c $< -o $@

#####################################################
#					Bonus	Part					#
#####################################################
bonus : $(BONUS_NAME)

$(BONUS_NAME): $(BONUS_OBJ)
	$(CXX) $(CXXFLAGS) $(BONUS_OBJ) -o $(BONUS_NAME)

%.o : %.cpp $(BONUS_INCLUDE)
	$(CXX) $(CXXFLAGS) -c $< -o $@

#####################################################
clean :
	rm -fr $(MAN_OBJ)
	rm -fr $(BONUS_OBJ)

fclean : clean
	rm -fr $(MAN_NAME)
	rm -fr $(BONUS_NAME)

re : fclean all

.PHONY : re fclean clean

#####################################################
