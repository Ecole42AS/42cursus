SOURCES	=	minishell.c \
			lexer/initialize.c \
			lexer/lexer.c \
			lexer/parser.c \
			lexer/infile.c \
			lexer/outfile.c \
			lexer/arg.c \
			lexer/replace_env_var.c \
			heredoc.c \
			signal.c \
			execution/execute.c \
			execution/ft_split.c \
			execution/get_next_line_utils.c \
			execution/pipe.c \
			execution/get_next_line.c \
			execution/generations.c \
			execution/creator.c \
			builtins/ft_cd.c \
			builtins/ft_env.c \
			builtins/ft_export.c \
			builtins/ft_unset.c \
			builtins/ft_echo.c \
			builtins/ft_pwd.c \
			enviro.c \
			exit.c \
			error.c \
			lexer/replace_env_var_utils.c \
			lexer/lexer_utils.c

OBJECTS	= $(SOURCES:.c=.o)

CC		= gcc #-g3 -fsanitize=address
CFLAGS	= -Wall -Wextra -Werror -D_GNU_SOURCE
export LDFLAGS="-L${HOME}/.brew/opt/readline/lib"

RM		= rm -f

NAME	= minishell

all:	${NAME}

%.o:	%.c
		${CC} ${CFLAGS} -c -o $@ $<

${NAME}:	${OBJECTS}
		@${MAKE} -C libft all
		${CC} ${CFLAGS} ${LDFLAGS} -lreadline -o $@ $^ -L./libft -lft

libft:
		make -C libft -s

clean:
		make clean -C libft -s
		${RM} ${OBJECTS}

fclean:		clean
		make fclean -C libft -s
		${RM} ${NAME}

re:		fclean all

.PHONY:	libft all bonus clean fclean re
