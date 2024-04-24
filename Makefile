# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ebmarque <ebmarque@student.42porto.com     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/23 15:52:25 by ebmarque          #+#    #+#              #
#    Updated: 2024/04/24 20:51:36 by ebmarque         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Cub3D

CC = cc
CFLAGS = -Wall -Wextra -Werror #-g fsanitize=address

LIBFT_DIRECTORY = src/LIB/LIBFT
LIBFT = $(LIBFT_DIRECTORY)/libft.a

MLX_DIRECTORY = src/LIB/MLX_MAC
MLX = $(MLX_DIRECTORY)/libmlx.a

SRC_DIRECTORY = src

INCLUDES = includes/core.h

SRCS = 	$(SRC_DIRECTORY)/core/main.c \
		$(SRC_DIRECTORY)/error/error.c $(SRC_DIRECTORY)/error/content_error.c \
		$(SRC_DIRECTORY)/tools/utils.c  $(SRC_DIRECTORY)/tools/utils2.c 
		# $(SRC_DIRECTORY)/core/*.c \
		# $(SRC_DIRECTORY)/parsing/*.c \
		# $(SRC_DIRECTORY)/raycasting/*.c \

OBJS = $(SRCS:.c=.o)

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S), Darwin)
		CC = cc
		MLX_DIRECTORY = src/LIB/MLX_MAC
		MLXFLAGS = -framework OpenGL -framework AppKit -L ./$(MLX_DIRECTORY) -lmlx
else ifeq ($(UNAME), FreeBSD) 
	CC = clang
else 
	CC = cc
	MLX_DIRECTORY = src/LIB/MLX_LINUX
	MLXFLAGS = -L ./$(MLX_DIRECTORY) -lmlx -Ilmlx -lXext -lX11 -lm
endif

all: $(NAME)

$(NAME): $(LIBFT) $(MLX) $(OBJS) $(INCLUDES)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX) $(MLXFLAGS) -o $(NAME)

$(LIBFT):
	@make -C $(LIBFT_DIRECTORY)

$(MLX):
	@make -C $(MLX_DIRECTORY) > /dev/null 2> /dev/null


clean:
	@make clean -C $(MLX_DIRECTORY) > /dev/null 2>/dev/null
	@make clean -C $(LIBFT_DIRECTORY)
	@rm -f $(OBJS)

fclean: clean
	@make clean -C $(MLX_DIRECTORY) > /dev/null 2>/dev/null
	@make fclean -C $(LIBFT_DIRECTORY)
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
