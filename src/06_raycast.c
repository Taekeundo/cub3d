/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   06_raycast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkwak <tkwak@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 10:46:59 by tkwak             #+#    #+#             */
/*   Updated: 2024/06/06 10:47:01 by tkwak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"
// using of the main Loop for the game 
// +-------------------+
// |  Hauptprogramm    |
// +-------------------+
//         |
//         v
// +-------------------+       Register Hook
// |   mlx_loop_hook   |      ---------------> +------------------+
// |                   |                       | Hook (ft_raycast)|
// |                   |---------------------->| +-------------+  |
// +-------------------+                       | | LOOP        |  |
//                                             | +-------------+  |
//                                            +------------------+

/**
 * @brief 
 * 
 * @param param 
 */
void	ft_raycast(void *param)
{
	t_main	*cub;
	int		x;

	cub = (t_main *)param;
	move_player(cub);
	clear_image(cub);
	x = 0;
	while (x < WIN_WIDTH)
	{
		cub->map_pos.x = cub->pos.x;
		cub->map_pos.y = cub->pos.y;
		cub->raydr = calc_ray_dir(x, cub->raydr, cub->dir, cub->plane);
		cub->delta_dist = calc_delta_dist(cub->delta_dist, cub->raydr);
		calc_step_and_side_dist(cub);
		perform_dda(cub);
		if (cub->side == 0)
			cub->perp_wall_dist = cub->side_dist.x - cub->delta_dist.x;
		else
			cub->perp_wall_dist = cub->side_dist.y - cub->delta_dist.y;
		draw_tex(cub, x);
		x++;
	}
}
