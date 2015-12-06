# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rpuccine <rpuccine@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/09/09 15:37:03 by rpuccine          #+#    #+#              #
#    Updated: 2015/12/06 19:26:02 by rpuccine         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror
INCLUDE_FOLDER = -Iincludes/ -Ilibft/includes/
SRC_FOLDER = src/
SRCS = main.c display.c parsing.c
SRC = $(addprefix $(SRC_FOLDER), $(SRCS))
OBJ = $(SRC:.c=.o)
NAME = fillit
LIB = -Llibft/ -lft

all: libfte $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $@ $(OBJ) $(LIB)

libfte:
	make -C libft/

%.o: %.c
	$(CC) -o $@ -c $<  $(CFLAGS) $(INCLUDE_FOLDER)

clean:
	make -C libft/ clean
	rm -rf $(OBJ)

fclean: clean
	make -C libft/ s_fclean
	rm -rf $(NAME)

re: fclean all
