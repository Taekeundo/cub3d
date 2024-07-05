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
static void	allocate_map_int(t_main *cub)
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

/**	[F]
 * @brief 
 *	[ Definition ]
 * 	check path and save it to the path array and return it.
 * 
 * @param cub 
 * @return char* 
 */
static char	*extract_texture_path(t_main *cub)
{
	char	path[PATH_MAX];
	int		i;

	i = 0;
	while (1)
	{
		if (cub->char_read == '\n')
			break ;
		path[i] = cub->char_read;
		i++;
		read_char(cub);
	}
	path[i] = '\0';
	i = 0;
	while (i < 4)
	{
		if (is_png_file(&path[i]) == 0)
			ft_error("path", cub);
		i++;
	}
	return (ft_strdup(path));
}

/**	[F]
 * @brief
 * 	[ Definition ]
 * 	Compare path with "Text" and distinguish each time and return it.
 * 
 * @param path 
 * @return int 
 */
static int	get_texture_index(char *path)
{
	if (!ft_strcmp(path, "NO"))
		return (0);
	if (!ft_strcmp(path, "SO"))
		return (1);
	if (!ft_strcmp(path, "WE"))
		return (2);
	if (!ft_strcmp(path, "EA"))
		return (3);
	return (-1);
}

/**	[F]
 * @brief 
 * 	[ Definition ]
 * 	Parsing (texture) identifier.
 * 
 * 	[ Logic ]
 * 	1. Compare (Param2)path's char one by one
 * 		with the cub->char_read by using the [f]match_char.
 * 		// while (cub->char_read == ' ')
 * 		= ex) NO' ' // currently read until here.
 * 	2. chosen_fileflag = choose_fileflag(cub, path);
 * 		Check, loaded texts match in which fileflags (no, so, we, ea, f, c)
 * 		by using [f] choose_fileflag.
 * 		
 * 		2-1. if (*chosen_fileflag == 1)
 * 			Already certain fileflag is assigned. (ex) flieflag.no = 1.
 * 			= Prevent duplication.
 * 	3. get_texture_index(path);
 * 		Check which texture it is and save it to 'i_texture_path'.
 * 		0	: NO
 * 		1	: SO
 * 		2	: WE
 * 		3	: EA
 * 		-1	: else
 * 	4. Save the path of current texture to the tex_paths[i_texture_path].
 * 	5. If texture found successfully, change flags
 * 		for "tex_paths_alloc" & "chosen_fileflag".
 * 
 * 	[ Fix for norm ]
 * 	(Original)
 *	if (*chosen_fileflag == 1)
 *	 	ft_error(ERR_DUPL_TEX, cub);
 * 
 * @param cub 
 * @param path 
 * @return true 
 * @return false 
 */
bool	parse_texture_identifier(t_main *cub, char *path)
{
	bool	*chosen_fileflag;
	int		i_texture_path;

	if (match_char(cub, path[0]))
	{
		read_char(cub);
		if (match_char(cub, path[1]))
		{
			read_char(cub);
			while (cub->char_read == ' ')
				read_char(cub);
			chosen_fileflag = choose_fileflag(cub, path);
			if (*chosen_fileflag == 1)
				ft_error("Invalid file format", cub);
			i_texture_path = get_texture_index(path);
			cub->tex_paths[i_texture_path] = extract_texture_path(cub);
			cub->tex_paths_alloc = true;
			*chosen_fileflag = true;
			return (1);
		}
		else
			ft_error(ERR_PREFIXES, cub);
	}
	return (0);
}
