/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiago <tiago@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 14:35:59 by tmoutinh          #+#    #+#             */
/*   Updated: 2024/05/23 21:31:07 by tiago            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/core.h"

t_cub	*cubed(void)
{
	static t_cub	cub;

	return (&cub);
}

static void	_init_img(t_img *img)
{
	img->mlx = cubed()->mx_var->mlx;
	img->win = cubed()->mx_var->win;
	img->img = mlx_new_image(img->mlx, WIDTH * 0.25, HEIGHT * 0.25);
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

void	update_player()
{
	//cubed()->player->dir = (t_pos) {(int)roundf(cos(cubed()->player->dir.teta)),(int)roundf(sin(cubed()->player->dir.teta)),0,0};
	//cubed()->player->plane =  /* cubed()->player->dir; */(t_pos) {(int)roundf(cos(cubed()->player->dir.teta * 0.33)),(int)roundf(sin(cubed()->player->dir.teta * 0.33)),0,0};
	if (cubed()->player->dir.teta == PI/2)
	{
		//cubed()->player->dir = (t_pos) {-1, 0,0,0};
		cubed()->player->plane = (t_pos) {0.66,0,0,0};
	}
	else if (cubed()->player->dir.teta == 3 * (PI/2))
	{
		//cubed()->player->dir = (t_pos) {1,0,0,0};
		cubed()->player->plane = (t_pos) {-0.66,0,0,0};
	}
	else if (cubed()->player->dir.teta == PI)
	{
		//cubed()->player->dir = (t_pos) {0,1,0,0};
		cubed()->player->plane = (t_pos) {0, 0.66,0,0};
	}
	else if (cubed()->player->dir.teta == 0)
	{
		//cubed()->player->dir = (t_pos) {0,-1,0,0};
		cubed()->player->plane = (t_pos) {0,-0.66,0,0};
	}
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
	screen_buff.img = mlx_new_image(cubed()->mx_var->mlx, \
		WIDTH, HEIGHT);
	screen_buff.mlx = cubed()->mx_var->mlx;
	screen_buff.win = cubed()->mx_var->win;
	screen_buff.addr = mlx_get_data_addr(screen_buff.img,
			&screen_buff.bbp, &screen_buff.line_length,
			&screen_buff.endian);
	cubed()->mx_var->screen_buffer = screen_buff;
/* 	cubed()->player->pos.x = cubed()->content->p_position.y;
	cubed()->player->pos.y = cubed()->content->p_position.x; */
	cubed()->player->pos = to_screen_pos(cubed()->player->pos);
	update_player();
	//_init_img(&cubed()->mx_var->screen_buffer);
	_init_gmap();
	cubed()->gmap->map_img = screen_buff;
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

t_texture	*_upload_texture(char *path)
{
	t_texture	*text;
	
	text = ft_calloc(1 ,sizeof(t_texture));
	text->img = mlx_xpm_file_to_image(cubed()->mx_var->mlx, path,
			&(text->width), &(text->height));
	text->addr = mlx_get_data_addr(text->img, &text->bpp, &text->line_len,
			&text->endian);
	return (text);
}

void	_load_textures(void)
{
	cubed()->texture = ft_calloc(5 ,sizeof(t_texture));
	cubed()->texture[NORTH] = _upload_texture(cubed()->content->no_t);
	cubed()->texture[SOUTH] = _upload_texture(cubed()->content->so_t);
	cubed()->texture[EAST] = _upload_texture(cubed()->content->ea_t);
	cubed()->texture[WEST] = _upload_texture(cubed()->content->we_t);
}

void	game_sequence()
{
	mx_var_init();
	_load_textures();
	mlx_hook (cubed()->mx_var->win, WIN_DESTROY, DESTROY_MASK, quit_game, NULL);
	mlx_hook(cubed()->mx_var->win, KEY_PRESSED, KEY_P_MASK, _key_pressed, cubed()->player);
	mlx_hook(cubed()->mx_var->win, KEY_RELEASED, KEY_R_MASK, _key_release, cubed()->player);
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