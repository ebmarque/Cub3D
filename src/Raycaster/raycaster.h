/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebmarque <ebmarque@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 12:22:08 by tmoutinh          #+#    #+#             */
/*   Updated: 2024/04/28 15:26:41 by ebmarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTER_H
# define RAYCASTER_H


//Screen width;
# define SCREEN_W 50
# define SCREEN_H 25
# include "test.h"
//For the absolute value function (fabs);
#include <math.h>
#include <stdbool.h>

typedef struct s_point
{
	double			x;
	double			y;
	double			teta;
}				t_pos;

typedef struct  s_ray
{
    //Start position of the ray [Player position];
    t_pos		pos;
    //Direction vector;
	t_pos		dir;
    //Direction in which the ray is going [Player orientation];
	t_pos		step;
    //Distance from one x or y side to the next x or y side;
	t_pos		delta_dist;
    //Distance from the player to the wall;
	t_pos		side_dist;
	int			side;
	double		wall_dist;
	double		wall_x;
	int			line_height;
	int			start;
	int			end;
}   t_ray;


#endif