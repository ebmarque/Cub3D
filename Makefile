# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ebmarque <ebmarque@student.42porto.com     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/23 15:52:25 by ebmarque          #+#    #+#              #
#    Updated: 2024/04/23 16:20:24 by ebmarque         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Cub3D

CC = cc
CFLAGS = -Wall -Wextra -Werror -g #fsanitize=address

LIBFT_DIRECTORY = src/LIB/LIBFT
LIBFT = $(LIBFT_DIRECTORY)/libft.a

MLX_DIRECTORY = src/LIB/MLX
MLX = $(MLX_DIRECTORY)/libmlx.a

SRC_DIRECTORY = src

SRCS = $(SRC_DIRECTORY)/erro/*.c \
	$(SRC_DIRECTORY)/tools/*.c \
	$(SRC_DIRECTORY)/core/*.c \
	$(SRC_DIRECTORY)/parsing/*.c \
	$(SRC_DIRECTORY)/raycasting/*.c \

OBJS = $(SRCS:.c=.o)

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
	MLXFLAGS = -Lmlx -lmlx -framework OpenGL -framework AppKit
else
	MLXFLAGS = -Lmlx -lmlx -lX11 -lbsd -lm
endif

all: $(NAME)

$(NAME): $(OBJS) $(INCLUDES) $(LIBFT) $(MLX)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX) $(MLXFLAGS) -o $(NAME)

$(LIBFT):
	@make -C $(LIBFT_DIRECTORY)

$(MLX):
	@make -C $(MLX_DIRECTORY)

clean:
	@make clean -C mlx
	@make clean -C src/LIBFT
	@rm -f $(OBJS)

fclean: clean
	@make fclean -C mlx
	@make fclean -C src/LIBFT
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
