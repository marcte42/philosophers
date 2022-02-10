# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mterkhoy <mterkhoy@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/17 10:25:07 by mterkhoy          #+#    #+#              #
#    Updated: 2022/02/10 16:25:55 by mterkhoy         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC 	= gcc
CFLAGS = -g -Wall -Wextra -Werror

INC_DIR = ./includes
LIB_DIR = ./libft

SRCS =		philo.c	\
			
OBJS = $(addprefix srcs/, $(SRCS:.c=.o))

.c.o:
	$(CC) $(CFLAGS) -I includes -I libft -c $< -o $(<:.c=.o) 

$(NAME): $(OBJS) $(INC_DIR)/philo.h
		make -s -C $(LIB_DIR)
		$(CC) $(CFLAGS) $(OBJS) -L$(LIB_DIR) -lft -o $(NAME)

all: $(NAME)

clean :
	make clean -s -C $(LIB_DIR)
	rm -rf $(OBJS)

fclean:	clean
	$(RM) libft/libft.a
	$(RM) $(NAME)

re:	fclean all

.PHONY:	all clean fclean re
