EXEC = phonebook
SRC = main.cpp
OBJ = ${SRC:.cpp=.o}
CPP = c++
FLAGS = -Werror -Wextra -Wall -std=c++98

all: ${EXEC}

$(EXEC) : %.cpp
	CPP CFLAGS -o $@ $^

%.o : %.cpp
	CPP FLAGS -c $< -o $@

clean:
	rm -f ${OBJ} ${EXEC}

re: clean all

.PHONY: all clean re