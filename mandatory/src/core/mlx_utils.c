/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoutinh <tmoutinh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:04:16 by ebmarque          #+#    #+#             */
/*   Updated: 2024/05/25 16:07:21 by tmoutinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/core.h"

void	_init_img(t_img *img)
{
	img->mlx = cubed()->mx_var->mlx;
	img->win = cubed()->mx_var->win;
	img->img = mlx_new_image(img->mlx, WIDTH, HEIGHT);
	img->addr = mlx_get_data_addr(img->img, &img->bbp,
			&img->line_length, &img->endian);
}

void	mx_var_init(void)
{
	void	*mlx;
	void	*win;

	cubed()->mx_var = ft_calloc(1, sizeof(t_mx_var));
	cubed()->mx_var->mlx = mlx_init();
	mlx = cubed()->mx_var->mlx;
	win = mlx_new_window(mlx, WIDTH, HEIGHT, "CUB3D");
	cubed()->mx_var->win = win;
	// _init_img(cubed()->mx_var->img);
	_init_img(&cubed()->mx_var->screen_buffer);
	//cubed()->gmap->map_img = cubed()->mx_var->screen_buffer;
	cubed()->player->pos = cubed()->player->pos;
	update_player();
	_init_gmap();
}
