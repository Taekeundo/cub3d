/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_check_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkwak <tkwak@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 10:44:35 by tkwak             #+#    #+#             */
/*   Updated: 2024/06/06 10:44:37 by tkwak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

/**
 * @brief 
 *	Check the (ac, av) condition, matching with the PDF.
 * @param argc 
 * @param argv 
 */
void	check_map_command(int argc, char **argv)
{
	int	i;

	if (argc < 2 || argc > 3)
		ft_error(ERR_ARGS, NULL);
	i = ft_strlen(argv[1]);
	if (ft_strnstr(&argv[1][i - 4], ".cub", 4) == NULL)
		ft_error(ERR_FILETYPE, NULL);
}

int	ft_sc_utils1(char **cmap, int x, int y)
{
	if (cmap[x][y] == ' ' || cmap[x][y] == '\0')
		return (1);
	return (0);
}

int	ft_sc_utils2(t_main *cub, int x, int y)
{
	return ((ft_sc_utils1(cub->map.data_c, x + 1, y)
			+ ft_sc_utils1(cub->map.data_c, x - 1, y)
			+ ft_sc_utils1(cub->map.data_c, x, y + 1)
			+ ft_sc_utils1(cub->map.data_c, x, y - 1)));
}

int	ft_surround_check_utils3(t_main *cub)
{
	int	y;

	y = 0;
	while (y < (int)ft_strlen(cub->map.data_c[0]))
	{
		if (cub->map.data_c[0][y] == '0')
			return (1);
		y++;
	}
	y = 0;
	while (y < (int)ft_strlen(cub->map.data_c[cub->map.nrows - 1]))
	{
		if (cub->map.data_c[cub->map.nrows - 1][y] == '0')
			return (1);
		y++;
	}
	return (0);
}

int	ft_surround_check(t_main *cub)
{
	int	x;
	int	y;

	if (ft_surround_check_utils3(cub))
		return (1);
	x = 0;
	while (x < cub->map.nrows)
	{
		y = 0;
		while (y < cub->map.longest_ncols)
		{
			if (cub->map.data_c[x][y] == '0')
				if (ft_sc_utils2(cub, x, y) > 0)
					return (1);
			y++;
		}
		x++;
	}
	return (0);
}
