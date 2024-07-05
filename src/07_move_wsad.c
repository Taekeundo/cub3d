/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   07_move_wsad.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkost <rkost@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 14:03:10 by rkost             #+#    #+#             */
/*   Updated: 2024/07/05 14:03:13 by rkost            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Moves the player character forwards based on the current 
 * 		  direction and speed.
 *
 * This function updates the player's position in the game world 
 * by moving them forward in the direction specified by `cub->dir`
 * (direction vector). It checks for collisions by querying the 
 * `cub->map.data_i` 2D integer array to ensure the intended new position 
 * is not blocked (indicated by a value of `0` in the `data_i` array).
 *
 * The player's new position is computed as:
 * - `new_x = cub->pos.x + cub->dir.x * cub->move_speed`
 * - `new_y = cub->pos.y + cub->dir.y * cub->move_speed`
 *
 * The function checks the validity of these new positions:
 * - If moving in the x direction is valid (i.e., the cell at 
 * 		`(new_x, pos.y)` in `data_i` has a value of `0`), it 
 * 		updates `cub->pos.x`.
 * - If moving in the y direction is valid (i.e., the cell at
 * 		`(pos.x, new_y)` in `data_i` has a value of `0`), it 
 * 		updates `cub->pos.y`.
 *
 * @param cub A pointer to the `t_main` structure that contains
 * 			the current game state, including the player's 
 * 			position, direction, move speed, and the map data.
 *       	`cub->map.data_i` is a 2D array representing the 
 * 			game world, where `0` indicates a free space and 
 * 			other values represent obstacles or boundaries.
 * @see t_main
 * @see t_map
 * @see move_speed
 * @see direction
 */
void	move_forwards(t_main *cub)
{
	if (cub->map.data_i[(int)(cub->pos.x + cub->dir.x
			* cub->move_speed)][(int)(cub->pos.y)] == 0)
		cub->pos.x += cub->dir.x * cub->move_speed;
	if (cub->map.data_i[(int)(cub->pos.x)][(int)(cub->pos.y + cub->dir.y
			* cub->move_speed)] == 0)
		cub->pos.y += cub->dir.y * cub->move_speed;
}

/**
 *  @brief Moves the player character backwards based on the current 
 *        direction and speed.
 *
 * This function updates the player's position by moving them backwards 
 * in the direction opposite to `cub->dir` (direction vector). It checks 
 * for collisions by querying the `cub->map.data_i` 2D integer array to 
 * ensure the new position is not blocked (indicated by a value of `0`).
 *
 * The new position is computed as:
 * - `new_x = cub->pos.x - cub->dir.x * cub->move_speed`
 * - `new_y = cub->pos.y - cub->dir.y * cub->move_speed`
 *
 * The function updates the position only if the new position is valid.
 *
 * @param cub A pointer to the `t_main` structure that contains the 
 * 			current 
 *          game state, including position, direction, move speed, and 
 * 			map data.
 * @see t_main
 * @see t_map
 * @see move_speed
 * @see direction
 */
void	move_backwards(t_main *cub)
{
	if (cub->map.data_i[(int)(cub->pos.x - cub->dir.x
			* cub->move_speed)][(int)(cub->pos.y)] == 0)
		cub->pos.x -= cub->dir.x * cub->move_speed;
	if (cub->map.data_i[(int)(cub->pos.x)][(int)(cub->pos.y - cub->dir.y
			* cub->move_speed)] == 0)
		cub->pos.y -= cub->dir.y * cub->move_speed;
}

/**
 * @brief Moves the player character left based on the current direction 
 *        and speed.
 *
 * This function updates the player's position by moving them left relative 
 * to the current direction. It calculates the left movement using the 
 * perpendicular vector to `cub->dir`. It checks for collisions by querying
 * the `cub->map.data_i` 2D integer array to ensure the new position is not 
 * blocked (indicated by a value of `0`).
 *
 * The new position is computed as:
 * - `new_x = cub->pos.x - cub->dir.y * cub->move_speed`
 * - `new_y = cub->pos.y + cub->dir.x * cub->move_speed`
 *
 * The function updates the position only if the new position is valid.
 *
 * @param cub A pointer to the `t_main` structure that contains the current 
 *            game state, including position, direction, move speed, 
 * 			  and map data.
 * @see t_main
 * @see t_map
 * @see move_speed
 * @see direction
 */
void	move_left(t_main *cub)
{
	if (cub->map.data_i[(int)(cub->pos.x + -cub->dir.y
			* cub->move_speed)][(int)(cub->pos.y)] == 0)
		cub->pos.x += -cub->dir.y * cub->move_speed;
	if (cub->map.data_i[(int)(cub->pos.x)][(int)(cub->pos.y + cub->dir.x
			* cub->move_speed)] == 0)
		cub->pos.y += cub->dir.x * cub->move_speed;
}

