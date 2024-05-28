/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiago <tiago@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 15:44:52 by ebmarque          #+#    #+#             */
/*   Updated: 2024/05/28 20:42:33 by tiago            ###   ########.fr       */
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
# define BG_BLACK "\033[40m"
# define BG_RED "\033[41m"
# define BG_GREEN "\033[42m"
# define BG_YELLOW "\033[43m"
# define BG_BLUE "\033[44m"
# define BG_MAGENTA "\033[45m"
# define BG_CYAN "\033[46m"
# define BG_WHITE "\033[47m"

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
# define MEMORY_ERROR "ERROR: Failed to allocate memory"
# define INVALID_ARGC "ERROR: Wrong number of arguments."
# define INVALID_NAME "ERROR: Invalid map name."
# define NO_ACCESS "ERROR: File cannot be accessed."
# define NO_RIGHTS "ERROR: File (Permission for execution denied)."
# define NO_TEXTURE_ACCESS "ERROR: Texture file cannot be accessed."
# define NO_TEXTURE_RIGHTS \
	"ERROR: Texture file (Permission for execution denied)."
# define EMPTY_MAP "ERROR: Empty map file."
# define WRONG_EXT "ERROR: Map file with wrong extension < .cub > ."
# define PARSING_ERROR "ERROR: Map file wrongly formatted."
# define EMPTY_TEXTURE "ERROR: Empty texture file."
# define INVALID_MAP_LINE "ERROR: Map contains invalid characters."
# define EMPTY_MAP_LINE "ERROR: Map contains empty line."
# define PLAYER_ON_EDGE "ERROR: Player is on the edge of the map."
# define DUPLICATED_PLAYER "ERROR: More than one player on the map"
# define NO_PLAYER "ERROR: Player start position not found."
# define OPEN_WALLS "ERROR: Player is not surrounded by walls."
# define SMALL_MAP "ERROR: Map dimensions are too small."
# define WIN_DESTROY 17
# define KEY_PRESSED 2
# define KEY_RELEASED 3
# define WIN_DESTROY 17
# define KEY_PRESSED 2
# define KEY_RELEASED 3
# define MOUSE_CLICK 4
# define MOUSE_MOTION 6
# define P_SPEED 0.080
# define R_SPEED 0.05
# define MOUSE_SPEED 0.001
# define BLOCK_SIZE 10
# define P_SIZE 30
# define RED_BLOCK 0x00FF0000
# define WHITE_BLOCK 0x00FFFFFF
# define INVISIBLE_BLOCK 0xFF000000
# define PI 3.1415926
# define SHADER_DIST 9.00

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
	E = 14,
	SPACE = 49,
	UP = 126,
	DOWN = 125,
	RIGHT = 124,
	LEFT = 123,
	ENTER = 36
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
	E = 101,
	F = 102,
	R = 114,
	SPACE = 32,
	ENTER = 65293,
	UP = 65362,
	DOWN = 65364,
	RIGHT = 65363,
	LEFT = 65361
}		t_key;

# endif

/*---------------------------------- CORE ------------------------------------*/
void		_load_textures(void);
void		_init_gmap(void);
t_texture	*_upload_texture(char *path);
void		update_player();
void		_init_img(t_img *img);
void		mx_var_init();
int			quit_game(void);

/*----------------------------- RAYCASTER_UTILS -------------------------------*/
void		init_ray(t_ray *ray, int x_cord);
void		get_side_dist(t_ray *ray);
void		perform_dda(t_ray *ray);
void		wall_placement(t_ray *ray);

/*--------------------------------- RENDERER ----------------------------------*/
t_texture	*get_text_info(t_ray *ray);
void		render_pixel(int x, int y, int color);
int			_get_img_pixel(t_texture *mlx, int x, int y);
void		_render_floor(int x);
void		_render_ceiling(int x);

/*--------------------------------- SHADERS -----------------------------------*/
void		texture_render(t_ray *ray, int x_cord);
int			shader_ceilling(double ref, double wall_dist, int color);
int			shader_floor(double ref, double wall_dist, int color);
int			shader_texture(double wall_dist, int color);


/*---------------------------------- ERROR -----------------------------------*/

void		_check_errors(int argc, char **argv);
t_file		*_check_map_content(char *file);
int			_check_color_values(t_rgb color);
int			_set_floor(char **split, t_file *content);
int			_set_ceiling(char **split, t_file *content);
int			_save_element_data(char **split, t_file *content);
bool		_is_player_on_edge(t_file *t);
bool		_duplicate_player(t_file *t);
int			_recover_block(char c);
void		_fill_block(t_file *t, t_point current, int c);

/*------------------------------ MAP VALIDATION ------------------------------*/

bool		_is_valid_map_char(char c);
int			_is_valid_map_line(char *line);
void		_check_valid_map_char(char *file, int start, int fd, t_file *content);
void		_update_map_width(t_file *content, char *line);
void		_check_valid_map_char(char *file, int start, int fd, t_file *content);
void		_check_and_parse_map(t_file *content, char *file);
void		_check_valid_map_char(char *file, int start, int fd, t_file *content);
int			_is_valid_map_line(char *line);

/*---------------------------------- TOOLS -----------------------------------*/

void		raycaster(void);
int			render_screen(void);
t_cub		*cubed(void);
t_pos		to_screen_pos(t_pos pos);

/*--------------------------------- UTILS 1 ----------------------------------*/

int			_get_split_size(char **line);
int			_is_element(char *line);
int			_is_map_line(char *line);
void		_exit_error(char *msg);
void		_free_map(t_file *t);

/*--------------------------------- UTILS 2 ----------------------------------*/

void		_clean_content(t_file *content);
void		_read_all_file(int fd);
int			_all_elements_set(t_file *t);
void		_print_content_variable(t_file *t);
char		*_give_texture(char *line);

/*--------------------------------- UTILS 3 ----------------------------------*/

int			_check_t_file_permissions(char *file);
int			_check_t_empty_file(char *file);
char		*_tab_into_spaces(char *source);
void		_fill_tabs(const char *source, char *new_string);
size_t		_count_tabs(const char *source);
void		_get_map(t_file *content, char *file);
void		_print_map(t_file *t);
void		_fill_map(t_file *content, char *file, int i, int fd);
void		_fill_map_line(t_file *t, int i, int width, char *line);
bool		_is_player_char(char c);

/*-------------------------------- MOVEMENTS ---------------------------------*/

bool		_inside_y_limits(int y);
bool		_inside_x_limits(int x);
void		_check_map_rules(t_file *t);
int			_key_pressed(int k, void *data);
int			_key_release(int k, void *data);
int			_raycasting_loop(void);
void		_linear_movement(t_player *p, int orientation);
void		_strafe_movement(t_player *p, int orientation);
void		_spin(t_player *p, int wise);
int			_mouse_move(int x, int y, void *data);
int			_mouse_click(int button, int x, int y, void *data);

/*--------------------------------- COLOR U ----------------------------------*/

int			gen_trgb(int opacity, t_rgb color);
int			get_opacity(int trgb);
int			get_r(int trgb);
int			get_g(int trgb);
int			get_b(int trgb);

/*--------------------------------- COLOR U ----------------------------------*/

void		_draw_square(t_gmap *mini, int x, int y, int factor);
void		my_mlx_pixel_put(t_img *data, int x, int y, int color);
void		_black_window(t_img *m, float factor);
void		_draw_map(t_gmap *mini);


int			_terminate_cubed(void);


#endif