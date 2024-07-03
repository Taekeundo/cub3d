/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   09_image.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkwak <tkwak@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 10:47:36 by tkwak             #+#    #+#             */
/*   Updated: 2024/06/06 10:47:37 by tkwak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

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