/**
 * @brief Moves the player character right based on the current direction 
 *        and speed.
 *
 * This function updates the player's position by moving them right relative 
 * to the current direction. It calculates the right movement using the 
 * perpendicular vector to `cub->dir`. It checks for collisions by querying
 * the `cub->map.data_i` 2D integer array to ensure the new position is not
 * blocked (indicated by a value 
 * of `0`).
 *
 * The new position is computed as:
 * - `new_x = cub->pos.x + cub->dir.y * cub->move_speed`
 * - `new_y = cub->pos.y - cub->dir.x * cub->move_speed`
 *
 * The function updates the position only if the new position is valid.
 *
 * @param cub A pointer to the `t_main` structure that contains the current 
 *            game state, including position, direction, move speed, and 
 * 			  map data.
 * @see t_main
 * @see t_map
 * @see move_speed
 * @see direction
 */
void	move_right(t_main *cub)
{
	if (cub->map.data_i[(int)(cub->pos.x + cub->dir.y
			* cub->move_speed)][(int)(cub->pos.y)] == 0)
		cub->pos.x += cub->dir.y * cub->move_speed;
	if (cub->map.data_i[(int)(cub->pos.x)][(int)(cub->pos.y + -cub->dir.x
		* cub->move_speed)] == 0)
		cub->pos.y += -cub->dir.x * cub->move_speed;
}

/**
 * @brief Updates the player's position and orientation based on the current
 *        key states.
 *
 * The function calls the following functions based on the key states:
 * - `move_forwards(cub)` if the W key is pressed.
 * - `move_backwards(cub)` if the S key is pressed.
 * - `move_left(cub)` if the A key is pressed.
 * - `move_right(cub)` if the D key is pressed.
 * - `rotate_left(cub)` if the left arrow key is pressed.
 * - `rotate_right(cub)` if the right arrow key is pressed.
 *
 * @param cub A pointer to the `t_main` structure that contains the current 
 *            game state, including key states, player position, direction, 
 *            move speed, and map data.
 * @see t_main
 * @see move_forwards
 * @see move_backwards
 * @see move_left
 * @see move_right
 * @see rotate_left
 * @see rotate_right
 */
void	move_player(t_main *cub)
{
	if (cub->key_w_pressed)
		move_forwards(cub);
	if (cub->key_s_pressed)
		move_backwards(cub);
	if (cub->key_a_pressed)
		move_left(cub);
	if (cub->key_d_pressed)
		move_right(cub);
	if (cub->key_left_pressed)
		rotate_left(cub);
	if (cub->key_right_pressed)
		rotate_right(cub);
}

/* 
//when the map int is 0 then move           not 1 or ' ' 
//move forward if no wall in front of you
void	move_forwards(t_main *cub)
{
	if (cub->map.data_i[(int)(cub->pos.x + cub->dir.x
			* cub->move_speed)][(int)(cub->pos.y)] == 0)
		cub->pos.x += cub->dir.x * cub->move_speed;
	if (cub->map.data_i[(int)(cub->pos.x)][(int)(cub->pos.y + cub->dir.y
			* cub->move_speed)] == 0)
		cub->pos.y += cub->dir.y * cub->move_speed;

}

//move backwards if no wall behind you
void	move_backwards(t_main *cub)
{
	if (cub->map.data_i[(int)(cub->pos.x - cub->dir.x
			* cub->move_speed)][(int)(cub->pos.y)] == 0)
		cub->pos.x -= cub->dir.x * cub->move_speed;
	if (cub->map.data_i[(int)(cub->pos.x)][(int)(cub->pos.y - cub->dir.y
			* cub->move_speed)] == 0)
		cub->pos.y -= cub->dir.y * cub->move_speed;
}

// move left if no wall on the left side
void	move_left(t_main *cub)
{
	if (cub->map.data_i[(int)(cub->pos.x + -cub->dir.y
			* cub->move_speed)][(int)(cub->pos.y)] == 0)
		cub->pos.x += -cub->dir.y * cub->move_speed;
	if (cub->map.data_i[(int)(cub->pos.x)][(int)(cub->pos.y + cub->dir.x
			* cub->move_speed)] == 0)
		cub->pos.y += cub->dir.x * cub->move_speed;
}

// move right if no wall on the right side
void	move_right(t_main *cub)
{
	if (cub->map.data_i[(int)(cub->pos.x + cub->dir.y
			* cub->move_speed)][(int)(cub->pos.y)] == 0)
		cub->pos.x += cub->dir.y * cub->move_speed;
	if (cub->map.data_i[(int)(cub->pos.x)][(int)(cub->pos.y + -cub->dir.x
		* cub->move_speed)] == 0)
		cub->pos.y += -cub->dir.x * cub->move_speed;
} 



// if (mouse_moved)
// 	rotate_mouse(m);
void	move_player(t_main *cub)
{
	if (cub->key_w_pressed)
		move_forwards(cub);
	if (cub->key_s_pressed)
		move_backwards(cub);
	if (cub->key_a_pressed)
		move_left(cub);
	if (cub->key_d_pressed)
		move_right(cub);
	if (cub->key_left_pressed)
		rotate_left(cub);
	if (cub->key_right_pressed)
		rotate_right(cub);
} 
*/
