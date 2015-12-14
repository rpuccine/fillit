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
INCLUDE_FOLDER = -Iincludes/
SRC_FOLDER = src/
SRCS = main.c parsing.c parsing_2.c parsing_3.c display.c solve.c solve_specific.c map.c
SRC = $(addprefix $(SRC_FOLDER), $(SRCS))
OBJ = $(SRC:.c=.o)
NAME = fillit

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $@ $(OBJ)

%.o: %.c
	$(CC) -o $@ -c $<  $(CFLAGS) $(INCLUDE_FOLDER)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all
