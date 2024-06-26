/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebmarque <ebmarque@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:17:13 by ebmarque          #+#    #+#             */
/*   Updated: 2024/05/29 00:45:26 by ebmarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/core.h"

void	_load_textures(void)
{
	cubed()->texture = ft_calloc(5, sizeof(t_texture));
	cubed()->texture[NORTH] = _upload_texture(cubed()->content->no_t);
	cubed()->texture[SOUTH] = _upload_texture(cubed()->content->so_t);
	cubed()->texture[EAST] = _upload_texture(cubed()->content->ea_t);
	cubed()->texture[WEST] = _upload_texture(cubed()->content->we_t);
}

void	_init_gmap(void)
{
	t_gmap	*mini;

	mini = ft_calloc(1, sizeof(t_gmap));
	mini->map = cubed()->content->map;
	mini->tile = \
		(float)((WIDTH * 0.25) / cubed()->content->matrix_dimensions.x);
	mini->player.x = cubed()->player->pos.x * mini->tile;
	mini->player.y = cubed()->player->pos.y * mini->tile;
	mini->player.is_set = 1;
	mini->player.teta = 0;
	_init_img(&mini->map_img);
	cubed()->gmap = mini;
	cubed()->player->map_view = 1;
}

t_texture	*_upload_texture(char *path)
{
	t_texture	*text;

	text = ft_calloc(1, sizeof(t_texture));
	text->img = mlx_xpm_file_to_image(cubed()->mx_var->mlx, path,
			&(text->width), &(text->height));
	text->addr = mlx_get_data_addr(text->img, &text->bpp, &text->line_len,
			&text->endian);
	return (text);
}

void	update_player(void)
{
	t_pos	p;

	p = cubed()->player->plane;
	if (cubed()->player->pos.teta == PI / 2)
		p = (t_pos){+0.66, 0, 0, 0};
	else if (cubed()->player->pos.teta == 3 * (PI / 2))
		p = (t_pos){-0.66, 0, 0, 0};
	else if (cubed()->player->pos.teta == PI)
		p = (t_pos){0, +0.66, 0, 0};
	else if (cubed()->player->pos.teta == 0)
		p = (t_pos){0, -0.66, 0, 0};
	cubed()->player->plane = p;
}
