# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ebmarque <ebmarque@student.42porto.com     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/23 15:52:25 by ebmarque          #+#    #+#              #
#    Updated: 2024/05/23 16:30:07 by ebmarque         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Colors
GREEN = \033[0;32m
YELLOW = \033[0;33m
NC = \033[0m

NAME = Cub3D

CC = cc
CFLAGS = -Wall -Wextra -Werror -g #fsanitize=address

LIBFT = $(LIBFT_DIRECTORY)/libft.a
MLX = $(MLX_DIRECTORY)/libmlx.a


INCLUDES =		 			includes/core.h
OBJDIR = 					OBJS
LIBFT_DIRECTORY = 			src/LIB/LIBFT
MLX_DIRECTORY = 			src/LIB/MLX_MAC
SRC_DIRECTORY = 			src
ERROR_DIRECTORY = 			src/error
EVENTS_DIRECTORY = 			src/events
TOOLS_DIRECTORY = 			src/tools
CORE_DIRECTORY = 			src/core
RAYCASTING_DIRECTORY = 		src/Raycaster

OBJS = $(addprefix $(OBJDIR)/, $(SRCS:.c=.o))

ERROR = $(addsuffix .c, $(addprefix $(ERROR_DIRECTORY)/, \
		content_error			\
		error_utils_1 			\
		error_utils_2			\
		error_utils_3			\
		error 					\
		map_validation_2 		\
		map_validation_1		\
		map_rules 				))

EVENTS = $(addsuffix .c, $(addprefix $(EVENTS_DIRECTORY)/, \
		draw 					\
		hooks movements 		\
		movements_utils 		\
		draw_utils 				\
		mouse	 				\
		color_utils				))

TOOLS = $(addsuffix .c, $(addprefix $(TOOLS_DIRECTORY)/, \
		utils1 					\
		utils2 					\
		utils3					\
		utils4					))

CORE = $(addsuffix .c, $(addprefix $(CORE_DIRECTORY)/, \
		terminate				\
		initialization			\
		mlx_utils				\
		main					))


RAYCASTER = $(addprefix $(RAYCASTING_DIRECTORY)/, raycaster.c)

SRCS = $(ERROR) $(TOOLS) $(CORE) $(RAYCASTER) $(EVENTS)

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


