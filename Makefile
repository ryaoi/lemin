# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ryaoi <ryaoi@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/01/30 16:48:59 by ryaoi             #+#    #+#              #
#    Updated: 2017/05/22 17:45:19 by ryaoi            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= lem-in

DIR_LIB	= libft

LIBFT	= $(DIR_LIB)/libft.a

SRC		= main.c \
		  ft_link.c \
		  ft_parse.c \
		  ft_room.c \
		  ft_usefull.c

OBJ		= $(SRC:.c=.o)

INCLUDE	= -Ilemin.h \
		  -I./libft/libft.h

CC		= gcc

CFLAGS	= -Wall -Wextra -Werror

all: $(NAME)

.SILENT:

%.o:%.c
	$(CC) $(CFLAGS) -I./$(INCLUDE) -o $@ -c $<

$(LIBFT):
	make -C $(DIR_LIB)
	printf "\033[1m"
	printf "\033[32m"
	printf "[libft.a compiled]\n"
	printf "\033[0m"

$(NAME): $(LIBFT) $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) ./libft/libft.a $(OBJ) $(INCLUDE)
	printf "\033[1m"
	printf "\033[32m"
	printf "[$@ compiled!]\n"
	printf "\033[0m"

clean:
	make clean -C $(DIR_LIB)
	rm -rf $(OBJ)

fclean: clean
	make fclean -C $(DIR_LIB)
	rm -rf $(NAME)

re: fclean all
