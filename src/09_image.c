/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   09_image.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkost <rkost@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 14:04:10 by rkost             #+#    #+#             */
/*   Updated: 2024/07/05 14:05:59 by rkost            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Clears the entire image by setting each pixel 
 * 	to a specific color.
 *
 * This function iterates over each pixel of the 
 * image and sets its color to opaque blue.
 * It essentially clears the image buffer.
 *
 * @param cub A pointer to the `t_main` structure that 
 * 	contains the image to be cleared. `cub->img` 
 * 	is a pointer to the `mlx_image_t` structure
 * 	representing the image that will be cleared.
 *
 * @see t_main
 * @see mlx_put_pixel
 * @see WIN_WIDTH
 * @see WIN_HEIGHT
 */
void	clear_image(t_main *cub)
{
	unsigned int	x;
	unsigned int	y;

	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			mlx_put_pixel(cub->img, x, y, 0x000000FF);
			x++;
		}
		y++;
	}
}
