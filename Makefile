IRC			= 	ircserv
SRC			=	main.cpp
INCLUDE		=
CXX			= 	c++
OBJ_DIR		=	./objs
OBJ			= 	$(OBJ_DIR)/$(SRC:.cpp=.o)
CFLAGS		= 	-std=c++98 -Wall -Wextra -Werror

all : $(IRC)

$(OBJ_DIR)/%.o : %.cpp $(INCLUDE)
	$(CXX) $(CFLAGS) -c $< -o $@

$(IRC): $(OBJ)
	$(CXX) $(CFLAGS) $(OBJ) -o $(IRC)

clean :
	rm -fr $(OBJ)

fclean : clean
	rm -fr $(IRC)

re : fclean all

.PHONY : re fclean clean