/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebmarque <ebmarque@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 18:34:20 by ebmarque          #+#    #+#             */
/*   Updated: 2024/05/08 14:56:36 by ebmarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/core.h"



static void	_draw_dir(t_pos p1, t_img *img, double teta)
{
	t_pos	p2;


	p2.x = p1.x - (cos(teta) * 200);
	p2.y = p1.y - (sin(teta) * 200);

	if (p2.x < 0 || p2.x > WIDTH)
	{
		while (p2.x < 0)
			p2.x += 1;
		while (p2.x > WIDTH)
			p2.x -= 1;
				
	}
	if (p2.y < 0 || p2.y > HEIGHT)
	{
		while (p2.y < 0)
			p2.y += 1;
		while (p2.y > HEIGHT)
			p2.y -= 1;
				
	}

    double dx = p2.x - p1.x;
    double dy = p2.y - p1.y;
    double steps = fmax(fabs(dx), fabs(dy));
    double x_increment = dx / steps;
    double y_increment = dy / steps;

    double x = p1.x;
    double y = p1.y;

    for (int i = 0; i < steps; i++)
	{
		my_mlx_pixel_put(img, (int)(round(x)), (int)(round(y)), 0xFFFFFFFF);
        x += x_increment;
        y += y_increment;
    }
}






