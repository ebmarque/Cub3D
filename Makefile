# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ebmarque <ebmarque@student.42porto.com     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/23 15:52:25 by ebmarque          #+#    #+#              #
#    Updated: 2024/05/01 13:24:43 by ebmarque         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Colors
GREEN = \033[0;32m
YELLOW = \033[0;33m
NC = \033[0m

NAME = Cub3D

CC = cc
CFLAGS = -Wall -Wextra -Werror -g #fsanitize=address

LIBFT_DIRECTORY = src/LIB/LIBFT
LIBFT = $(LIBFT_DIRECTORY)/libft.a

MLX_DIRECTORY = src/LIB/MLX_MAC
MLX = $(MLX_DIRECTORY)/libmlx.a

OBJDIR = OBJS
OBJS = $(addprefix $(OBJDIR)/, $(SRCS:.c=.o))

SRC_DIRECTORY = src

INCLUDES = includes/core.h

ERROR_DIRECTORY = src/error

TOOLS_DIRECTORY = src/tools

CORE_DIRECTORY = src/core

RAYCASTING_DIRECTORY = src/raycaster

TESTS_DIRECTORY = src/tests

TESTS = $(TESTS_DIRECTORY)/main.c \
		$(TESTS_DIRECTORY)/draw.c \
		$(TESTS_DIRECTORY)/utils.c \
		$(TESTS_DIRECTORY)/movements.c \
		$(TESTS_DIRECTORY)/event.c

ERROR = $(ERROR_DIRECTORY)/error.c $(ERROR_DIRECTORY)/content_error.c \
		$(ERROR_DIRECTORY)/map_validation.c \
		$(ERROR_DIRECTORY)/map_validation_2.c \
		$(ERROR_DIRECTORY)/map_rules.c

TOOLS = $(TOOLS_DIRECTORY)/utils1.c $(TOOLS_DIRECTORY)/utils2.c \
		$(TOOLS_DIRECTORY)/utils3.c

CORE = $(TESTS)  #$(CORE_DIRECTORY)/main.c

SRCS = $(ERROR) $(TOOLS) $(CORE)

# OBJS = $(SRCS:.c=.o)

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
	@echo "$(GREEN)[$(NAME)]: compiled successfully!$(NC)"

$(LIBFT):
	@make -s -C $(LIBFT_DIRECTORY)
	@echo "$(GREEN)[LIBFT]: compiled successfully!$(NC)"

$(MLX):
	@make -s -C $(MLX_DIRECTORY) > /dev/null 2> /dev/null
	@echo "$(GREEN)[MLX]: compiled successfully!$(NC)"

$(OBJDIR)/%.o: %.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@ -I ./includes

clean:
	@make -s clean -C $(MLX_DIRECTORY) > /dev/null 2>/dev/null
	@make -s clean -C $(LIBFT_DIRECTORY)
	@rm -rf $(OBJDIR)
	@echo "$(YELLOW)Cleaned object files!$(NC)"

fclean: clean
	@make -s clean -C $(MLX_DIRECTORY) > /dev/null 2>/dev/null
	@make -s fclean -C $(LIBFT_DIRECTORY)
	@rm -f $(NAME)
	@echo "$(YELLOW)Cleaned $(NAME) executable!$(NC)"

re: fclean all

.PHONY: all clean fclean re


