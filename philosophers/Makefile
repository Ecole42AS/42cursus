# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: astutz <astutz@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/04 18:51:15 by astutz            #+#    #+#              #
#    Updated: 2023/08/04 19:17:02 by astutz           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	= $(wildcard *.c)

OBJS	= $(SRCS:%.c=%.o)

NAME	= philo

CC		= gcc
RM		= rm -f

CFLAGS	= -Wall -Wextra -Werror -g3 -lpthread -fsanitize=thread #-fsanitize=address
# TFLAGS	= -lpthread -fsanitize=thread

all:		${NAME}

%.o:	%.c
		${CC} ${CFLAGS} -c $< -o $@

${NAME}:	${OBJS}
		${CC} ${CFLAGS} $^ -o $@

clean:
		${RM} ${OBJS}

fclean:	clean
		${RM} ${NAME}

re:		fclean all

.PHONY:		all bonus clean fclean re