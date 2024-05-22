/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebmarque <ebmarque@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:04:16 by ebmarque          #+#    #+#             */
/*   Updated: 2024/05/22 18:03:14 by ebmarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/core.h"

void	_init_img(t_img *img)
{
	img->mlx = cubed()->mx_var->mlx;
	img->win = cubed()->mx_var->win;
	img->img = mlx_new_image(img->mlx, WIDTH * 0.25, HEIGHT * 0.25);
	img->addr = mlx_get_data_addr(img->img, &img->bbp, \
		&img->line_length, &img->endian);
}

void	mx_var_init()
{
	t_img	screen_buff;
	cubed()->mx_var = ft_calloc(1, sizeof(t_mx_var));
	cubed()->mx_var->mlx = mlx_init();
	cubed()->mx_var->win = mlx_new_window(\
		cubed()->mx_var->mlx, WIDTH, HEIGHT, "Cub3D");
	cubed()->mx_var->img = mlx_new_image(cubed()->mx_var->mlx, \
		WIDTH, HEIGHT);
	screen_buff.img = mlx_new_image(cubed()->mx_var->mlx, \
		WIDTH, HEIGHT);
	screen_buff.mlx = cubed()->mx_var->mlx;
	screen_buff.win = cubed()->mx_var->win;
	screen_buff.addr = mlx_get_data_addr(screen_buff.img,
			&screen_buff.bbp, &screen_buff.line_length,
			&screen_buff.endian);
	// cubed()->mx_var->screen_buffer = screen_buff;
	_init_img(&cubed()->mx_var->screen_buffer);
	cubed()->player->pos = to_screen_pos(cubed()->player->pos);
	update_player();
	_init_gmap();
}
