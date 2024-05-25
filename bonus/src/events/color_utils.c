/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebmarque <ebmarque@student.42porto.com     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 14:39:16 by ebmarque          #+#    #+#             */
/*   Updated: 2024/05/23 16:03:51 by ebmarque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/core.h"

/**
 * Generates a 32-bit ARGB color value based on the given opacity, red, green, 
 * and blue values.
 * 
 * @param opacity The opacity value (0-255).
 * @param red The red value (0-255).
 * @param green The green value (0-255).
 * @param blue The blue value (0-255).
 * @return The generated 32-bit ARGB color value.
 */
int	gen_trgb(int opacity, t_rgb color)
{
	if (opacity > 255 || color.r > 255 || color.g > 255 || color.b > 255)
		return (0);
	return (opacity << 24 | color.r << 16 | color.g << 8 | color.b);
}

/**
 * Retrieves the opacity value from a 32-bit ARGB color value.
 * 
 * @param trgb The 32-bit ARGB color value.
 * @return The opacity value (0-255).
 */
int	get_opacity(int trgb)
{
	return ((trgb >> 24) & 0xFF);
}

/**
 * Retrieves the red value from a 32-bit ARGB color value.
 * 
 * @param trgb The 32-bit ARGB color value.
 * @return The red value (0-255).
 */
int	get_r(int trgb)
{
	return ((trgb >> 16) & 0xFF);
}

/**
 * Retrieves the green value from a 32-bit ARGB color value.
 * 
 * @param trgb The 32-bit ARGB color value.
 * @return The green value (0-255).
 */
int	get_g(int trgb)
{
	return ((trgb >> 8) & 0xFF);
}

/**
 * Retrieves the blue value from a 32-bit ARGB color value.
 * 
 * @param trgb The 32-bit ARGB color value.
 * @return The blue value (0-255).
 */
int	get_b(int trgb)
{
	return (trgb & 0xFF);
}
