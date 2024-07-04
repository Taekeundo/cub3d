/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_init_cub.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkwak <tkwak@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 10:45:06 by tkwak             #+#    #+#             */
/*   Updated: 2024/06/06 10:45:14 by tkwak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

/**	[F]
 * @brief 
 * 	[ Definition ]
 * 	Initialize structures (t_main *cub)
 * 
 * 	[ Reference ]
 * 	typedef struct mlx
 * 	{
 * 		void*		window;		// window itself.
 * 		void*		context;	// context Abstracted opengl data.
 * 		int32_t		width;		// The width of the window.
 * 		int32_t		height;		// The height of the window.
 * 		double		delta_time; // The time difference between
 * 								// the previous frame and current time.
 * 	}	mlx_t;
 * 
 * 	[ Memo ]
 * 	key_w,s,d,a_pressed		// Keys for 4 directions for moving.
 * 	key_left, right_pressed	// Keys for 2 directions for rotating.
 * 
 * @param argc 
 * @param argv 
 * @param cub 
 */
void	init_cub(int argc, char **argv, t_main *cub)
{
	cub->key_w_pressed = 0;
	cub->key_s_pressed = 0;
	cub->key_a_pressed = 0;
	cub->key_d_pressed = 0;
	cub->key_left_pressed = 0;
	cub->key_right_pressed = 0;
	cub->texture_alloc = 0;
	cub->tex_paths_alloc = 0;
	cub->move_speed = SQRS_PER_SEC / 100;
	cub->rot_speed = RADS_PER_SEC / 100;
	cub->pitch = 100;
	cub->map.data_c = 0;
	cub->map.data_i = 0;
	cub->map.c_alloc = 0;
	cub->map.i_alloc = 0;
	cub->dir.x = 0;
	cub->dir.y = 0;
	init_data_from_file(argv, cub);
	if (argc == 3 && !ft_strcmp(argv[2], "test"))
		display_cub_info(cub);
}

/**	[F]
 * @brief 
 * 	[ Definition ]
 * 	Initialize all flags for 4 directions & floor, ceiling.
 * 
 * @param cub 
 */
void	init_fileflags(t_main *cub)
{
	cub->fileflags.no = 0;
	cub->fileflags.so = 0;
	cub->fileflags.we = 0;
	cub->fileflags.ea = 0;
	cub->fileflags.floor = 0;
	cub->fileflags.ceiling = 0;
}
