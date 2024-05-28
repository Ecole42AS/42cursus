NAME =	fixed_point_nb

SRCS =	main.cpp Fixed.cpp

OBJS = ${SRCS:.cpp=.o}

CPP =	c++

FLAGS =	-Werror -Wextra -Wall -std=c++98

all: $(NAME)

$(NAME): $(OBJS)
	@$(CPP) $(FLAGS) -o $@ $^ && echo "\033[32mCOMPILATION SUCCESSFUL !\033[0m"

%.o: %.cpp
	@$(CPP) $(FLAGS) -c $< -o $@

fclean:
	@rm -f $(OBJS) $(NAME) && echo "Cleaning complete"

re: fclean all

.PHONY: all fclean re
