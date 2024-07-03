/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_init_window.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkwak <tkwak@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 10:45:19 by tkwak             #+#    #+#             */
/*   Updated: 2024/06/06 10:45:32 by tkwak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

/**	[F]
 * @brief 
 * 	[ Definition ]
 * 	Create a graphics window using the MLX library and attach images to the window.
 * 	= MLX 라이브러리를 사용하여 그래픽 창을 생성하고, 이미지를 윈도우에 연결.
 * 
 * 	[ Goal ]
 * 	1. Initialize the mlx and img members of the t_main structure.
 * 	= t_main 구조체의 member(mlx & img)를 초기화.
 * 
 * 	2. Set up the "Raycaster(NAME)" program's window and image.
 * 	= Name: "Raycaster" 프로그램의 윈도우와 이미지를 설정.
 * 
 * 	[ Logic ]
 * 	1. mlx_set_setting(MLX_STRETCH_IMAGE, false)
 * 		'MLX_STRETCH_IMAGE' 설정을 false로.
 * 		= Not stretch the image to match with the window size.
 * 		= Ex) window: 800 x 600 pixel
 * 			  Image:  400 x 300 pixel
 * 			  -> !! not muliple !!
 * 			  -> Stick to use original size and scale.
 * 		= 이미지를 스트레칭하지 않겠다.
 * 	2. mlx_init(width, height, title, whether resize or not).
 * 		2-1. if (!cub->mlx): Fail to make the window // 윈도우 생성 실패 시.
 * 	3. mlx_new_image(mlx, width, height).
 * 		3-1. if (!cub->img): Fail to make the image // 이미지 생성 실패 시
 * 	4. mlx_image_to_window(mlx, image, pos.x, pos.y)
 * 		Display the created image in a window.
 * 		생성한 이미지를 윈도우에 표시.
 * 
 * @param cub 
 */
void	init_window(t_main *cub)
{
	mlx_set_setting(MLX_STRETCH_IMAGE, false);
	cub->mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "Raycaster", false);
	if (!cub->mlx)
		ft_error(ERR_MLX_WIN, cub);
	cub->img = mlx_new_image(cub->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!cub->img)
		ft_error(ERR_MLX_IMG, cub);
	if ((mlx_image_to_window(cub->mlx, cub->img, 0, 0) < 0))
		ft_error(ERR_MLX_IMGWIN, cub);
}
