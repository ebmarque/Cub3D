/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebmarque <ebmarque@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 00:28:59 by ebmarque          #+#    #+#             */
/*   Updated: 2024/05/29 00:34:17 by ebmarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_Point
{
	int	x;
	int	y;
}				t_point;

typedef struct s_point
{
	double			x;
	double			y;
	double			teta;
	bool			is_set;
}				t_pos;

typedef enum e_text_index
{
	NORTH = 0,
	SOUTH = 1,
	WEST = 2,
	EAST = 3,
}	t_text_index;

typedef struct s_player
{
	int				w;
	int				s;
	int				d;
	int				a;
	int				map_view;
	int				r_s;
	int				r_a;
	int				r_d;
	t_pos			pos;
	t_pos			dir;
	t_pos			plane;
}				t_player;

typedef struct s_texture
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
}				t_texture;

typedef struct s_text_info
{
	double		pos;
	int			x;
	int			y;
	double		step;
}				t_text_info;

/**
 * @brief Adicionei um ponteiro para a conexao com a mlx, a ideia aqui e poder
 * trabalhar com diferentes imagens, causando uma sobreposicao de imagens,
 * basicamente uma ideia de 'layers; ex: jogo -> mini_map -> mini->player.
 * 
 */
typedef struct s_img
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bbp;
	int		line_length;
	int		endian;
}				t_img;

typedef struct s_rgb
{
	long	r;
	long	b;
	long	g;
	bool	is_set;
}				t_rgb;

typedef struct s_ray
{
	t_pos	pos;
	t_pos	dir;
	t_pos	step;
	t_pos	delta_dist;
	t_pos	side_dist;
	int		side;
	double	wall_dist;
	double	wall_x;
	int		line_height;
	int		start;
	int		end;
}				t_ray;

typedef struct s_mx_var
{
	void	*mlx;
	void	*win;
	void	*img;
	t_img	screen_buffer;
}				t_mx_var;

typedef struct s_file
{
	char	*no_t;
	char	*so_t;
	char	*ea_t;
	char	*we_t;
	int		**map;
	t_point	begin;
	t_rgb	floor;
	t_rgb	ceiling;
	bool	open_map;
	int		map_width;
	t_pos	p_position;
	int		map_end_line;
	int		map_start_line;
	t_point	matrix_dimensions;
}				t_file;

typedef struct s_gmap
{
	int		tile;
	int		**map;
	t_pos	player;
	t_img	map_img;
}				t_gmap;

typedef struct s_mouse
{
	t_point	prev;
	t_point	pos;
	int		on;
}				t_mouse;

typedef struct s_sprite
{
	t_texture	**sprites;
	int			current_frame;
	double		time;
}				t_sprite;

typedef struct s_cub
{
	char		*map_name;
	t_file		*content;
	t_player	*player;
	t_mx_var	*mx_var;
	t_texture	**texture;
	t_texture	*door;
	t_sprite	*sprite;
	t_gmap		*gmap;
	t_mouse		mouse;
}				t_cub;

#endif