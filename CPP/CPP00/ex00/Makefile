SRC = megaphone.cpp
OBJ = ${SRC:.cpp=.o}
EXEC = megaphone
CPP = c++
FLAGS = -Wall -Wextra -Werror -std=c++98 

all: ${EXEC}

${EXEC} :  ${OBJ}
	${CPP} ${FLAGS} -o $@ $^

%.o : %.cpp
	${CPP} ${FLAGS} -c $< -o $@

clean:
	rm -f ${OBJ} ${EXEC}

fclean: clean
	rm -f $(EXEC)

re: fclean all

.PHONY: all clean fclean re