/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_readmap_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rene <rene@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 10:46:14 by tkwak             #+#    #+#             */
/*   Updated: 2024/07/06 10:00:12 by rene             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
/**	[F]
 * @brief
 * 	[ Definition ]
 * 	
 * 	[ Logic ]
 * 	1. Read char one by one in the map.
 * 	2. If not allowed char -> error.
 * 	3. Handling newline('\n')
 * 		comparing (longest_ncols) with (current ncols), update.
 * 		= initialize index for (ncols) to '\0'.
 * 		= go to the next line in the map.
 * 	4. Not a newline -> go to the next char(ncols) in the same rows.
 * 	5. Update the current char(*onechar) to the member(cub->char_read).
 * 
 * @param cub 
 * @param one 
 */
static void	validate_map(t_main *cub, char *onechar)
{
	int	i_result_read;

	while (1)
	{
		i_result_read = read(cub->fd, onechar, 1);
		if (i_result_read <= 0)
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

/**	[F]
 * @brief
 * 	[ Definition ]
 * 	Check the size of the map in cub3D.
 * 
 * 	[ Logic ]
 * 	1. Initialize (nrows, ncols, longest_ncols) to '0'.
 * 	2. Validate maps (check every single char one by one).
 * 	3. Go to the last rows (cub->map.nrows++).
 * 	4. Update the longest_ncols.
 * 	5. Update the ncols from longest_ncols.
 * 	6. Initialize (map.data_c) to '0'.
 * 
 * @param cub 
 */
void	check_map_size(t_main *cub)
{
	char	one;

	cub->map.nrows = 0;
	cub->map.ncols = 0;
	cub->map.longest_ncols = 0;
	validate_map(cub, &one);
	cub->map.nrows++;
	if (cub->map.ncols > cub->map.longest_ncols)
		cub->map.longest_ncols = cub->map.ncols;
	cub->map.ncols = cub->map.longest_ncols;
	cub->map.data_c = 0;
}

/**	[F]
 * @brief 
 * 	[ Definition ]
 * 	Read one row by one row from the file,
 * 	store it in the cub->map.data_c[row][col] array.
 * 	!! All rows are stored as rectangles of length ncols, !!
 * 	!! which causes the map to have a rectangular shape.  !!
 * 
 * 	[ Example ]
 * 	' is one empty space
 * 
 * 	(Before)		free shape.
 * 	11111111
 * 	1000011111
 * 	111001111
 * 	   110111
 * 	1111111
 * 
 * 	(After)			must rectangle shape.
 * 	11111111''
 * 	1000011111
 * 	111001111'
 * 	'''110111'
 * 	1111111'''
 * 
 * 	[ Detail ]
 * 	row index를 사용하여 2D map의 특정 row을 읽어오는 기능을 수행.
 * 	cub->fd로부터 한 줄씩 데이터를 읽어와 cub->map.data_c[row]배열에 데이터를 저장.
 * 	데이터 읽기 중에 개행 문자를 처리.
 * 	개행 문자가 나오면 줄의 끝을 인식하고 공백으로 데이터를 채운다.
 * 
 * 	[ Background ]
 * 	flag_eol; // flag for the end of line ('\n').
 * 
 * 	[ Logic ]
 * 	1. Initialize "flag for end of line" and "col".
 * 	2. Check one line(col) by one line. (while loop)
 * 		Case
 * 		2-1. if (read(cub->fd, &one, 1) == 0)
 * 			= 파일의 끝에 도달하면
 * 		2-2. if (col == 0 && one == '\n')
 * 			= 첫 번째 col에서 '\n'문자 만나면
 * 		2-3. if (col > 0 && one == '\n')
 * 			= col의 중간에서 줄 바꿈 문자를 만나면
 * 
 * @param cub 
 * @param row
 */
static void	read_row_fill_rec_shape(t_main *cub, int row)
{
	int		col;
	bool	flag_eol;
	char	one;

	flag_eol = 0;
	col = 0;
	while (col < cub->map.ncols)
	{
		if (flag_eol == 0)
		{
			if (read(cub->fd, &one, 1) == 0)
				flag_eol = 1;
			if (col == 0 && one == '\n')
				read(cub->fd, &one, 1);
			if (col > 0 && one == '\n')
				flag_eol = 1;
		}
		if (flag_eol == 0)
			cub->map.data_c[row][col] = one;
		if (flag_eol == 1)
			cub->map.data_c[row][col] = ' ';
		col++;
	}
}

/**	[F]
 * @brief
 * 	[ Definition ]
 * 	cub 구조체의 맵 데이터를 저장할 2D 배열을 생성하고 초기화.
 * 	맵 데이터를 저장하기 위한 메모리 할당
 * 
 * @param cub 
 */
static void	allocate_map_char(t_main *cub)
{
	int		i;
	t_map	*map;

	i = 0;
	map = &cub->map;
	map->data_c = (char **)malloc(map->nrows * sizeof(char *) + sizeof(char *));
	if (!map->data_c)
		ft_error(ERR_MEM_ROWPTR, cub);
	map->data_c[map->nrows] = 0;
	map->c_alloc = 1;
	while (i < map->nrows)
	{
		map->data_c[i] = (char *)malloc(map->ncols * sizeof(char) + 1);
		if (!map->data_c[i])
			ft_error(ERR_MEM_ROW, cub);
		map->data_c[i][map->ncols] = '\0';
		i++;
	}
}

/**	[F]
 * @brief 
 *	[ Definition ]
 *	맵 데이터의 읽기와 처리를 관리.
 * 
 * 	[ Logic ]
 * 	1. allocate memory for map(2d array) and copy (char type) to the map.
 * 	2. fd no more need -> close.
 * 	3. open map again.
 * 	4. read every words from the file.
 * 	5. 
 * 
 * @param cub 
 */
void	load_and_fill_map(t_main *cub)
{
	char	onechar;
	int		i;
	int		row;

	i = 0;
	row = 0;
	allocate_map_char(cub);
	close(cub->fd);
	cub->fd = open(cub->filename, O_RDONLY);
	if (cub->fd == -1)
		ft_error(ERR_FILE, cub);
	while (i < cub->total_chars_read - 1)
	{
		read(cub->fd, &onechar, 1);
		i++;
	}
	while (row < cub->map.nrows)
		read_row_fill_rec_shape(cub, row++);
	close(cub->fd);
}
