/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_key.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkwak <tkwak@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 10:46:54 by tkwak             #+#    #+#             */
/*   Updated: 2024/06/06 10:46:55 by tkwak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

/**	[F]
 * @brief
 *	[ Definition ]
 * 	Handling the 'w' and 's' keys.
 *  Check the key-type (w || s) and key-action (press, repeat, release)
 *
 * 	[ Goal ]
 * 	Checks whether MLX_KEY_W or MLX_KEY_S is pressed or released,
 * 	and updates the state of the cub structure accordingly.
 * 
 * 	[ How to proceed ]
 * 	1. keydata.key
 * 		Check which key is pressed by the user (2 sorts)
 * 						  keys_t (typedef enum keys)
 * 		a. MLX_KEY_W	: 87	// move forward.
 * 		b. MLX_KEY_S	: 83	// move backward.
 *
 * 	2. keydata.action
 * 		Check the status of the keydata (3 sorts)
 * 						  action_t (typedef enum action)
 *		a. MLX_PRESS	: 	1	// key_w_pressed turns to '1'.
 *		b. MLX_REPEAT	:   2	// key_w_pressed turns to '1'.
 * 		c. MLX_REEASE	:   0	// key_w_pressed turns to '0'.
 * 
 * @param keydata
 * @param cub
 */
void	keys_ws(mlx_key_data_t keydata, t_main *cub)
{
	if (keydata.key == MLX_KEY_W)
	{
		if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
			cub->key_w_pressed = 1;
		if (keydata.action == MLX_RELEASE)
			cub->key_w_pressed = 0;
	}
	if (keydata.key == MLX_KEY_S)
	{
		if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
			cub->key_s_pressed = 1;
		if (keydata.action == MLX_RELEASE)
			cub->key_s_pressed = 0;
	}
}

/**	[F]
 * @brief 
 *	[ Definition ]
 * 	Handling the 'a' and 'd' keys.
 * 	It has the same function as "keys_ws". Please note that function.
 * 
 * @param keydata
 * @param cub 
 */
void	keys_ad(mlx_key_data_t keydata, t_main *cub)
{
	if (keydata.key == MLX_KEY_A)
	{
		if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
			cub->key_a_pressed = 1;
		if (keydata.action == MLX_RELEASE)
			cub->key_a_pressed = 0;
	}
	if (keydata.key == MLX_KEY_D)
	{
		if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
			cub->key_d_pressed = 1;
		if (keydata.action == MLX_RELEASE)
			cub->key_d_pressed = 0;
	}
}

/**	[F]
 * @brief
 * 	[ Definition ]
 * 	Handling the 'left' and 'right' keys.
 * 	It has the same function as "keys_ws". Please note that function.
 * 
 * @param keydata 
 * @param cub 
 */
void	keys_left_right(mlx_key_data_t keydata, t_main *cub)
{
	if (keydata.key == MLX_KEY_LEFT)
	{
		if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
			cub->key_left_pressed = 1;
		if (keydata.action == MLX_RELEASE)
			cub->key_left_pressed = 0;
	}
	if (keydata.key == MLX_KEY_RIGHT)
	{
		if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
			cub->key_right_pressed = 1;
		if (keydata.action == MLX_RELEASE)
			cub->key_right_pressed = 0;
	}
}

/**	[F]
 * @brief
 * 	[ Must ]
 *	All event handlers must be registered before executing mlx_loop
 * 	to respond appropriately when an event occurs.
 * 
 * 	[ Definition ]
 * 	Call-back function for the 'mlx_key_hook' function.
 * 	ex) This function is executed when a specific button is pressed.
 * 
 * 	[ Goal ]
 * 	It is used to handle key events (w,s,a,d,left,right,escape).
 * 
 * 	[ Background ]
 * 	mlx_key_data_t
 * 		keys_t		key;
 * 		action_t	action;
 * 	= check the funtion("keys_ws")'s note.
 * 
 * 	[ How to proceed ]
 * 	1. new_cub = (t_main *)origin_cub;
 * 	 = Cpy the origin_cub to new_cub.
 * 	 = Why?
 * 		It is copied and used to release the memory,
 * 		in case function terminats during execution because of 'escape'.
 * 	 = Acutally don't need it but for high readability.
 * 
 * 	2. keys_ws, keys_ad, keys_left_right;
 * 	 = Update datas based on pressed button,
 *	   and save the updated data to the (*cub).
 *
 * 	3. If (key: ESCAPE, action: PRESS) -> yes
 * 	 = Terminate (mlx) and free the struct (new_cub).
 *   = Ends the program.
 * 
 * @param keydata 
 * @param cub 
 */
void	keyhook(mlx_key_data_t keydata, void *origin_cub)
{
	t_main	*new_cub;

	new_cub = (t_main *)origin_cub;
	keys_ws(keydata, origin_cub);
	keys_ad(keydata, origin_cub);
	keys_left_right(keydata, origin_cub);
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		mlx_terminate(new_cub->mlx);
		free_cub(new_cub);
		exit(0);
	}
}
