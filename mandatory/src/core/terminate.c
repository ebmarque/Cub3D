/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiago <tiago@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 17:30:43 by ebmarque          #+#    #+#             */
/*   Updated: 2024/05/28 23:10:55 by tiago            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/core.h"

static void	_terminate_textures(t_texture **t)
{
	int	i;

	i = 0;
	while (t[i])
	{
		if (t[i]->img)
			mlx_destroy_image(cubed()->mx_var->mlx, t[i]->img);
		if (t[i])
			free(t[i]);
		i++;
	}
	if (t)
		free(t);
}

static void	destroy_game(void)
{
	if (cubed()->gmap)
	{
		mlx_destroy_image(cubed()->mx_var->mlx, cubed()->gmap->map_img.img);
		free(cubed()->gmap);
	}
	if (cubed()->mx_var->screen_buffer.img)
		mlx_destroy_image(cubed()->mx_var->mlx, \
			cubed()->mx_var->screen_buffer.img);
	if (cubed()->mx_var->img)
	{
		mlx_destroy_image(cubed()->mx_var->mlx, cubed()->mx_var->img);
		free(cubed()->mx_var->img);
	}
	if (cubed()->mx_var->win)
		mlx_destroy_window(cubed()->mx_var->mlx, cubed()->mx_var->win);
	if (cubed()->mx_var->mlx)
	{
		mlx_destroy_display(cubed()->mx_var->mlx);
		free(cubed()->mx_var->mlx);
	}
	if (cubed()->mx_var)
		free(cubed()->mx_var);
}

int	_terminate_cubed(void)
{
	t_cub	*cub;

	cub = cubed();
	_terminate_textures(cub->texture);
	destroy_game();
	_clean_content(cub->content);
	if (cub->player)
		free(cub->player);
	exit (EXIT_SUCCESS);
}
