# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbachar <mbachar@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/24 19:18:19 by abait-ta          #+#    #+#              #
#    Updated: 2024/03/14 02:19:47 by mbachar          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#####################################################
#					Mandatory Part					#
#####################################################
MAN_NAME		=	ircserv

MAN_SERVERPATH	=	./mandatory/srcs/server

MAN_CMDPATH		=	./mandatory/srcs/commands

MAN_HEAD		=	./mandatory/headers

MAN_SRC			=	./mandatory/main.cpp \
					$(MAN_SERVERPATH)/Server.cpp \
					$(MAN_SERVERPATH)/Client.cpp \
					$(MAN_SERVERPATH)/utils.cpp \
					$(MAN_CMDPATH)/ChatRoom.cpp \
					$(MAN_CMDPATH)/GlobalException.cpp \
					$(MAN_CMDPATH)/InviteRequest.cpp \
					$(MAN_CMDPATH)/JoinRequest.cpp \
					$(MAN_CMDPATH)/KickRequest.cpp \
					$(MAN_CMDPATH)/MessageRecognizer.cpp \
					$(MAN_CMDPATH)/ModeRequest.cpp \
					$(MAN_CMDPATH)/PartRequest.cpp \
					$(MAN_CMDPATH)/PRIVmsgRequest.cpp \
					$(MAN_CMDPATH)/QUITrequest.cpp \
					$(MAN_CMDPATH)/ReforMessage.cpp \
					$(MAN_CMDPATH)/TOPICrequest.cpp

MAN_INCLUDE		=	$(MAN_HEAD)/Server.hpp $(MAN_HEAD)/Client.hpp $(MAN_HEAD)/ChatRoom.hpp $(MAN_HEAD)/Commands.hpp $(MAN_HEAD)/GlobalException.hpp $(MAN_HEAD)/ReforMessage.hpp

MAN_OBJ			=	${MAN_SRC:.cpp=.o}

#####################################################
#					Bonus	Part					#
#####################################################
BONUS_NAME			=	ircserv_bonus

BONUS_SERVERPATH	=	./bonus/srcs/server

BONUS_BOTPATH		=	./bonus/srcs/bot

BONUS_CMDPATH		=	./bonus/srcs/commands

BONUS_SRC			=	./mandatory/main.cpp \
						$(BONUS_SERVERPATH)/Server.cpp \
						$(BONUS_SERVERPATH)/Client.cpp \
						$(BONUS_SERVERPATH)/utils.cpp \
						$(BONUS_CMDPATH)/ChatRoom.cpp \
						$(BONUS_CMDPATH)/GlobalException.cpp \
						$(BONUS_CMDPATH)/InviteRequest.cpp \
						$(BONUS_CMDPATH)/JoinRequest.cpp \
						$(BONUS_CMDPATH)/KickRequest.cpp \
						$(BONUS_CMDPATH)/MessageRecognizer.cpp \
						$(BONUS_CMDPATH)/ModeRequest.cpp \
						$(BONUS_CMDPATH)/PartRequest.cpp \
						$(BONUS_CMDPATH)/PRIVmsgRequest.cpp \
						$(BONUS_CMDPATH)/QUITrequest.cpp \
						$(BONUS_CMDPATH)/ReforMessage.cpp \
						$(BONUS_CMDPATH)/TOPICrequest.cpp \
						$(BONUS_BOTPATH)/Bot.cpp

BONUS_INCLUDE		=	$(BONUS_HEAD)/Server.hpp $(BONUS_HEAD)/Client.hpp $(BONUS_HEAD)/Bot.hpp $(BONUS_HEAD)/ChatRoom.hpp $(BONUS_HEAD)/Commands.hpp $(BONUS_HEAD)/GlobalException.hpp $(BONUS_HEAD)/ReforMessage.hpp

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
