# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: astutz <astutz@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/28 14:22:23 by astutz            #+#    #+#              #
#    Updated: 2022/11/20 11:10:03 by astutz           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRCS =		ft_isdigit.c \
			ft_isalnum.c \
			ft_isascii.c \
			ft_strlen.c \
			ft_atoi.c \
			ft_isalpha.c \
			ft_isprint.c \
			ft_toupper.c \
			ft_tolower.c \
			ft_memcpy.c \
			ft_memmove.c \
			ft_memchr.c \
			ft_memcmp.c \
			ft_memset.c \
			ft_strlcat.c \
			ft_strlcpy.c \
			ft_bzero.c \
			ft_strncmp.c \
			ft_strrchr.c \
			ft_strchr.c \
			ft_calloc.c \
			ft_strnstr.c \
			ft_strdup.c \
			ft_substr.c \
			ft_strjoin.c \
			ft_strtrim.c \
			ft_itoa.c \
			ft_strmapi.c \
			ft_striteri.c \
			ft_putchar_fd.c \
			ft_putstr_fd.c \
			ft_putendl_fd.c \
			ft_putnbr_fd.c \
			ft_split.c

BNS_SRCS =	ft_lstnew.c \
			ft_lstadd_front.c \
			ft_lstsize.c \
			ft_lstlast.c \
			ft_lstadd_back.c \
			ft_lstdelone.c \
			ft_lstclear.c \
			ft_lstiter.c \
			ft_lstmap.c 

OBJS = $(SRCS:.c=.o)

BNS_OBJS	= $(BNS_SRCS:%.c=%.o)

FLAGS = -Wall -Wextra -Werror -g

$(NAME) : $(OBJS)
	gcc $(FLAGS) -c $(SRCS) -I./
	ar rc $(NAME) $(OBJS)

all : $(NAME)

bonus: $(NAME)
	gcc $(FLAGS) -c $(BNS_SRCS) -I ./
	ar rc $(NAME) $(BNS_OBJS)

clean :
	rm -f $(OBJS) $(BNS_OBJS)

fclean	:	clean
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re