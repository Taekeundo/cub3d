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
