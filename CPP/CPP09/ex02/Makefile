NAME =	PmergeMe

SRCS = $(wildcard *.cpp)

OBJS = ${SRCS:.cpp=.o}

CPP =	c++

FLAGS = -Werror -Wextra -Wall -std=c++98 -g -fsanitize=address

GREEN = \033[32m

RESET = \033[0m

all: $(NAME)

$(NAME): $(OBJS)
	@$(CPP) $(FLAGS) -o $@ $^ && echo "$(GREEN)COMPILATION SUCCESSFUL !$(RESET)"

%.o: %.cpp
	@$(CPP) $(FLAGS) -c $< -o $@

clean:
	@rm -f $(OBJS)
	@echo "$(GREEN)Cleaning objects complete$(RESET)"

fclean:
	@rm -f $(OBJS) $(NAME)
	@echo "$(GREEN)Cleaning complete$(RESET)"

re: fclean all

.PHONY: all fclean re