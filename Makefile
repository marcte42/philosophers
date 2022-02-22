# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mterkhoyev <mterkhoyev@student.42.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/17 10:25:07 by mterkhoy          #+#    #+#              #
#    Updated: 2022/02/11 17:10:36 by mterkhoyev       ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC 	= gcc
CFLAGS = -g -Wall -Wextra -Werror

INC_DIR = ./inc

SRCS =		philo.c	\
			parse.c	\
			init.c	\
			run.c	\
			monitor.c	\
			print.c	\
			utils.c	\
			libft.c	\

OBJS = $(addprefix src/, $(SRCS:.c=.o))

.c.o:
	$(CC) $(CFLAGS) -I $(INC_DIR) -c $< -o $(<:.c=.o)

$(NAME): $(OBJS) $(INC_DIR)/philo.h
		$(CC) $(CFLAGS) $(OBJS) -lpthread -o $(NAME)

all: $(NAME)

clean :
	rm -rf $(OBJS)

fclean:	clean
	$(RM) $(NAME)

re:	fclean all

.PHONY:	all clean fclean re
