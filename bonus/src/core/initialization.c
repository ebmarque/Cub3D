/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebmarque <ebmarque@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 17:48:30 by ebmarque          #+#    #+#             */
/*   Updated: 2024/06/04 19:07:32 by ebmarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/core.h"

void	_load_sprite(void)
{
	t_sprite	*s;

	s = ft_calloc(1, sizeof(t_sprite));
	s->sprites = ft_calloc(NB_SPRITES, sizeof(t_texture));
	s->sprites[0] = _upload_texture(SPRITE_1);
	s->sprites[1] = _upload_texture(SPRITE_2);
	s->sprites[2] = _upload_texture(SPRITE_3);
	s->current_frame = 0;
	s->time = clock();
	cubed()->sprite = s;
}

void	_load_textures(void)
{
	cubed()->texture = ft_calloc(5, sizeof(t_texture));
	cubed()->texture[NORTH] = _upload_texture(cubed()->content->no_t);
	cubed()->texture[SOUTH] = _upload_texture(cubed()->content->so_t);
	cubed()->texture[EAST] = _upload_texture(cubed()->content->ea_t);
	cubed()->texture[WEST] = _upload_texture(cubed()->content->we_t);
	cubed()->door = _upload_texture(DOOR_PATH);
	_load_sprite();
}

void	_init_gmap(void)
{
	t_gmap	*mini;

	mini = ft_calloc(1, sizeof(t_gmap));
	mini->map = cubed()->content->map;
	mini->tile = (float)((WIDTH * 0.25) / \
		cubed()->content->matrix_dimensions.x);
	mini->player.x = cubed()->player->pos.x * mini->tile;
	mini->player.y = cubed()->player->pos.y * mini->tile;
	mini->player.is_set = 1;
	mini->player.teta = 0;
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
	t_pos	plane;

	plane = (t_pos){0, 0, 0, 0};
	if (cubed()->player->pos.teta == PI / 2)
		plane = (t_pos){+0.66, 0, 0, 0};
	else if (cubed()->player->pos.teta == 3 * (PI / 2))
		plane = (t_pos){-0.66, 0, 0, 0};
	else if (cubed()->player->pos.teta == PI)
		plane = (t_pos){0, +0.66, 0, 0};
	else if (cubed()->player->pos.teta == 0)
		plane = (t_pos){0, -0.66, 0, 0};
	cubed()->player->plane = plane;
}
