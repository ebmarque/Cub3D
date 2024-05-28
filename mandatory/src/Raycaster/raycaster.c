/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiago <tiago@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 12:22:20 by tmoutinh          #+#    #+#             */
/*   Updated: 2024/05/28 20:38:52 by tiago            ###   ########.fr       */
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

int	render_screen(void)
{
	_black_window(&cubed()->mx_var->screen_buffer, 1.0f);
	_raycasting_loop();
	raycaster();
	mlx_put_image_to_window(cubed()->mx_var->mlx, cubed()->mx_var->win, \
		cubed()->mx_var->screen_buffer.img, 0, 0);
	return (EXIT_SUCCESS);
}
