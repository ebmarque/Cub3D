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

t_cub	*cubed(void)
{
	static t_cub	cub;

	return (&cub);
}

int quit_game(void)
{
	exit(EXIT_SUCCESS);
	return (0);
}

static void	_init_img(t_img *img)
{
	img->mlx = cubed()->mx_var->mlx;
	img->win = cubed()->mx_var->win;
	img->img = mlx_new_image(img->mlx, WIDTH, HEIGHT);
	img->addr = mlx_get_data_addr(img->img, &img->bbp, \
		&img->line_length, &img->endian);
}
void	_init_gmap(void)
{
	t_gmap	*mini;

	mini = ft_calloc(1, sizeof(t_gmap));
	mini->map = cubed()->content->map;
	mini->tile = (float)((WIDTH * 0.25) / cubed()->content->matrix_dimensions.x);
	mini->player.x = cubed()->player->pos.x * mini->tile;
	mini->player.y = cubed()->player->pos.y * mini->tile;
	mini->player.is_set = 1;
	mini->player.teta = 0;
	_init_img(&mini->map_img);
	cubed()->gmap = mini;
	printf("posicao na matrix -> x: %0.3f y: %0.3f\n", cubed()->player->pos.x, cubed()->player->pos.y );
	printf("posicao na screen -> x: %0.3f y: %0.3f\n\n", cubed()->gmap->player.x, cubed()->gmap->player.y );
}


void	mx_var_init()
{
	cubed()->mx_var = ft_calloc(1, sizeof(t_mx_var));
	cubed()->mx_var->mlx = mlx_init();
	cubed()->mx_var->win = mlx_new_window(cubed()->mx_var->mlx, WIDTH, HEIGHT, "CUB3D");
	cubed()->mx_var->img = mlx_new_image(cubed()->mx_var->mlx, WIDTH, HEIGHT);
	_init_img(&cubed()->mx_var->screen_buffer);
	_init_gmap();
}

int main(int argc, char *argv[])
{
	_check_errors(argc, argv);
	mx_var_init();
	mlx_hook(cubed()->mx_var->win, WIN_DESTROY, DESTROY_MASK, quit_game, NULL);
	mlx_hook(cubed()->mx_var->win, KEY_PRESSED, KEY_P_MASK, _key_pressed, cubed()->player);
	mlx_hook(cubed()->mx_var->win, KEY_RELEASED, KEY_R_MASK, _key_release, cubed()->player);
	mlx_loop_hook(cubed()->mx_var->mlx, _raycasting_loop, cubed()->player);
	mlx_loop(cubed()->mx_var->mlx);
	return (0);
}
