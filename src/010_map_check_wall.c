#include "cub3d.h"

static	int	copy_old_map_inside_new_map(char **old_map, char **new_map)
{
	int	colum;
	int	line;

	line = -1;
	while (old_map[++line])
	{
		colum = -1;
		while (old_map[line][++colum] != '\0')
			new_map[line + 2][colum + 2] = old_map[line][colum];
	}
	return (0);
}

static	char	*creat_line_with_empty(int len)
{
	char	*new_line;
	int		count;

	new_line = malloc((len + 1) * sizeof(char));
	if (!new_line)
	{
		perror("Failed to allocate memory for new_map[i]");
		return (NULL);
	}
	count = -1;
	while (++count < len)
		new_line[count] = ' ';
	new_line[len] = '\0';
	return (new_line);
}

static	char	**create_new_map(t_main *cub)
{
	char	**new_map;
	int		count;

	new_map = malloc((cub->map.nrows + 5) * sizeof(char *));
	if (!new_map)
	{
		perror("Failed to allocate memory for new_map");
		return (NULL);
	}
	count = -1;
	while (++count < cub->map.nrows + 4)
	{
		new_map[count] = creat_line_with_empty(cub->map.ncols + 5);
		if (new_map[count] == NULL)
			return (NULL);
	}
	copy_old_map_inside_new_map(cub->map.data_c, new_map);
	return (new_map);
}

static int	check_char(char **map, int row, int colum, int last_row)
{
	int	len;

	if (!ft_isspace(map[row][colum + 1]) && map[row][colum + 1] != '1')
		return (1);
	if (!ft_isspace(map[row][colum - 1]) && map[row][colum - 1] != '1')
		return (1);
	if ((last_row - 1) > row)
	{
		len = ft_strlen(map[row + 1]);
		if ((len > colum) && !ft_isspace(map[row + 1][colum])
			&& map[row + 1][colum] != '1')
			return (1);
	}
	if (row > 0)
	{
		len = ft_strlen(map[row - 1]);
		if ((len > colum) && !ft_isspace(map[row - 1][colum])
			&& map[row - 1][colum] != '1')
			return (1);
	}
	return (0);
}

int	ft_map_surround_wall(t_main *cub)
{
	int		row;
	int		colum;
	int		len;
	char	**new_map;

	row = 0;
	new_map = create_new_map(cub);
	while (new_map[row] && row <= cub->map.nrows)
	{
		colum = 1;
		len = ft_strlen(new_map[row]);
		while (new_map[row][colum] && colum < len - 1)
		{
			if (new_map[row][colum] == ' ')
			{
				if (check_char(new_map, row, colum, cub->map.nrows + 4))
				{
					free_char_array(new_map);
					new_map = NULL;
					return (1);
				}
			}
			colum++;
		}
		row++;
	}
	free_char_array(new_map);
	return (0);
}
