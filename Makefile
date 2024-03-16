# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abait-ta <abait-ta@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/24 19:18:19 by abait-ta          #+#    #+#              #
#    Updated: 2024/03/15 17:15:47 by abait-ta         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#####################################################
#					Mandatory Part					#
#####################################################
NAME		=	ircserv

SERVERPATH	=	./IRC/srcs/server

BOTPATH			=	./IRC/srcs/bot

CMDPATH		=	./IRC/srcs/commands

HEADERS		=	./IRC/headers

SRC			=	./IRC/main.cpp \
					$(SERVERPATH)/Server.cpp \
					$(SERVERPATH)/Client.cpp \
					$(SERVERPATH)/utils.cpp \
					$(CMDPATH)/ChatRoom.cpp \
					$(CMDPATH)/GlobalException.cpp \
					$(CMDPATH)/InviteRequest.cpp \
					$(CMDPATH)/JoinRequest.cpp \
					$(CMDPATH)/KickRequest.cpp \
					$(CMDPATH)/MessageRecognizer.cpp \
					$(CMDPATH)/ModeRequest.cpp \
					$(CMDPATH)/PartRequest.cpp \
					$(CMDPATH)/PRIVmsgRequest.cpp \
					$(CMDPATH)/QUITrequest.cpp \
					$(CMDPATH)/ReforMessage.cpp \
					$(CMDPATH)/TOPICrequest.cpp \
					$(BOTPATH)/Bot.cpp

INCLUDE		=	$(HEADERS)/Server.hpp $(HEADERS)/Client.hpp $(CMDPATH)/ChatRoom.hpp $(HEADERS)/Commands.hpp $(HEADERS)/GlobalException.hpp $(HEADERS)/ReforMessage.hpp $(HEADERS)/Bot.hpp

OBJ			=	${SRC:.cpp=.o}

#####################################################
CXX				=	c++

CXXFLAGS		=	-std=c++98 -Wall -Wextra -Werror

#####################################################
#					Mandatory Part					#
#####################################################
all : $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(NAME)

%.o : %.cpp $(INCLUDE)
	$(CXX) $(CXXFLAGS) -c $< -o $@

#####################################################
clean :
	rm -fr $(OBJ)

fclean : clean
	rm -fr $(NAME)

re : fclean all

.PHONY : re fclean clean

#####################################################
