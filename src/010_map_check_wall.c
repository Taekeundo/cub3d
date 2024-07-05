/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   010_map_check_wall.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkost <rkost@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 14:02:09 by rkost             #+#    #+#             */
/*   Updated: 2024/07/05 14:02:17 by rkost            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

/**
 * @brief Copies the old map into the new map with an offset.
 *
 * The function `copy_old_map_inside_new_map` copies the 
 * contents of the old map into the new map with a specified
 * offset. This ensures that the new map has extra space around
 * the original map data, useful for boundary checking.
 *
 * @param old_map A double pointer to the old map array.
 * @param new_map A double pointer to the new map array 
 * 				where the old map will be copied.
 * @return int Always returns 0.
 */
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

/**
 * @brief Creates a new map with extra space for 
 * 			boundary checking.
 *
 * The function `create_new_map` allocates and 
 * initializes a new map with additional rows and 
 * columns to facilitate boundary checking. 
 * It first allocates memory for the new map,
 * then creates each line with extra columns,
 * and finally copies the original map into the new map.
 *
 * @param cub A pointer to the `t_main` structure
 * 			that contains the original map.
 * @return char** Returns a pointer to the newly
 * 			created map, or NULL if memory allocation fails.
 */
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

/**
 * @brief Checks if a given character on the map is 
 * 			properly surrounded by walls or spaces.
 *
 * The function `check_char` verifies whether the 
 * character at the specified position (row, colum)
 * on the map is correctly surrounded by either walls
 * ('1') or spaces. It checks the characters to the left,
 * right, above, and below the specified position to 
 * ensure they are either walls or spaces.
 *
 * @param map A double pointer to the map array.
 * @param row The row index of the character to check.
 * @param colum The column index of the character to check.
 * @param last_row The index of the last row in the map.
 * @return int Returns 0 if the character is properly surrounded,
 * 			otherwise returns 1.
 */
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

/*	[ For testing ]
*/
static void	print_map_char_test(char **map)
{
	int	row;
	int	col;

	row = 0;
	col = 0;
	while (map[row])
	{
		printf("|");
		col = 0;
		while (map[row][col])
		{
			printf("%c", map[row][col]);
			col++;
		}
		printf("|\n");
		row++;
	}
}


/**
 * @brief Checks if the given map from the structure 
 * 			t_main is surrounded by walls.
 *
 * The function `ft_map_surround_wall` checks if the map 
 * contained in the structure `t_main` is completely surrounded
 * by walls. It creates a new map for this purpose and checks
 * each cell. If an empty space (' ') is found on the map, it must
 * be surrounded only by 1's or other empty spaces
 * to the left, right, top, and bottom.
 * 
 * @param cub A pointer to the `t_main` structure that contains the map.
 * @return int Returns 0 if the map is correctly surrounded by walls, 
 *             otherwise, an error code is returned.
 */
int	ft_map_surround_wall(t_main *cub)
{
	int		row;
	size_t	colum;
	char	**new_map;

	row = 0;
	new_map = create_new_map(cub);
	printf("ia here \n");
	print_map_char_test(new_map);
	while (new_map[row] && row <= cub->map.nrows + 3)
	{
		colum = 1;
		while (new_map[row][colum] && colum < ft_strlen(new_map[row]) - 1)
		{
			if (new_map[row][colum] == ' ')
			{
				if (check_char(new_map, row, colum, cub->map.nrows + 4))
					return (free_char_array(new_map));
			}
			colum++;
		}
		row++;
		printf("ia here %i \n", row);
	}
	free_char_array(new_map);
	return (0);
}
