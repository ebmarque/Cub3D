/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebmarque <ebmarque@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 13:04:15 by ebmarque          #+#    #+#             */
/*   Updated: 2024/05/01 13:27:04 by ebmarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_H
#define TEST_H

#include "../../includes/core.h"

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;


typedef struct s_t
{
	int		w;
	int		s;
	int		a;
	int		d;
	void	*mlx;
	void	*mlx_win;
	t_data	*img;
	t_point	center;
} t_p;


/* --------------------------------- MOVEMENT --------------------------------*/
void	_walk_up(t_p *game);
void	_walk_down(t_p *game);
void	_walk_left(t_p *game);
void	_walk_right(t_p *game);


/* ----------------------------------- DRAW ----------------------------------*/
bool	_is_inside(t_point center, int y, int x, int lengh);
void	draw_square(t_p *game, int lengh);
void	_black_window(t_p *game);

/* ----------------------------------- EVENT ---------------------------------*/
int		read_keys(void *param);
int		key_press(int key_pressed, void *param);
int		key_release(int key_pressed, void *param);

/* ----------------------------------- UTILS ---------------------------------*/
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
int		exit_game(void *data);
t_p		*_init_mlx(void);




#endif