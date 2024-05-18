# SRC =	main.cpp
#  	# PhoneBook.cpp 
# 	# 	Contact.cpp

# EXEC = phonebook
# OBJ = ${SRC:.cpp=.o}
# CPP = c++
# FLAGS = -Werror -Wextra -Wall -std=c++98

# all: ${EXEC}

# ${EXEC} :  ${OBJ}
# 	${CPP} ${FLAGS} -o $@ $^

# %.o : %.cpp
# 	${CPP} ${FLAGS} -c $< -o $@

# clean:
# 	rm -f ${OBJ} ${EXEC}

# re: clean all

# .PHONY: all clean re

# print:
#     @echo "SRC = ${SRC}"
#     @echo "OBJ = ${OBJ}"

SRC = main.cpp
OBJ = ${SRC:.cpp=.o}
EXEC = main
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