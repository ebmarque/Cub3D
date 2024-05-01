/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebmarque <ebmarque@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 13:10:47 by ebmarque          #+#    #+#             */
/*   Updated: 2024/05/01 13:26:53 by ebmarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	exit_game(void *data)
{
	t_p *game;
	game = (t_p *)data;

	if(game->img)
		free(game->img);
	if (game)
		free(game);
	exit(EXIT_SUCCESS);	
}

t_p *_init_mlx(void)
{
	t_p	*game;
	game = malloc(sizeof(t_p));
	ft_bzero(game, sizeof(t_p));
	game->img = malloc(sizeof(t_data));
    ft_bzero(game->img, sizeof(t_data));
	game->mlx = NULL;
	game->mlx_win = NULL;
	game->center.x = WIDTH / 2;
	game->center.y = HEIGHT / 2;
	game->mlx = mlx_init();
	game->mlx_win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "Hello world!");
	game->img->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->img->addr = mlx_get_data_addr(game->img->img, \
		&game->img->bits_per_pixel, &game->img->line_length, \
		&game->img->endian);
	return (game);
}
