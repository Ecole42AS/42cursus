# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: astutz <astutz@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/20 18:46:37 by astutz            #+#    #+#              #
#    Updated: 2022/11/27 09:38:02 by astutz           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# NAME	= libftprintf.a
# LIBFT = ./libft/libft.a

# SRCS	= 	ft_printf.c	\
# 			srcs/ft_putptr_fd.c \
# 			srcs/ft_putunbr_fd.c \
# 			srcs/ft_putxnbr_fd.c \
# 			srcs/ft_putxxnbr_fd.c

# OBJS	= ${SRCS:%.c=%.o}

# FLAGS	= -Wall -Wextra -Werror -g

# # $(NAME):
# # 	gcc $(FLAGS) -c $(SRCS) -I ./
# # 	ar rc $(NAME) $(OBJS)

# ${NAME}:	${OBJS}
# 			make -C libft
# 			cp ${LIBFT} .
# 			mv libft.a libftprintf.a
# 			ar rcs ${NAME} ${OBJS}

# all: $(NAME)

# clean:
# 	rm -rf $(OBJS)

# fclean: clean
# 	rm -rf $(NAME)

# re: fclean all

# .PHONY: all clean fclean re

# SRCS	= 	srcs/ft_printf.c	\
# 			srcs/ft_putptr_fd.c \
# 			srcs/ft_putunbr_fd.c \
# 			srcs/ft_putxnbr_fd.c \
# 			srcs/ft_putxxnbr_fd.c

# OBJS	=	${SRCS:.c=.o}

# NAME	=	libftprintf.a

# LIBFT	= libft

# CC		=	gcc

# RM		=	rm -f

# CFLAGS	=	-Wall -Wextra -Werror -g

# .c.o:		${CC} ${CFLAGS} -c $< -o ${<:.c=.o} # -I ${HEADERDIR}

# ${NAME}:	${OBJS}
# 			@make -C $(LIBFT)
# 			@cp libft/libft.a .
# 			@mv libft.a $(NAME)
# 			ar rcs ${NAME} ${OBJS}

# all:		${NAME}

# clean:
# 			${RM} ${OBJS}
# 			@make clean -C $(LIBFT)

# fclean:		clean
# 			${RM} ${NAME}
# 			@$(RM) -f $(LIBFT)/libft.a

# re:			fclean all

# .PHONY:		all clean fclean re

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
NAME = libftprintf.a
LIBFT = ./libft/libft.a
HEADERDIR = ./includes

SRCS	= 	srcs/ft_printf.c  	\
			srcs/ft_putptr.c   	\
			srcs/ft_putunbr.c  	\
			srcs/ft_putxnbr.c  	\
			srcs/ft_putxxnbr.c 	\
			srcs/ft_print_c.c	\
			srcs/ft_print_di.c 	\
			srcs/ft_print_s.c	\
			srcs/ft_print_percent.c

OBJS = ${SRCS:.c=.o}

.c.o:	
	${CC} ${CFLAGS} -c -I ${HEADERDIR} $< -o ${<:.c=.o}

${NAME}:	${OBJS}
			make -C libft
			cp ${LIBFT} .
			mv libft.a libftprintf.a
			ar rcs ${NAME} ${OBJS}

all:	${NAME}

clean: 
	rm -rf ${OBJS}

fclean:	clean
	rm -rf ${NAME}

re: fclean all

.PHONY: all fclean clean re