/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   11_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkost <rkost@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 14:00:19 by rkost             #+#    #+#             */
/*   Updated: 2024/07/05 14:00:54 by rkost            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

/**
 * @brief Draws the ceiling and floor 
 * 		for a given column on the screen.
 *
 * The `draw_floor_ceiling` function fills 
 * the areas above and below the wall stripe 
 * for the given column `x` on the screen. 
 * The wall stripe itself is drawn by the 
 * `draw_tex2` function, and this function 
 * is responsible for drawing the ceiling 
 * and floor.
 * 
 * @param cub A pointer to a `t_main` structure
 * 		that contains the current game state and
 * 		necessary data, including the colors for
 * 		the ceiling and floor as well as the image
 * 		data for rendering.
 * @param x The x-coordinate of the current column
 * 		on the screen where the ceiling and floor
 * 		should be drawn.
 */

void	draw_floor_ceiling(t_main *cub, int x)
{
	int	y;

	y = 0;
	while (y < cub->draw_start)
	{
		mlx_put_pixel(cub->img, x, y, cub->ceiling_color);
		y++;
	}
	y = cub->draw_end;
	while (y < WIN_HEIGHT)
	{
		mlx_put_pixel(cub->img, x, y, cub->floor_color);
		y++;
	}
}

/**
 * @brief Draws the wall texture for a given column 
 * 		on the screen.
 *
 * The `draw_tex3` function renders the wall texture 
 * for the specified column `x` from `draw_start` to 
 * `draw_end`. It calculates the correct texture 
 * y-coordinate for each screen pixel and draws the 
 * texture to the screen.
 *
 * @param cub A pointer to a `t_main` structure that
 * 				contains the current game state and 
 * 				necessary data, including the textures
 * 				for the wall and the image data for rendering.
 * @param x The x-coordinate of the current column on the 
 * 				screen where the wall texture should be drawn.
 * @param tex_x The x-coordinate of the texture for the wall
 * 				stripe.
 *
 * @details
 * - `step` is calculated to determine how much to advance
 * 	 	in the texture for each pixel row on the screen.
 * - `tex_pos` is initialized to the starting position 
 * 		in the texture and is updated for each pixel row.
 * - `tex_y` determines the vertical position within 
 * 		the texture based on `tex_pos`.
 * - The pixel value from the texture is extracted and 
 * 		used to set the pixel on the screen.
 * 
 * Why Bitshifting for `mlx_put_pixel`
 * 		These components are stored in a 32-bit value, 
 * 		with each component using 8 bits (1 byte). 
 * 		The structure is as follows:
 * 
 * R: 8 Bits (Bits 24 to 31)
 * G: 8 Bits (Bits 16 to 23)
 * B: 8 Bits (Bits 8 to 15)
 * A: 8 Bits (Bits 0 to 7)
 */
void	draw_tex3(t_main *cub, int x, int tex_x)
{
	double		step;
	double		tex_pos;
	int			y;
	u_int8_t	*pixel;
	int			tex_y;

	step = 1.0 * cub->textures[cub->wall_direction]->height / cub->line_height;
	tex_pos = 
		(cub->draw_start - cub->pitch - WIN_HEIGHT / 2 \
		+ cub->line_height / 2) * step;
	y = cub->draw_start;
	while (y < cub->draw_end)
	{
		tex_y = (int)tex_pos & (cub->textures[cub->wall_direction]->height - 1);
		tex_pos += step;
		pixel = &cub->textures[cub->wall_direction]->pixels[(tex_x + tex_y
				* cub->textures[cub->wall_direction]->width)
			* cub->textures[cub->wall_direction]->bytes_per_pixel];
		mlx_put_pixel(cub->img, x, y,
			pixel[0] << 24 | pixel[1] << 16 | pixel[2] << 8 | pixel[3]);
		y++;
	}
}
/**
 * @brief Calculates the texture x-coordinate and draws the wall 
 * texture for a given column on the screen.
 *
 * The `draw_tex2` function computes the correct `tex_x` 
 * coordinate for the wall texture based on the ray direction
 * and wall intersection, and then calls `draw_tex3` to render 
 * the texture on the screen.
 *
 * @param cub A pointer to a `t_main` structure that contains the 
 * 				current game state and necessary data, including 
 * 				texture information and the wall direction.
 * @param x The x-coordinate of the current column on the screen
 * 				where the wall texture should be drawn.
 *
 * @details
 * - `wall_x` is calculated to determine the horizontal position
 * 		of the wall hit based on the current ray's direction.
 * - `tex_x` is computed from `wall_x` to find the correct
 * 		horizontal texture coordinate for the wall.
 * - Adjustments to `tex_x` are made based on the ray's side 
 * 		and direction to correctly map the texture.
 * - `draw_tex3` is called to draw the wall texture from 
 * 		`draw_start` to `draw_end` using `tex_x` to 
 * 		access the correct texture data.
 */

void	draw_tex2(t_main *cub, int x)
{
	double	wall_x;
	int		tex_x;

	if (cub->side == 0)
		wall_x = cub->pos.y + cub->perp_wall_dist * cub->raydr.y;
	else
		wall_x = cub->pos.x + cub->perp_wall_dist * cub->raydr.x;
	wall_x -= floor((wall_x));
	tex_x = (wall_x * cub->textures[cub->wall_direction]->width);
	if (cub->side == 0 && cub->raydr.x > 0)
		tex_x = cub->textures[cub->wall_direction]->width - tex_x - 1;
	if (cub->side == 1 && cub->raydr.y < 0)
		tex_x = cub->textures[cub->wall_direction]->width - tex_x - 1;
	draw_tex3(cub, x, tex_x);
}

/**
 * @brief Draws the vertical stripe of the wall 
 * 			texture for a given column on the screen.
 *
 * The `draw_tex` function calculates the start and end 
 * positions for drawing the wall texture stripe based 
 * on the distance to the wall and the vertical field of 
 * view. It also adjusts the height of the wall stripe to 
 * match the perspective projection and handles edge cases
 * to ensure the drawing coordinates stay within screen bounds.
 * 
 * @param cub A pointer to a `t_main` structure that holds 
 * 				the game state and necessary data, including
 * 				the current wall distance, field of view, and
 * 				texture information.
 * @param x The x-coordinate of the column on the screen where
 * 				the wall texture stripe should be drawn.
 * 
 * @see draw_floor_ceiling
 * @see draw_tex2
 */
void	draw_tex(t_main *cub, int x)
{
	cub->draw_start = 0;
	cub->draw_end = 0;
	cub->line_height = WIN_HEIGHT / cub->perp_wall_dist;
	cub->draw_start = -cub->line_height / 2 + WIN_HEIGHT / 2 + cub->pitch;
	if (cub->draw_start < 0)
		cub->draw_start = 0;
	cub->draw_end = cub->line_height / 2 + WIN_HEIGHT / 2 + cub->pitch;
	if (cub->draw_end >= WIN_HEIGHT || cub->draw_end < 0)
		cub->draw_end = WIN_HEIGHT - 1;
	draw_floor_ceiling(cub, x);
	draw_tex2(cub, x);
}
