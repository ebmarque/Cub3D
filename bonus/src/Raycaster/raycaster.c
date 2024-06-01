/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebmarque <ebmarque@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 12:22:20 by tmoutinh          #+#    #+#             */
/*   Updated: 2024/06/01 18:43:57 by ebmarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/core.h"

void	raycaster(void)
{
	t_ray	ray;
	int		x;

	x = 0;
	while (x < WIDTH)
	{
		_render_floor(x);
		_render_ceiling(x);
		init_ray(&ray, x);
		get_side_dist(&ray);
		perform_dda(&ray);
		wall_placement(&ray);
		texture_render(&ray, x);
		x++;
	}
}

void	sprite(void)
{
	t_sprite	*sprite;

	sprite = cubed()->sprite;
	if (clock() - sprite->time >= FRAME_DELAY)
	{
		cubed()->sprite->current_frame += 1;
		if (cubed()->sprite->current_frame >= NB_SPRITES)
			cubed()->sprite->current_frame = 0;
		sprite->time = clock();
	}
	mlx_put_image_to_window(cubed()->mx_var->mlx, cubed()->mx_var->win, \
		sprite->sprites[sprite->current_frame]->img, (WIDTH / 2 - \
		sprite->sprites[sprite->current_frame]->width / 2), 0);
}

int	render_screen(void)
{
	_black_window(&cubed()->mx_var->screen_buffer, 1.0f);
	_raycasting_loop();
	raycaster();
	mlx_put_image_to_window(cubed()->mx_var->mlx, cubed()->mx_var->win, \
		cubed()->mx_var->screen_buffer.img, 0, 0);
	// sprite();
	if (cubed()->player->map_view == 1)
		_draw_map(cubed()->gmap);
	return (EXIT_SUCCESS);
}
