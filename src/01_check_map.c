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

/**	[F]
 * @brief 
 * 	[ Definition ]
 * 	Check the (ac, av) condition, matching with the mendetory pary in PDF.
 * 
 * @param argc
 * 	2 <= argc <= 3 (2 or 3)
 * @param argv
 * 	[ Basic ]
 * 		argv[0]: Name of the program (= ./cub3D)
 * 		argv[1]: Directory of the maps (= maps/0.cub)
 * 
 * 	[ Test ]
 *  	argv[2]: For tge test (= test), else -> exit the program.
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

/**	[F]
 * @brief 
 * 	
 * 	[ Definition ]
 * 	If) meets with 'empty' or '\0' -> return (1)
 * 	else) return (0)
 * 
 * @param cmap 	// cub->map.data_c
 * @param x 	// position x
 * @param y 	// position y
 * @return int
 */
int	check_empty_null(char **cmap, int x, int y)
{
	if (cmap[x][y] == ' ' || cmap[x][y] == '\0')
		return (1);
	return (0);
}

/**	[F]
 * @brief 
 * 	[ Definition ]
 * 	Call "check_empty_null" for the four coordinates
 * 	(above, below, left, right) of the given coordinates (x, y)
 * 	to check whether they are empty spaces or null characters.
 * 	= 주어진 좌표 (x, y)의 상,하,좌,우 네 좌표에 대해
 * 	  'check_empty_null' 호출하여 빈 공간이거나 널 문자인지 확인.
 * 
 * 	[ Logic ]
 * 	!! four coordinates's sum !!
 * 	
 * 	[ Example 1 ]
 * 	11111						 (x, y)
 * 	10111		first '0' is now (1, 1)
 * 	10001
 * 	11111
 * 
 * 	x = 1	, y = 1		// (1, 1): 0
 * 	x + 1	, y			// (2, 1): 1 (right) : OK -> return (0)
 *	x - 1	, y			// (0, 1): 1 (left)	 : OK -> return (0)
 * 	x		, y + 1		// (1, 2): 0 (over)	 : OK -> return (0)
 * 	x		, y - 1		// (1, 0): 1 (below) : OK -> return (0)
 * 
 * 	[ Example 2 ]
 * 	11111						 (x, y)
 * 	00111		first '0' is now (0, 1)
 * 	10001
 * 	11111
 * 
 * 	x = 0	, y = 1
 * 	x + 1	, y			// (1 , 1): 0   (right)  : OK -> return (0)
 *	x - 1	, y			// (-1, 1): ' ' (left)	 : OK -> return (1)
 * 	x		, y + 1		// (0 , 2): 1 (over)	 : OK -> return (0)
 * 	x		, y - 1		// (0 , 0): 1 (below)    : OK -> return (0)
 * 
 * @param cub 
 * @param x 
 * @param y 
 * @return int 
 */
int	check_four_coordinates(t_main *cub, int x, int y)
{
	return ((check_empty_null(cub->map.data_c, x + 1, y)
			+ check_empty_null(cub->map.data_c, x - 1, y)
			+ check_empty_null(cub->map.data_c, x, y + 1)
			+ check_empty_null(cub->map.data_c, x, y - 1)));
}

/**	[F]
 * @brief
 * 	[ Definition ]
 * 	Check, whether the map's first row and last row are 0.
 * 
 * 	[ Logic ]
 * 	1. First while loop
 * 		check the first row, whether it consist of '0'.
 * 		= If '0' is found in the first or last line -> return (1)
 * 	2. Initialize y to '0' for second while loop.
 * 	3. Second while loop
 * 		check the last row, whether it consist of '0'.
 * 		= If '0' is found in the first or last line -> return (1)
 * 		
 * @param cub 
 * @return int 
 */
int	check_first_last_row(t_main *cub)
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

/**	[F]
 * @brief
 * 	[ Definition ]
 * 	Check every coordinates in maps, whether it's surrounded by the wall(1).
 * 
 * 	[ Logic ]
 * 	1. check_first_last_row
 * 	= Check first and last row in the maps, whether it's '0'.
 *  = 첫 번째 행, 마지막 행 '0'있는지 확인.
 * 
 * 	2. while (x < cub->map.nrows)
 * 	= Check every rows and columns.
 *  
 * 		2-1. if (cub->map.data_c[x][y] == '0')
 * 		= Since all lines are filled with 0
 * 		  based on the longest line in the function,
 * 		  the last column may be 0.
 * 		= 맵의 각 좌표 (x, y)에 대해, 그 위치가 '0'이면 'check_four_coordinates' 호출
 * 
 * 			3. if (check_four_coordinates(cub, x, y) > 0)
 * 			= Check whether the position (top, bottom, left, right)
 * 			  are valid from the current position which is found 0(value).
 * 			= 발견된 (0)의 위치로부터 상,하,좌,우가 유효한지 확인.
 * 			= 4개 중 하나라도 유효하지 않을 경우 return (1).
 * 
 * @param cub 
 * @return int // (0) is no error, (1) is error.
 */
int	check_surround_wall(t_main *cub)
{
	int	x;
	int	y;

	if (check_first_last_row(cub))
		return (1);
	x = 0;
	while (x < cub->map.nrows)
	{
		y = 0;
		while (y < cub->map.longest_ncols)
		{
			if (cub->map.data_c[x][y] == '0')
				if (check_four_coordinates(cub, x, y) > 0)
					return (1);
			y++;
		}
		x++;
	}
	return (0);
}
