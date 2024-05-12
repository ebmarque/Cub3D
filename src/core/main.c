#/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebmarque <ebmarque@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 15:44:41 by ebmarque          #+#    #+#             */
/*   Updated: 2024/04/23 15:44:44 by ebmarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/core.h"

int quit_game(void)
{
	exit(EXIT_SUCCESS);
	return (0);
}

void	mx_var_init()
{

	cubed()->mx_var = ft_calloc(1, sizeof(t_mx_var));
	cubed()->mx_var->mlx = mlx_init();
	cubed()->mx_var->win = mlx_new_window(cubed()->mx_var->mlx, WIDTH, HEIGHT, "TEST");
	cubed()->mx_var->img = mlx_new_image(cubed()->mx_var->mlx, WIDTH, HEIGHT);
	cubed()->mx_var->screen_buffer.img = mlx_new_image(cubed()->mx_var->mlx, WIDTH, HEIGHT);
	cubed()->mx_var->screen_buffer.mlx = cubed()->mx_var->mlx;
	cubed()->mx_var->screen_buffer.win = cubed()->mx_var->win;
	cubed()->mx_var->screen_buffer.addr = mlx_get_data_addr(cubed()->mx_var->screen_buffer.img, \
		&cubed()->mx_var->screen_buffer.bbp, &cubed()->mx_var->screen_buffer.line_length, \
		&cubed()->mx_var->screen_buffer.endian);
}

int main(int argc, char *argv[])
{
	// t_cub	cub;
	_check_errors(argc, argv);
	mx_var_init();
	mlx_hook(cubed()->mx_var->win, WIN_DESTROY, DESTROY_MASK, quit_game, NULL);
	mlx_hook(cubed()->mx_var->win, KEY_PRESSED, KEY_P_MASK, _key_pressed, cubed()->player);
	mlx_hook(cubed()->mx_var->win, KEY_RELEASED, KEY_R_MASK, _key_release, cubed()->player);
	mlx_loop_hook(cubed()->mx_var->mlx, _raycasting_loop, cubed()->player);
	mlx_loop(cubed()->mx_var->mlx);
	return (0);
}
