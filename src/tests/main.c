/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebmarque <ebmarque@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 17:01:00 by ebmarque          #+#    #+#             */
/*   Updated: 2024/04/30 21:09:57 by ebmarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	void	*mlx;
	void	*mlx_win;
	t_data	*img;
	t_point	center;
} t_p;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	_black_window(t_p *game)
{
	
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			my_mlx_pixel_put(game->img, j, i, 0x00000000);
		}
	}
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->img->img, 0, 0);
} 



bool	_is_inside(t_point center, int y, int x, int lengh)
{
	if (x >= center.x - (lengh / 2) && x <= center.x + (lengh / 2))
	{
		if (y >= center.y - (lengh / 2) && y <= center.y + (lengh / 2))
			return true;
	}
	return false;
}


void draw_square(t_p *game, int lengh)
{
	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			if (_is_inside(game->center, y, x, lengh))
				my_mlx_pixel_put(game->img, x, y, 0x00FF0000);
		}
	}
}
void	_walk_up(t_p *game)
{
	if (game->center.y < HEIGHT && (game->center.y - 10) >= 0)
		game->center.y -= 10;
	draw_square(game, 10);

}

void	_walk_down(t_p *game)
{
	if (game->center.y < HEIGHT && (game->center.y + 10) >= 0)
		game->center.y += 10;
	draw_square(game, 10);

}

void	_walk_left(t_p *game)
{
	if (game->center.x < WIDTH && (game->center.x - 10) >= 0)
		game->center.x -= 10;
	draw_square(game, 10);
}

void	_walk_right(t_p *game)
{
	if (game->center.x < WIDTH && (game->center.x + 10) >= 0)
		game->center.x += 10;
	draw_square(game, 10);
}

int     read_keys(int key_pressed, void *param)
{
        t_p *img;

        img = (t_p *)param;
        if (key_pressed == ESC || !img)
                exit(0);
        else if (key_pressed == UP || key_pressed == 'w')
		{
			_black_window(img);
			_walk_up(img);
		}
        else if (key_pressed == DOWN || key_pressed == 's')
		{
			_black_window(img);
			_walk_down(img);
		}
        else if (key_pressed == LEFT || key_pressed == 'a')
		{
			_black_window(img);
			_walk_left(img);
		}
        else if (key_pressed == RIGHT || key_pressed == 'd')
		{
			_black_window(img);
			_walk_right(img);
		}
		else
			return (-1);
        mlx_put_image_to_window(img->mlx, img->mlx_win, img->img->img, 0, 0);
        return (0);
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



int	main(void)
{
	t_p *game;
	game = malloc(sizeof(t_p));
	ft_bzero(game, sizeof(t_p));
	game->mlx = NULL;
	game->mlx_win = NULL;
	game->center.x = WIDTH / 2;
	game->center.y = HEIGHT / 2;
	
	game->mlx = mlx_init();
	game->mlx_win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "Hello world!");

	game->img = malloc(sizeof(t_data));
    ft_bzero(game->img, sizeof(t_data));
	
	game->img->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->img->addr = mlx_get_data_addr(game->img->img, &game->img->bits_per_pixel, &game->img->line_length, &game->img->endian);

	// mlx_key_hook(game->mlx_win, read_keys, game);
	
	// draw_square(game, 10);
	mlx_hook(game->mlx_win, 2, 1L << 0, read_keys, game);
	mlx_hook(game->mlx_win, 17, 0, exit_game, game);
	mlx_loop_hook(game->mlx, read_keys, game);
	
	
	mlx_loop(game->mlx);
}
