/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebmarque <ebmarque@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 15:44:52 by ebmarque          #+#    #+#             */
/*   Updated: 2024/04/26 13:17:29 by ebmarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORE_H
# define CORE_H

# define BLACK "\033[0;30m"
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define MAGENTA "\033[0;35m"
# define CYAN "\033[0;36m"
# define WHITE "\033[0;37m"
# define RESET "\033[0m"

// The width of the game window.
# define WIDTH 1200
// The height of the game window.
# define HEIGHT 840

/*------------------------------ ERROR MESSAGES ------------------------------*/
/**
 * @file core.h
 * @brief This file contains error messages defined as macros.
 *
 * The macros define various error messages that can be used in the program.
 * Each error message is defined as a string constant with a specific 
 * color code.These error messages can be used to display error 
 * information to the user. The color codes are used to highlight 
 * the error messages for better visibility.
 */

# define MEMORY_ERROR RED "ERROR: Fail to allocate memory" RESET
# define INVALID_ARGC RED "ERROR: Wrong number of arguments." RESET
# define INVALID_NAME RED "ERROR: Invalid map name." RESET
# define NO_ACCESS RED "ERROR: File cannot be accessed." RESET
# define NO_RIGHTS RED "ERROR: File (Permission for execution denided)." RESET
# define NO_TEXTURE_ACCESS RED "ERROR: Texture file cannot be accessed." RESET
# define NO_TEXTURE_RIGHTS RED \
	"ERROR: Texture file (Permission for execution denided)." RESET
# define EMPTY_MAP RED "ERROR: Empty map file." RESET
# define WRONG_EXT RED "ERROR: Map file with wrong extension < .cub > ." RESET
# define PARSING_ERROR RED "ERROR: Map file wrongly formated." RESET
# define EMPTY_TEXTURE RED "ERROR: Empty texture file." RESET

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <errno.h>
# include <unistd.h>
# include <math.h>
# include <time.h>
# include "../src/LIB/LIBFT/libft.h"

# ifdef __APPLE__

#  include "../src/LIB/MLX_MAC/mlx.h"

# elif defined(__linux__)

#  include "../src/LIB/MLX_LINUX/mlx.h"

# endif

# ifdef __APPLE__

typedef enum e_key
{
	ESC = 53,
	A = 0,
	S = 1,
	D = 2,
	W = 13,
	Q = 12,
	UP = 126,
	DOWN = 125,
	RIGHT = 124,
	LEFT = 123
}		t_key;

typedef enum e_mask
{
	KEY_MASK = 0,
	CLOSE_MASK = 0
}	t_mask;

# elif defined(__linux__)

typedef enum e_key
{
	ESC = 65307,
	A = 97,
	S = 115,
	D = 100,
	W = 119,
	Q = 113,
	UP = 65362,
	DOWN = 65364,
	RIGHT = 65363,
	LEFT = 65361
}		t_key;


# endif

typedef struct s_rgb
{
	long	r;
	long	b;
	long	g;
	bool	is_set;
}				t_rgb;

typedef struct s_file
{
	t_rgb	floor;
	t_rgb	ceiling;
	char	*no_t;
	char	*so_t;
	char	*ea_t;
	char	*we_t;
	char	**map;
}				t_file;

typedef struct s_cub
{
	char	*map_name;
	t_file	*content;
}				t_cub;

/*---------------------------------- ERRORS -----------------------------------*/

/*---------------------------------- ERROR -----------------------------------*/
void	_check_errors(int argc, char **argv);
void	_check_file_name(char *file);
void	_check_file_permissions(char *file);
void	_check_empty_file(char *file);
t_file	*_check_map_content(char *file);

/*---------------------------------- TOOLS -----------------------------------*/

/*--------------------------------- UTILS 1 ----------------------------------*/
int		_get_split_size(char **line);
int		_is_element(char *line);
int		_is_map_line(char **split);
void	_exit_error(char *msg);

/*--------------------------------- UTILS 2 ----------------------------------*/

void	_clean_content(t_file *content);
void	_read_all_file(int fd);
int		_all_elements_set(t_file *t);
void	_print_content_variable(t_file *t);
char	*_give_texture(char *line);

/*--------------------------------- UTILS 3 ----------------------------------*/

int		_check_t_file_permissions(char *file);
int		_check_t_empty_file(char *file);

#endif