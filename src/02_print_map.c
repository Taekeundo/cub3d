/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_print_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkwak <tkwak@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 10:44:50 by tkwak             #+#    #+#             */
/*   Updated: 2024/06/06 10:44:52 by tkwak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

/**	[F]
 * @brief 
 * 	[ Definition ]
 * 	print all color by using 'bits operator'.
 * 
 * 	[ Logic ]
 * 	1. Send all digit from each color to the last 8digits.
 * 	2. Remove unnessary digits
 * 		Use 0xFF mask to remove high order bits and leave only low order 8 bits.
 * 	3. print all colors with (hexa-decimal)type.
 * 
 * 	[ Example ]
 * 	0xRRGGBBAA // 32bits integer.
 * 	red		== (0xRRGGBBAA >> 24) -> (0xRR) & (0xFF) -> 0xRR (red)
 * 	green	== (0xRRGGBBAA >> 16) -> (0xGG) & (0xFF) -> 0xGG (green)
 * 	blue	== (0xRRGGBBAA >>  8) -> (0xBB) & (0xFF) -> 0xBB (blue)
 *  alpha	== (0xRRGGBBAA >>  8) -> (0xAA) & (0xFF) -> 0xAA (alpha)
 * 
 * @param value 
 */
static void	print_color(int value)
{
	int	red;
	int	green;
	int	blue;
	int	alpha;

	red = (value >> 24) & 0xFF;
	green = (value >> 16) & 0xFF;
	blue = (value >> 8) & 0xFF;
	alpha = value & 0xFF;
	printf("0x%02X%02X%02X%02X", red, green, blue, alpha);
}

/** [F]
 * @brief
 *	[ Definition ]
 * 	print the 'char' version map to the terminal.
 * 
 * @param map 
 */
static void	print_map_char(t_map *map)
{
	int	row;
	int	col;

	row = 0;
	col = 0;
	printf("\nmap.data_char[%i][%i]:\n", map->nrows, map->ncols);
	while (row < map->nrows)
	{
		col = 0;
		while (col < map->ncols)
		{
			printf("%c", map->data_c[row][col]);
			col++;
		}
		printf("\n");
		row++;
	}
}

/** [F]
 * @brief
 * 	[ Definition ]
 * 	print the 'int' version map to the terminal.
 * 	
 * 	[ Memo ]
 * 	int map version is always rectangle shape.
 * 	All empty space filled with '0'.
 * 
 * @param map 
 */
static void	print_map_int(t_map *map)
{
	int	row;
	int	col;

	row = 0;
	col = 0;
	printf("\nmap.data_int[%i][%i]:\n", map->nrows, map->ncols);
	while (row < map->nrows)
	{
		col = 0;
		while (col < map->ncols)
		{
			printf("%i", map->data_i[row][col]);
			col++;
		}
		printf("\n");
		row++;
	}
}

/**	[F]
 * @brief 
 * 	[ Definition ]
 * 	Print all about 'cub'.
 * 	
 * 	[ What prints ]
 * 	1. texture paths (4ea)
 * 	2. color of floor, ceiling
 * 	3. char version map
 * 	4. int version map
 * 
 * 	[ Why ]
 * 	To check more detail and for evaluation.
 * 	
 * @param cub 
 */
void	display_cub_info(t_main *cub)
{
	printf("\n");
	printf("texture[0]: %s\n", cub->tex_paths[0]);
	printf("texture[1]: %s\n", cub->tex_paths[1]);
	printf("texture[2]: %s\n", cub->tex_paths[2]);
	printf("texture[3]: %s\n", cub->tex_paths[3]);
	printf("\nfloor color: ");
	print_color(cub->floor_color);
	printf("\n");
	printf("ceiling color: ");
	print_color(cub->ceiling_color);
	printf("\n");
	print_map_char(&cub->map);
	print_map_int(&cub->map);
}
