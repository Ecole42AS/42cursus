# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: astutz <astutz@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/05 14:11:43 by astutz            #+#    #+#              #
#    Updated: 2023/08/01 10:41:10 by astutz           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	= 	draw.c			\
			errors_free.c	\
			fdf.c 			\
			graphic.c 		\
			hook.c 			\
			convert.c 		\
			colors.c 		\
			parsing.c

OBJS	= ${SRCS:.c=.o}

NAME 	= fdf

CC 		= gcc

RM		= rm -f

CFLAGS	= -Wall -Wextra -Werror -g -w

%.o: 				%.c
					${CC} ${CFLAGS} -Ilibft -I./minilibx -c $? -o $@

${NAME}:			${OBJS}
					@make -C libft
					@make -C minilibx
					${CC} ${CFLAGS} $^ -Llibft -lft -L./minilibx -lmlx -framework OpenGL -framework AppKit -o ${NAME}

libft/libft.a:
					@make -C libft

minilibx/libmlx.a:
					@make -C minilibx

all:	${NAME}

clean:
					${RM} $(OBJS)
					@make -C libft clean
					@make -C minilibx clean

fclean:				clean
					${RM} fdf libft/libft.a
					@make -C libft fclean
					@make -C minilibx fclean

re: 				fclean all

.PHONY:				all  clean fclean re