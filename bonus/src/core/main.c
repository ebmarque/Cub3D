/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebmarque <ebmarque@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 14:35:59 by tmoutinh          #+#    #+#             */
/*   Updated: 2024/05/22 17:42:16 by ebmarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/core.h"

t_cub	*cubed(void)
{
	static t_cub	cub;

	return (&cub);
}

void	game_sequence()
{
	mx_var_init();
	_load_textures();
	mlx_hook (cubed()->mx_var->win, WIN_DESTROY, 1L<<17, quit_game, NULL);
	mlx_hook(cubed()->mx_var->win, KEY_PRESSED, 1L<<0, _key_pressed, cubed()->player);
	mlx_hook(cubed()->mx_var->win, KEY_RELEASED, 1L<<1, _key_release, cubed()->player);
	mlx_hook(cubed()->mx_var->win, MOUSE_CLICK, 1L<<2, _mouse_click, NULL);
	mlx_hook(cubed()->mx_var->win, MOUSE_MOTION, 1L<<6, _mouse_move, NULL);
	mlx_loop_hook(cubed()->mx_var->mlx, render_screen, NULL);
	mlx_loop(cubed()->mx_var->mlx);
}

int	main(int argc, char**argv)
{
	_check_errors(argc, argv);
	game_sequence();
	_clean_content(cubed()->content);
	return (0);
}