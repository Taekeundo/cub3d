/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10_math.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkwak <tkwak@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 10:47:47 by tkwak             #+#    #+#             */
/*   Updated: 2024/06/06 10:47:48 by tkwak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

t_pt2d_d	calc_ray_dir(int x, t_pt2d_d raydr, t_pt2d_d dir, t_pt2d_d plane)
{
	double	camera_x;

	camera_x = 2 * x / (double)WIN_WIDTH - 1;
	camera_x = -camera_x;
	raydr.x = dir.x + plane.x * camera_x;
	raydr.y = dir.y + plane.y * camera_x;
	return (raydr);
}

t_pt2d_d	calc_delta_dist(t_pt2d_d delta_dist, t_pt2d_d raydr)
{
	if (raydr.x == 0)
		delta_dist.x = 1e30;
	else
		delta_dist.x = fabs(1 / raydr.x);
	if (raydr.y == 0)
		delta_dist.y = 1e30;
	else
		delta_dist.y = fabs(1 / raydr.y);
	return (delta_dist);
}

void	calc_step_and_side_dist(t_main *cub)
{
	if (cub->raydr.x < 0)
	{
		cub->step.x = -1;
		cub->side_dist.x = (cub->pos.x - cub->map_pos.x) * cub->delta_dist.x;
	}
	else
	{
		cub->step.x = 1;
		cub->side_dist.x = (cub->map_pos.x + 1.0 - cub->pos.x) \
		* cub->delta_dist.x;
	}
	if (cub->raydr.y < 0)
	{
		cub->step.y = -1;
		cub->side_dist.y = (cub->pos.y - cub->map_pos.y) * cub->delta_dist.y;
	}
	else
	{
		cub->step.y = 1;
		cub->side_dist.y = (cub->map_pos.y + 1.0 - cub->pos.y) \
		* cub->delta_dist.y;
	}
}

void	handle_wall_hit(t_main *cub, int side)
{
	cub->side = side;
	if (side == 0)
	{
		if (cub->step.x < 0)
			cub->wall_direction = TEXTURE_NO;
		else
			cub->wall_direction = TEXTURE_SO;
	}
	else
	{
		if (cub->step.y < 0)
			cub->wall_direction = TEXTURE_WE;
		else
			cub->wall_direction = TEXTURE_EA;
	}
}

/*	[?]
	[ Definition ]
	Digital Differential Algorithm.

	[ How to proceed ]
	1. 
*/
void	perform_dda(t_main *cub)
{
	int	hit;
	int	side;

	hit = 0;
	while (hit == 0)
	{
		if (cub->side_dist.x < cub->side_dist.y)
		{
			cub->side_dist.x += cub->delta_dist.x;
			cub->map_pos.x += cub->step.x;
			side = 0;
		}
		else
		{
			cub->side_dist.y += cub->delta_dist.y;
			cub->map_pos.y += cub->step.y;
			side = 1;
		}
		if (cub->map.data_i[cub->map_pos.x][cub->map_pos.y] > 0)
		{
			hit = 1;
			handle_wall_hit(cub, side);
		}
	}
}
