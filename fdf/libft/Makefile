# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: astutz <astutz@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/30 18:24:25 by astutz            #+#    #+#              #
#    Updated: 2023/07/30 18:29:27 by astutz           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
			ft_strlen.c ft_toupper.c ft_tolower.c ft_atoi.c ft_split.c \
			ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
			ft_strncmp.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c \
			ft_strchr.c ft_strrchr.c ft_memchr.c ft_memcmp.c ft_strnstr.c \
			ft_strlcpy.c ft_strlcat.c ft_calloc.c ft_strdup.c ft_substr.c \
			ft_strjoin.c ft_strtrim.c ft_strmapi.c ft_striteri.c ft_itoa.c \
			ft_printf.c  	\
			ft_putptr.c   	\
			ft_putunbr.c  	\
			ft_putxnbr.c  	\
			ft_putxxnbr.c 	\
			ft_print_c.c	\
			ft_print_di.c 	\
			ft_print_s.c	\
			ft_print_percent.c \
			get_next_line.c get_next_line_utils.c \

OBJS	=	${SRCS:.c=.o}

NAME	=	libft.a

CC		=	gcc

RM		=	rm -f

CFLAGS	=	-Wall -Wextra -Werror -g

.c.o:		${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}:	${OBJS}
			ar rcs ${NAME} ${OBJS}

all:		${NAME}

clean:
			${RM} ${OBJS}

fclean:		clean
			${RM} ${NAME}

re:			fclean all

.PHONY:		all clean fclean re