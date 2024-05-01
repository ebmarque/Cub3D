/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoutinh <tmoutinh@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 14:35:59 by tmoutinh          #+#    #+#             */
/*   Updated: 2024/05/01 19:48:27 by tmoutinh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/core.h"

t_cub	*cubed(void)
{
	static t_cub	cub;

	return (&cub);
}

void	mx_var_init()
{
	t_img	screen_buff;

	cubed()->mx_var = ft_calloc(1, sizeof(t_mx_var));
	cubed()->mx_var->mlx = mlx_init();
	cubed()->mx_var->win = mlx_new_window(\
		cubed()->mx_var->mlx, WIDTH, HEIGHT, "Cub3D");
	cubed()->mx_var->img = mlx_new_image(cubed()->mx_var->mlx, \
		WIDTH, HEIGHT);
	screen_buff.img = mlx_new_image(cubed()->mx_var->mlx, HEIGHT - 1, WIDTH - 1);
	screen_buff.addr = mlx_get_data_addr(screen_buff.img,
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

int	quit_game(void)
{
	/*Bene tens algum sanitize ja pronto?*/
	destroy_game();
	exit(EXIT_SUCCESS);
}

void	_upload_texture(t_texture *text, char *path)
{
	printf("%s\nok\n", path);
	text->img = mlx_xpm_file_to_image(cubed()->mx_var->mlx, path,
			&(text->width), &(text->height));
	text->addr = mlx_get_data_addr(text->img, &text->bpp, &text->line_len,
			&text->endian);
}

void	_load_textures(void)
{
	cubed()->texture = ft_calloc(4 ,sizeof(t_texture));
	_upload_texture(cubed()->texture[NORTH],\
	cubed()->content->no_t);
	_upload_texture(cubed()->texture[SOUTH],\
	cubed()->content->so_t);
	_upload_texture(cubed()->texture[EAST],\
	cubed()->content->ea_t);
	_upload_texture(cubed()->texture[WEST],\
	cubed()->content->we_t);
}

void	game_sequence()
{
	mx_var_init();
	_load_textures();
	mlx_hook (cubed()->mx_var->win, WIN_DESTROY, DESTROY_MASK, quit_game, NULL);
	mlx_loop_hook(cubed()->mx_var->mlx, raycaster, NULL);
	mlx_loop(cubed()->mx_var->mlx);
}

int	main(int argc, char**argv)
{
	_check_errors(argc, argv);
	game_sequence();
	_clean_content(cubed()->content);
	return (0);
}