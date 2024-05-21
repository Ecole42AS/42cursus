EXEC = phonebook
SRC = main.cpp Contact.cpp
OBJ = ${SRC:.cpp=.o}
CPP = c++
FLAGS = -Werror -Wextra -Wall -std=c++98

all: ${EXEC}

${EXEC}: ${OBJ}
	${CPP} ${FLAGS} -o $@ $^

%.o: %.cpp
	${CPP} ${FLAGS} -c $< -o $@

fclean:
	rm -f ${OBJ} ${EXEC}

re: fclean all

.PHONY: all fclean re