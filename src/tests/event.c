/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebmarque <ebmarque@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 13:11:21 by ebmarque          #+#    #+#             */
/*   Updated: 2024/05/01 13:28:13 by ebmarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"



int	read_keys(void *param)
{
        t_p *game;

        game = (t_p *)param;
        _black_window(game);
        if (game->w)
			_walk_up(game);
        if (game->s)
			_walk_down(game);
        if (game->a)
			_walk_left(game);
        if (game->d)
			_walk_right(game);
		draw_square(game, 10);
        mlx_put_image_to_window(game->mlx, game->mlx_win, game->img->img, 0, 0);
        return (0);
}

int	key_press(int key_pressed, void *param)
{
        t_p *game;

        game = (t_p *)param;
        if (key_pressed == ESC || !game)
               exit_game(game);
        if (key_pressed == UP || key_pressed == 'w')
			game->w = 1;
        if (key_pressed == DOWN || key_pressed == 's')
			game->s = 1;
        if (key_pressed == LEFT || key_pressed == 'a')
			game->a = 1;
        if (key_pressed == RIGHT || key_pressed == 'd')
			game->d = 1;
		else
			return (-1);
        return (0);
}

int	key_release(int key_pressed, void *param)
{
        t_p *game;

        game = (t_p *)param;
        if (key_pressed == ESC || !game)
               exit_game(game);
        if (key_pressed == UP || key_pressed == 'w')
			game->w = 0;
        if (key_pressed == DOWN || key_pressed == 's')
			game->s = 0;
        if (key_pressed == LEFT || key_pressed == 'a')
			game->a = 0;
        if (key_pressed == RIGHT || key_pressed == 'd')
			game->d = 0;
		else
			return (-1);
        return (0);
}
