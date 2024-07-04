#include "cub3d.h"
/**
 * @brief Main raycasting function for 
 * 		rendering the 3D scene.
 *
 * The `ft_raycast` function handles the core 
 * raycasting process for the game engine.
 * It processes each column of the screen 
 * to cast rays into the game world, perform
 * collision detection, calculate the distance 
 * to the nearest wall, and render the wall
 * texture based on the ray's interaction with the map.
 * 
 * This function performs the following steps:
 * 1. Moves the player based on input.
 * 2. Clears the previous frame's image.
 * 3. Iterates over each column of the screen 
 * 		(from left to right).
 * 4. Updates the player's position and direction 
 * 		for the current ray.
 * 5. Calculates the direction of the current ray.
 * 6. Computes the distance between grid lines and 
 * 		the step direction for the ray.
 * 7. Performs the DDA (Digital Differential Analysis) 
 * 		algorithm to find the wall hit point.
 * 8. Calculates the perpendicular distance to the 
 * 		wall for perspective projection.
 * 9. Draws the wall texture for the current column.
 * 
 * @param param A pointer to a `t_main` structure 
 * 				that contains game state information, 
 *              including player position, direction,
 * 				textures, and other necessary data.
 * 
 *  using of the main Loop for the game 
 * 	in main (ft_raycast is hook up in the main loop)
* +-------------------+
* |  Hauptprogramm    |
* +-------------------+
*         |
*         v
* +-------------------+       Register Hook
* |   mlx_loop_hook   |      ---------------> +------------------+
* |                   |                       | Hook (ft_raycast)|
* |                   |---------------------->| +-------------+  |
* +-------------------+                       | | LOOP  DRAW  |  |
*         |                                   | +-------------+  |
*   	  v	                                  +------------------+
* +-------------------+
* |Main Loop(mlx_loop)|
* +-------------------+
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
