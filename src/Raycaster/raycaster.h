/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoutinh <tmoutinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 12:22:08 by tmoutinh          #+#    #+#             */
/*   Updated: 2024/04/28 21:18:39 by tmoutinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTER_H
# define RAYCASTER_H

//Screen width;
# define SCREEN_W 50
# define SCREEN_H 25
//For the absolute value function (fabs);
#include <math.h>
#include <stdbool.h>
#include "../includes/core.h"

typedef enum e_text_index
{
	NORTH,
	SOUTH,
	WEST,
	EAST,
}	t_text_index;

typedef struct s_point
{
	double			x;
	double			y;
}				t_pos;

typedef struct s_player
{
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

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bbp;
	int		line_length;
	int		endian;
}				t_img;

typedef struct  s_ray
{
    //Start position of the ray [Player position];
    t_pos		pos;
    //Direction vector;
	t_pos		dir;
    //Direction in which the ray is going [Player orientation];
	t_pos		step;
    //Distance from one x or y side to the next x or y side;
	t_pos		delta_dist;
    //Distance from the player to the wall;
	t_pos		side_dist;
	int			side;
	double		wall_dist;
	double		wall_x;
	int			line_height;
	int			start;
	int			end;
}   t_ray;

typedef struct s_mx_var
{
	void		*mlx;
	void		*win;
	void		*img;
	t_img		screen_buffer;
}				t_mx_var;

t_cub	*cubed(void);
#endif