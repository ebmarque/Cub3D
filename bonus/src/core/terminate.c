/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebmarque <ebmarque@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 17:30:43 by ebmarque          #+#    #+#             */
/*   Updated: 2024/05/25 15:30:51 by ebmarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/core.h"

/* static void	_terminate_textures(t_texture **t)
{
	int	i;

	i = 0;
	while (t[i])
	{
		if (t[i]->img)
			free(t[i]->img);
		if (t[i]->addr)
			free(t[i]->addr);
		if (t[i])
			free(t[i]);
		i++;
	}
	if (t)
		free(t);
} */

/* static void	_terminate_img(t_img *img)
{
	if (img->mlx)
		free(img->mlx);
	if (img->win)
		free(img->win);
	if (img->img)
		free(img->img);
	if (img->addr)
		free(img->addr);
} */

/* static void	_terminate_mx_var(t_mx_var *mx)
{
	if (mx->mlx)
		free(mx->mlx);
	if (mx->win)
		free(mx->win);
	if (mx->img)
		free(mx->img);
} */

/* 
static void	destroy_game(void)
{
	if (cubed()->mx_var->screen_buffer.img)
		mlx_destroy_image(cubed()->mx_var->mlx, \
			cubed()->mx_var->screen_buffer.img);
	if (cubed()->mx_var->img)
		mlx_destroy_image(cubed()->mx_var->mlx, cubed()->mx_var->img);
	if (cubed()->mx_var->win)
		mlx_destroy_window(cubed()->mx_var->mlx, cubed()->mx_var->win);
	if (cubed()->mx_var->mlx)
		free(cubed()->mx_var->mlx);
} */

int	_terminate_cubed(void)
{
	/* t_cub	*cub;

	cub = cubed();
	destroy_game();
	_clean_content(cub->content);
	if (cub->player)
		free(cub->player);
	// _terminate_mx_var(cub->mx_var);
	_terminate_textures(cub->texture);
	if(cub->gmap)
		free(cub->gmap); */
		exit(0);
	return (EXIT_SUCCESS);
}
