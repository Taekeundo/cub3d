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

/**
 * @brief Calculates the ray direction vector 
 * 			for a given pixel on the screen.
 *
 * This function computes the direction vector 
 * of a ray that starts at the camera's position and 
 * passes through a specific pixel on the screen.
 * The direction is calculated based on the camera's
 * current view direction vector (`dir`) and the 
 * camera's plane vector (`plane`). The pixel's 
 * X-coordinate on the screen influences the direction
 * of the ray.
 * 
 * @param x The X-coordinate of the pixel on the 
 * 			screen (from 0 to \text{WIN\_WIDTH} - 1).
 * @param raydr A `t_pt2d_d` structure that will be
 * 			updated with the computed ray direction vector.
 * @param dir A `t_pt2d_d` structure representing
 * 			the current direction vector of the camera.
 * @param plane A `t_pt2d_d` structure representing the
 * 			camera plane vector, which is orthogonal 
 * 			to the direction vector.
 * @return The updated `raydr` structure containing
 * 			the computed ray direction vector.
 *
 * @see t_pt2d_d
 * @see WIN_WIDTH
 * @see dir
 * @see plane
 * 
 * Skizze
*      Camera
*		0(0,0)
*   	| \
*  		|  \---ray direction (raydr)
*  		|   \
* dir  -|    \
*   	|     \
*   	|      \
*   	|       \
*   	+--------> x (Pixel Coordinate)
*      		/
*          /
* 		plane
*/
t_pt2d_d	calc_ray_dir(int x, t_pt2d_d raydr,
		t_pt2d_d dir, t_pt2d_d plane)
{
	double	camera_x;

	camera_x = 2 * x / (double)WIN_WIDTH - 1;
	camera_x = -camera_x;
	raydr.x = dir.x + plane.x * camera_x;
	raydr.y = dir.y + plane.y * camera_x;
	return (raydr);
}

/**
 * @brief Calculates the distance to the next grid line
 * 		intersection for each axis.
 *
 * This function computes the distance to the next
 * grid line intersection based on the ray's direction 
 * vector (`raydr`). The distances are used in 
 * raycasting algorithms to determine how far the ray
 * travels before hitting the next horizontal or vertical
 * grid line.
 *
 * @param delta_dist A `t_pt2d_d` structure that will
 * 			be updated with the calculated distances to
 * 			the next grid line intersections.
 * @param raydr A `t_pt2d_d` structure representing
 * 			the ray direction vector.
 *
 * @return The updated `delta_dist` structure with the
 * 			calculated distances to the next grid line
 * 			intersections.
 *
 * @see t_pt2d_d
 * @see raydr
 */
t_pt2d_d	calc_delta_dist(t_pt2d_d delta_dist,
		t_pt2d_d raydr)
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

/**
 * @brief Calculates the step size and side 
 * 		distance for the next grid line intersection.
 *
 * This function calculates the step size (`step.x` and 
 * `step.y`) and the side distance (`side_dist.x` and 
 * `side_dist.y`) for the ray based on its direction vector
 * (`raydr`) and the current position. The step size determines
 * the direction in which the ray moves through the grid, while
 * the side distance calculates the distance from the current
 * position to the next vertical or horizontal grid line.
 *
 * The calculations are performed as follows:
 * - If `raydr.x < 0`, the ray is moving to the left, so `step.x` 
 * 		is set to `-1` and `side_dist.x` is calculated as
 *   	`(pos.x - map_pos.x) * delta_dist.x`.
 * - If `raydr.x >= 0`, the ray is moving to the right, so `step.x` 
 * 		is set to `1` and `side_dist.x` is calculated as
 *   	`(map_pos.x + 1.0 - pos.x) * delta_dist.x`.
 * - If `raydr.y < 0`, the ray is moving downward, so `step.y` 
 * 		is set to `-1` and `side_dist.y` is calculated as
 *   	`(pos.y - map_pos.y) * delta_dist.y`.
 * - If `raydr.y >= 0`, the ray is moving upward, so `step.y` 
 * 		is set to `1` and `side_dist.y` is calculated as
 *   	`(map_pos.y + 1.0 - pos.y) * delta_dist.y`.
 *
 * @param cub A pointer to the `t_main` structure that contains the
 * 			current state of the game, including the ray's direction,
 *          position, and delta distances for grid lines.
 * @see t_main
 * @see t_pt2d_d
 * @see raydr
 * @see side_dist
 * @see step
 */
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

/**
 * @brief Handles the collision with a wall and determines 
 * 		the wall texture based on the ray's direction.
 *
 * This function processes the collision detected by the
 * `perform_dda()` function. It determines which wall texture
 * to use based on the side of the collision (vertical or 
 * horizontal) and the direction of the ray.
 *
 * The texture assignments are based on the direction of 
 * the ray's step:
 * - If the ray hits a vertical wall (`side == 0`):
 *   - If `step.x < 0`, the ray came from the west 
 * 		(assign `TEXTURE_NO`).
 *   - If `step.x > 0`, the ray came from the east
 * 		(assign `TEXTURE_SO`).
 * - If the ray hits a horizontal wall (`side == 1`):
 *   - If `step.y < 0`, the ray came from the south
 * 		(assign `TEXTURE_WE`).
 *   - If `step.y > 0`, the ray came from the north
 * 		(assign `TEXTURE_EA`).
 * 
 * @param cub A pointer to the `t_main` structure that 
 * 				contains the current state of the raycasting
 * 				process, including the side of the collision
 * 				and the direction of the ray.
 *	@param side The side of the wall hit by the ray (0 for 
 * 				vertical, 1 for horizontal).
 */

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

/**
 * @brief Performs the Digital Differential Analyzer 
 * 		(DDA) algorithm for raycasting.
 *
 * This function advances the ray through the 2D grid
 * by incrementally updating the side distances
 * and map position until a collision with a wall 
 * is detected. The DDA algorithm is used to determine
 * the closest intersection of the ray with the grid lines.
 *
 * The function compares the side distances to determine 
 * which direction to move the ray:
 * - If the distance to the next vertical grid line (`side_dist.x`) 
 * 		is less than the distance to the next horizontal grid line 
 * 		(`side_dist.y`), the ray moves to the next vertical line.
 * - Otherwise, the ray moves to the next horizontal line.
 * 
 * Upon detecting a collision (when 
 * `map.data_i[cub->map_pos.x][cub->map_pos.y] > 0`), the function calls
 * `handle_wall_hit()` to handle the collision and determine the 
 * appropriate texture for the wall.
 *
 * @param cub A pointer to the `t_main` structure that contains the 
 * 				current state of the raycasting process, including 
 * 				the ray direction, position, side distances, delta 
 * 				distances, and map data.
 * @see t_main
 * @see handle_wall_hit
 * @see delta_dist
 * @see side_dist
 * @see step
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
