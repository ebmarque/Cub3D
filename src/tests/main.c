/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebmarque <ebmarque@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 17:01:00 by ebmarque          #+#    #+#             */
/*   Updated: 2024/05/01 13:26:59 by ebmarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"



int	main(void)
{
	t_p *game;
	game = _init_mlx();
	mlx_hook(game->mlx_win, 2, 1L << 0, key_press, game);
	mlx_hook(game->mlx_win, 3, 1L << 1, key_release, game);
	mlx_hook(game->mlx_win, 17, 0, exit_game, game);
	mlx_loop_hook(game->mlx, read_keys, game);
	
	
	mlx_loop(game->mlx);
}
