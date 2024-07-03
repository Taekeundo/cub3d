/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_0.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkwak <tkwak@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 10:48:04 by tkwak             #+#    #+#             */
/*   Updated: 2024/06/06 10:48:05 by tkwak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

void	ft_error(char *str, t_main *cub)
{
	write(2, "Error\n", 6);
	write(2, str, (int)ft_strlen(str));
	if (cub)
		free_cub(cub);
	exit(EXIT_FAILURE);
}

void	delete_textures(t_main *cub)
{
	int	i;

	i = 0;
	while (i < NUM_TEXTURES)
	{
		mlx_delete_texture(cub->textures[i]);
		i++;
	}
}

void	closehook(void *param)
{
	t_main	*cub;

	cub = (t_main *)param;
	mlx_terminate(cub->mlx);
	free_cub(cub);
	exit(EXIT_FAILURE);
}
