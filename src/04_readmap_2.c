/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_readmap_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkwak <tkwak@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 10:46:21 by tkwak             #+#    #+#             */
/*   Updated: 2024/06/06 10:46:23 by tkwak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

void	malloc_map_i(t_main *cub)
{
	int		i;
	t_map	*map;

	map = &cub->map;
	map->data_i = (int **)malloc(map->nrows * sizeof(int *) + sizeof(char *));
	if (map->data_i == NULL)
		ft_error(ERR_MEM_ROWPTR, cub);
	map->i_alloc = 1;
	i = 0;
	while (i < map->nrows)
	{
		map->data_i[i] = (int *)malloc(map->ncols * sizeof(int) + 1);
		if (map->data_i[i] == NULL)
			ft_error(ERR_MEM_ROW, cub);
		i++;
	}
}

void	convert_map_data_c_to_i(t_main *cub)
{
	int		col;
	int		row;
	char	c;

	malloc_map_i(cub);
	row = 0;
	while (row < cub->map.nrows)
	{
		col = 0;
		while (col < cub->map.ncols)
		{
			c = cub->map.data_c[row][col];
			if (c == 'N' || c == 'S' || c == 'W' || c == 'E' || c == ' ')
				cub->map.data_i[row][col] = 0;
			else
				cub->map.data_i[row][col] = c - '0';
			col++;
		}
		row++;
	}
}

/* void	malloc_map_i(t_main *cub)
{
	int		i;
	t_map	*map;

	map = &cub->map;
	map->data_i = (int **)malloc(map->nrows * sizeof(int *) + sizeof(char *));
	//map->data_i = (int **)malloc(map->nrows * sizeof(int *));
	if (map->data_i == NULL)
		ft_error(ERR_MEM_ROWPTR, cub);
	map->i_alloc = 1;
	i = 0;
	while (i < map->nrows)
	{
		//map->data_i[i] = (int *)malloc(map->ncols * sizeof(int));
		map->data_i[i] = (int *)malloc(map->ncols * sizeof(int) + 1);
		if (map->data_i[i] == NULL)
			ft_error(ERR_MEM_ROW, cub);
		i++;
	}
}

// converts ' ' to 0 for now (in the end better if -1)
void	convert_map_data_c_to_i(t_main *cub)
{
	int		col;
	int		row;
	char	c;

	malloc_map_i(cub);
	row = 0;
	while (row < cub->map.nrows)
	{
		col = 0;
		while (col < cub->map.ncols)
		{
			c = cub->map.data_c[row][col];
			if (c == 'N' || c == 'S' || c == 'W' || c == 'E' || c == ' ')
				cub->map.data_i[row][col] = 0;
			else
				cub->map.data_i[row][col] = c - '0';
			col++;
		}
		row++;
	}
} */
