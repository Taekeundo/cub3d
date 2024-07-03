/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_readmap_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkwak <tkwak@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 10:46:14 by tkwak             #+#    #+#             */
/*   Updated: 2024/06/06 10:46:16 by tkwak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

void	read_map_characters(t_main *cub, char *onechar)
{
	int	read_check;

	while (1)
	{
		read_check = read(cub->fd, onechar, 1);
		if (read_check <= 0)
			break ;
		if (cub->char_read != '0' && cub->char_read != '1'
			&& cub->char_read != 'N' && cub->char_read != 'E'
			&& cub->char_read != 'S' && cub->char_read != 'W'
			&& cub->char_read != ' ' && cub->char_read != '\n')
			ft_error(ERR_INVALID_MAP_CHAR, cub);
		if (cub->char_read == '\n')
		{
			if (cub->map.ncols > cub->map.longest_ncols)
				cub->map.longest_ncols = cub->map.ncols;
			cub->map.ncols = 0;
			cub->map.nrows++;
		}
		else
			cub->map.ncols++;
		cub->char_read = *onechar;
	}
}

void	get_map_dims(t_main *cub)
{
	char	onechar;

	cub->map.nrows = 0;
	cub->map.ncols = 0;
	cub->map.longest_ncols = 0;
	read_map_characters(cub, &onechar);
	cub->map.nrows++;
	if (cub->map.ncols > cub->map.longest_ncols)
		cub->map.longest_ncols = cub->map.ncols;
	cub->map.ncols = cub->map.longest_ncols;
	cub->map.data_c = 0;
}

void	process_row(t_main *cub, int row)
{
	int		col;
	bool	detectingendoftheline;
	char	onechar;

	detectingendoftheline = 0;
	col = 0;
	while (col < cub->map.ncols)
	{
		if (detectingendoftheline == 0)
		{
			if (read(cub->fd, &onechar, 1) == 0)
				detectingendoftheline = 1;
			if (col == 0 && onechar == '\n')
				read(cub->fd, &onechar, 1);
			if (col > 0 && onechar == '\n')
				detectingendoftheline = 1;
		}
		if (detectingendoftheline == 0)
			cub->map.data_c[row][col] = onechar;
		if (detectingendoftheline == 1)
			cub->map.data_c[row][col] = ' ';
		col++;
	}
}

static void	malloc_map_c(t_main *cub)
{
	int		i;
	t_map	*map;

	map = &cub->map;
	map->data_c = (char **)malloc(map->nrows * sizeof(char *) + sizeof(char *));
	if (!map->data_c)
		ft_error(ERR_MEM_ROWPTR, cub);
	map->data_c[map->nrows] = 0;
	map->c_alloc = 1;
	i = 0;
	while (i < map->nrows)
	{
		map->data_c[i] = (char *)malloc(map->ncols * sizeof(char) + 1);
		if (!map->data_c[i])
			ft_error(ERR_MEM_ROW, cub);
		map->data_c[i][map->ncols] = '\0';
		i++;
	}
}

void	fill_map(t_main *cub)
{
	char	onechar;
	int		i;
	int		row;

	malloc_map_c(cub);
	close(cub->fd);
	cub->fd = open(cub->filename, O_RDONLY);
	if (cub->fd == -1)
		ft_error(ERR_FILE, cub);
	i = 0;
	while (i < cub->total_chars_read - 1)
	{
		read(cub->fd, &onechar, 1);
		i++;
	}
	row = 0;
	while (row < cub->map.nrows)
		process_row(cub, row++);
	close(cub->fd);
}
