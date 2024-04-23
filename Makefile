# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ebmarque <ebmarque@student.42porto.com     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/23 15:52:25 by ebmarque          #+#    #+#              #
#    Updated: 2024/04/23 17:39:14 by ebmarque         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Cub3D

CC = cc
CFLAGS = -Wall -Wextra -Werror #-g fsanitize=address

LIBFT_DIRECTORY = src/LIB/LIBFT
LIBFT = $(LIBFT_DIRECTORY)/libft.a

MLX_DIRECTORY = src/LIB/MLX
MLX = $(MLX_DIRECTORY)/libmlx.a

SRC_DIRECTORY = src

INCLUDES = includes/core.h

SRCS = $(SRC_DIRECTORY)/tests/main.c
	# $(SRC_DIRECTORY)/erro/*.c \
	# $(SRC_DIRECTORY)/tools/*.c \
	# $(SRC_DIRECTORY)/core/*.c \
	# $(SRC_DIRECTORY)/parsing/*.c \
	# $(SRC_DIRECTORY)/raycasting/*.c \

OBJS = $(SRCS:.c=.o)

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S), Darwin)
	MLXFLAGS = -framework OpenGL -framework AppKit -L ./src/LIB/MLX -lmlx
else
	MLXFLAGS = -Lmlx -lmlx -lX11 -lbsd -lm
endif

all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(OBJS) $(INCLUDES)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX) $(MLXFLAGS) -o $(NAME)

$(LIBFT):
	@make -C $(LIBFT_DIRECTORY)

$(MLX):
	@make -C $(MLX_DIRECTORY) 2> /dev/null


clean:
	@make clean -C $(MLX_DIRECTORY)
	@make clean -C $(LIBFT_DIRECTORY)
	@rm -f $(OBJS)

fclean: clean
	@make clean -C $(MLX_DIRECTORY)
	@make fclean -C $(LIBFT_DIRECTORY)
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
