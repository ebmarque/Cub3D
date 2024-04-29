/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoutinh <tmoutinh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 14:35:59 by tmoutinh          #+#    #+#             */
/*   Updated: 2024/04/29 21:52:15 by tmoutinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Raycaster/raycaster.h"
#include "../includes/core_t.h"

t_cub	*cubed(void)
{
	static t_cub	cub;

	return (&cub);
}

void	mx_var_init()
{
	t_img	screen_buff;

	cubed()->mx_var->mlx = mlx_init();
	cubed()->mx_var->win = mlx_new_window(\
		cubed()->mx_var->mlx, SCREEN_W, SCREEN_H, "Cub3D");
	cubed()->mx_var->img = mlx_new_image(cubed()->mx_var->mlx, \
		SCREEN_W, SCREEN_H);
	screen_buff.img = mlx_new_image(cubed()->mx_var->mlx, SCREEN_H, SCREEN_W);
	screen_buff.addr = (int *)mlx_get_data_addr(screen_buff.img,
			&screen_buff.bbp, &screen_buff.line_length,
			&screen_buff.endian);
	cubed()->mx_var->screen_buffer = screen_buff;
}

void	destroy_game()
{
	if (cubed()->mx_var->screen_buffer.img)
		mlx_destroy_image(cubed()->mx_var->mlx, cubed()->mx_var->screen_buffer.img);
	if (cubed()->mx_var->img)
		mlx_destroy_image(cubed()->mx_var->mlx, cubed()->mx_var->img);
	if (cubed()->mx_var->win)
		mlx_destroy_window(cubed()->mx_var->mlx, cubed()->mx_var->win);
	if (cubed()->mx_var->mlx)
	{	
		mlx_destroy_display(cubed()->mx_var->mlx);
		free(cubed()->mx_var->mlx);
	}
}

void	quit_game(void)
{
	/*Bene tens algum sanitize ja pronto?*/
	destroy_game();
}

void	game_sequence()
{
	mx_var_init();
	mlx_hook (cubed()->mx_var->win, WIN_DESTROY, DESTROY_MASK, quit_game, NULL);
}

int	main(int argc, char**argv)
{
	if (argc != 2)
		_exit_error("Error\nInvalid number of arguments\n");
	game_sequence();
	return (0);
}