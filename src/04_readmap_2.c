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

/** [F]
 * @brief
 * 	[ Definition ]
 * 	Allocate the 2dimensional array to the member(data_i) of cub struct.
 * 	= cub 구조체의 map 필드 내 data_i 2차원 배열을 할당.
 * 	= Not yet assign the data in this function.
 * 	
 * @param cub 
 */
void	allocate_map_int(t_main *cub)
{
	int		i;
	t_map	*map;

	i = 0;
	map = &cub->map;
	map->data_i = (int **)malloc(map->nrows * sizeof(int *) + sizeof(char *));
	if (map->data_i == NULL)
		ft_error(ERR_MEM_ROWPTR, cub);
	map->i_alloc = 1;
	while (i < map->nrows)
	{
		map->data_i[i] = (int *)malloc(map->ncols * sizeof(int) + 1);
		if (map->data_i[i] == NULL)
			ft_error(ERR_MEM_ROW, cub);
		i++;
	}
}

/** [F]
 * @brief 
 * 	[ Definition ]
 * 	Convert the original map, consist of 'char'type, to the 'int' type map.
 * 	= 캐릭터 맵 데이터를 숫자 맵 데이터로 변환
 * 
 * 	[ Goal ]
 * 	Numeric map data is easier to handle in various game or simulation logic.
 * 	= 숫자 맵 데이터는 다양한 게임이나 시뮬레이션 로직에서 다루기가 더 쉽다.
 * 
 * 	[ Logic ]
 * 	1. [f] allocate_map_int.
 * 		Allocate memory for the map, which is integer version 
 * 	2. double while loop
 * 		data_c 배열의 문자 데이터를 data_i 배열의 정수 데이터로 변환
 * 		'N', 'S', 'W', 'E', ' ' -> convert to -> 0
 * 		나머지 숫자 -> 실제 숫자 값으로 변환.
 * 
 * 	[ Example ]
 * 	(Before)
 * 	11111
 * 	100N1
 * 	11111
 * 
 * 	(after)
 * 	[1, 1, 1, 1, 1]
 * 	[1, 0, 0, 0, 1]
 * 	[1, 1, 1, 1, 1]
 * 
 * 	int data_i[3][5] = {
 * 	{1, 1, 1, 1, 1},
 * 	{1, 0, 0, 0, 1},
 * 	{1, 1, 1, 1, 1}
 * 	};
 * 
 * @param cub 
 */
void	convert_char_map_to_i(t_main *cub)
{
	int		col;
	int		row;
	char	c;

	col = 0;
	row = 0;
	allocate_map_int(cub);
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
