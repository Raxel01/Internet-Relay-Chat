IRC			= 	ircserv

SRC			=	main.cpp \
				./srcs/server/Server.cpp

INCLUDE		=	./headers/Server.hpp

CXX			= 	c++

OBJ_DIR		=	/Users/$(USER)/Desktop/Internet-Relay-Chat/objs

OBJ			= 	$(OBJ_DIR)/$(SRC:.cpp=.o)

CXXFLAGS	= 	-std=c++98 -Wall -Wextra -Werror

all : $(IRC)

$(OBJ_DIR)/%.o : %.cpp $(INCLUDE)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(IRC): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(IRC)

clean :
	rm -fr $(OBJ)

fclean : clean
	rm -fr $(IRC)

re : fclean all

.PHONY : re fclean clean