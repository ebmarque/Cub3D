/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebmarque <ebmarque@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 17:30:43 by ebmarque          #+#    #+#             */
/*   Updated: 2024/06/03 12:18:07 by ebmarque         ###   ########.fr       */
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
	if (cubed()->mx_var->screen_buffer.img)
		mlx_destroy_image(cubed()->mx_var->mlx, \
			cubed()->mx_var->screen_buffer.img);
	if (cubed()->mx_var->img)
	{
		mlx_destroy_image(cubed()->mx_var->mlx, cubed()->mx_var->img);
		free(cubed()->mx_var->img);
	}
	if (cubed()->door)
	{
		mlx_destroy_image(cubed()->mx_var->mlx, cubed()->door->img);
		free(cubed()->door);
	}
	if (cubed()->mx_var->win)
		mlx_destroy_window(cubed()->mx_var->mlx, cubed()->mx_var->win);
	if (cubed()->mx_var->mlx)
	{
		#ifdef __LINUX__
		mlx_destroy_display(cubed()->mx_var->mlx);
		#endif
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
	_terminate_textures(cub->sprite->sprites);
	destroy_game();
	_clean_content(cub->content);
	if (cub->player)
		free(cub->player);
	if (cub->gmap)
		free(cub->gmap);
	if (cub->sprite)
		free(cub->sprite);
	exit (EXIT_SUCCESS);
}
