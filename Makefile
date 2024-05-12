# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tiago <tiago@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/23 15:52:25 by ebmarque          #+#    #+#              #
#    Updated: 2024/05/10 17:03:06 by ebmarque         ###   ########.fr        #
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

EVENTS_DIRECTORY = src/events

TOOLS_DIRECTORY = src/tools

CORE_DIRECTORY = src/core

RAYCASTING_DIRECTORY = src/Raycaster

ERROR = $(addprefix $(ERROR_DIRECTORY)/, \
		error.c content_error.c map_validation.c \
		map_validation_2.c map_rules.c)

EVENTS = $(addprefix $(EVENTS_DIRECTORY)/, \
		draw.c hooks.c movements.c \
		movements_utils.c draw_utils.c color_utils.c )

TOOLS = $(addprefix $(TOOLS_DIRECTORY)/, \
		utils1.c utils2.c utils3.c)

CORE = $(addprefix $(SRC_DIRECTORY)/, main.c)


#SRCS = $(ERROR) $(TOOLS) $(CORE) $(EVENTS)

RAYCASTER = $(addprefix $(RAYCASTING_DIRECTORY)/, raycaster.c)
SRCS = $(ERROR) $(TOOLS) $(CORE) $(RAYCASTER)


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


