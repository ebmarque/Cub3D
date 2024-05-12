/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiago <tiago@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 15:44:52 by ebmarque          #+#    #+#             */
/*   Updated: 2024/05/12 16:06:29 by ebmarque         ###   ########.fr       */
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
# define INVISIBLE "\033[8m"

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

# define EMPTY_SPACES " \t\v\b\a\r\f\n"
# define MEMORY_ERROR RED "ERROR: Failed to allocate memory" RESET
# define INVALID_ARGC RED "ERROR: Wrong number of arguments." RESET
# define INVALID_NAME RED "ERROR: Invalid map name." RESET
# define NO_ACCESS RED "ERROR: File cannot be accessed." RESET
# define NO_RIGHTS RED "ERROR: File (Permission for execution denied)." RESET
# define NO_TEXTURE_ACCESS RED "ERROR: Texture file cannot be accessed." RESET
# define NO_TEXTURE_RIGHTS RED \
	"ERROR: Texture file (Permission for execution denied)." RESET
# define EMPTY_MAP RED "ERROR: Empty map file." RESET
# define WRONG_EXT RED "ERROR: Map file with wrong extension < .cub > ." RESET
# define PARSING_ERROR RED "ERROR: Map file wrongly formatted." RESET
# define EMPTY_TEXTURE RED "ERROR: Empty texture file." RESET
# define INVALID_MAP_LINE RED "ERROR: Map contains invalid characters." RESET
# define EMPTY_MAP_LINE RED "ERROR: Map contains empty line." RESET
# define PLAYER_ON_EDGE RED "ERROR: Player is on the edge of the map." RESET
# define DUPLICATED_PLAYER RED "ERROR: More than one player on the map" RESET
# define NO_PLAYER RED "ERROR: Player start position not found." RESET
# define OPEN_WALLS RED "ERROR: Player is not surrounded by walls." RESET
# define SMALL_MAP RED "ERROR: Map dimensions are too small." RESET

/*-----------------MLX--------------------*/
/**
 * @file core.h
 * @brief This file contains the definitions of various constants used in the Cub3D program.
 */

# define WIN_DESTROY 17 /**< The window destroy event code. */
# define KEY_PRESSED 2 /**< The key pressed event code. */
# define KEY_RELEASED 3 /**< The key released event code. */
# define DESTROY_MASK (1L << 17) /**< The mask for the window destroy event. */
# define KEY_P_MASK (1L << 0) /**< The mask for the key pressed event. */
# define KEY_R_MASK (1L << 1) /**< The mask for the key released event. */

# define WIN_DESTROY 17
# define KEY_PRESSED 2
# define KEY_RELEASED 3
# define DESTROY_MASK (1L << 17)
# define KEY_P_MASK (1L << 0)
# define KEY_R_MASK (1L << 1)

# define P_SPEED 0.01
# define R_SPEED 0.05
# define BLOCK_SIZE 10
# define P_SIZE 30
# define RED_BLOCK 0x00FF0000
# define WHITE_BLOCK 0x00FFFFFF
# define INVISIBLE_BLOCK 0xFF000000
/*-----------------MATH--------------------*/
#define PI 3.1415926

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <errno.h>
# include <unistd.h>
# include <math.h>
# include <time.h>
# include "../src/LIB/LIBFT/libft.h"
# include "structs.h"

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



/*---------------------------------- ERRORS -----------------------------------*/
/*---------------------------------- ERROR -----------------------------------*/

void	_check_errors(int argc, char **argv);
t_file	*_check_map_content(char *file);

/*------------------------------ MAP VALIDATION ------------------------------*/

void	_check_valid_map_char(char *file, int start, int fd, t_file *content);
void	_check_and_parse_map(t_file *content, char *file);
void	_check_valid_map_char(char *file, int start, int fd, t_file *content);
int		_is_valid_map_line(char *line);


/*---------------------------------- TOOLS -----------------------------------*/
void	raycaster(void);
int	render_screen(void);
t_cub	*cubed(void);
t_pos	to_screen_pos(t_pos pos);


/*--------------------------------- UTILS 1 ----------------------------------*/

int		_get_split_size(char **line);
int		_is_element(char *line);
int		_is_map_line(char *line);
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
char	*_tab_into_spaces(char *source);
void	_fill_tabs(const char *source, char *new_string);
size_t	_count_tabs(const char *source);


void	_get_map(t_file *content, char *file);
void	_print_map(t_file *t);
void	_fill_map(t_file *content, char *file, int i, int fd);
void	_fill_map_line(t_file *t, int i, int width, char *line);
bool	_is_player_char(char c);

/*-------------------------------- MOVEMENTS ---------------------------------*/

bool	_inside_y_limits(int y);
bool	_inside_x_limits(int x);

void	_check_map_rules(t_file *t);
int		_key_pressed(int k, void *data);
int		_key_release(int k, void *data);
int		_raycasting_loop(void);
void	_handle_input(t_player *p);


void	_linear_movement(t_player *p, int orientation);
void	_strafe_movement(t_player *p, int orientation);
void	_spin(t_player *p, int wise);


/*--------------------------------- COLOR U ----------------------------------*/

int		gen_trgb(int opacity, t_rgb color);
int		get_opacity(int trgb);
int		get_r(int trgb);
int		get_g(int trgb);
int		get_b(int trgb);

/*--------------------------------- COLOR U ----------------------------------*/

void	_draw_map_square(t_img *img, int x, int y, int color);
bool	_insede_p_square(int x, int y, int side_l, t_point c);
void	my_mlx_pixel_put(t_img *data, int x, int y, int color);
void	_black_window(t_img *m);
void	_draw_map(t_file *t, t_img *img);



#endif