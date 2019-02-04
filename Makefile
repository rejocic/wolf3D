# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rejocic <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/24 11:05:56 by rejocic           #+#    #+#              #
#    Updated: 2019/01/24 11:43:01 by rejocic          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = wolf3d

CC = @gcc -Wall -Werror -Wextra

FLAGS = -framework OpenGL -framework AppKit -lpthread

SRC = src/main.c src/parser.c src/imagination.c src/commands.c src/movement.c \
src/drawing.c

OBJS = $(SRC:.c=.o)

LIB = libft/libft.a

MLX = minilibx_macos/libmlx.a

.PHONY: clean, fclean, re, bug

all: $(NAME) $(LIB)

$(NAME): $(OBJS) $(LIB) $(MLX)
	$(CC) $(FLAGS) -o $(NAME) $(OBJS) $(LIB) $(MLX)

$(OBJS): wolf3d.h

$(LIB):
	@cd libft && make

$(MLX):
	@cd minilibx_macos && make

bug: $(OBJS) $(LIB) $(MLX)
	$(CC) $(FLAGS) -o bug -g $(SRC) $(LIB) $(MLX)

clean:
	@cd libft && make clean
	@rm -rf bug.dSYM
	@rm -f $(OBJS)

fclean: clean
	@cd libft && make fclean
	@cd minilibx_macos && make clean
	@rm -rf bug
	@rm -rf $(NAME)

re: fclean all
