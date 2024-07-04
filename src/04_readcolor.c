/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_readcolor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkwak <tkwak@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 10:45:50 by tkwak             #+#    #+#             */
/*   Updated: 2024/07/05 15:50:40 by tkwak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

/** [F]
 * @brief 
 *	[ Definition ]
 * 	현재 읽고 있는 파일에서 색상 값(0-255 범위의 정수)을 읽어와서
 * 	정수형으로 변환한 후 반환하는 역할.
 * 
 *	[ Example ]
 *	F 220,255,255
 *    ---
 *    red color
 *
 * 		first char: '2' -> go into while loop
 * 		color[0] = '2'
 * 		color[1] = '2'
 * 		color[2] = '0'
 * 		color[3] = '\0'
 * 
 * 		color = "220'\0'"
 * 		return (atoi(color)); -> 220 (int).
 * 
 * @param cub 
 * @return int 
 */
int	extract_color_from_map(t_main *cub)
{
	char	color[PATH_MAX];
	int		i;

	i = 0;
	while (cub->char_read >= '0' && cub->char_read <= '9')
	{
		color[i] = cub->char_read;
		read_char(cub);
		i++;
	}
	if (i == 0)
		ft_error(ERR_COL_VAL, cub);
	color[i] = '\0';
	return (ft_atoi(color));
}

/** [F]
 * @brief 
 *	[ Definition ]
 *	Reads a string and returns the RGB color value in uint32_t format.
 *	= 문자열을 읽어와서 RGB 색상 값을 uint32_t 형식으로 반환
 *
 *	[ Example ]
 *	F 100,150,200
 * 
 * 	[ Background ]
 * 	1. RGB
 * 			R(red)     	 G(green)		 B(blue)
 * 	Decimal  100          150         	 200
 *		     (64+32+8)    (128+16+4+2) 	 (128+64+8)
 *	Binary	 0110 0100    1001 0110	 	 1100 1000
 * 			  6    4        9   6          C   8
 *			 ---------------------------------------
 *	Hexa	   0x64         0x96       	    0xC8
 * 
 *	(red << 24)		: 24 left in binary.
 *	= 0110 0100 // 0000 0000 0000 0000 0000 0000
 * 	
 * 	(green << 16)	: 16 left in binary.
 * 	= 0000 0000 // 1001 0110 // 0000 0000 0000 0000
 * 
 * 	(blue << 8)		: 8 left in binary.
 *	= 0000 0000 0000 0000 // 1100 1000 // 0000 0000
 * 
 * 	(0xFF)
 * 	= 0000 0000 0000 0000 0000 0000 // 1111 1111
 * 
 * 	   red	  |	  green   |    blue   |   0xFF
 * 	0110 0100 + 1001 0110 + 1100 1000 + 1111 1111
 * 	----------------------------------------------
 * 	0x 64 96 C8 FF
 * 
 * 	2. Functions
 *		[f] read_char(cub)	: 색상 값들 사이의 쉼표와 공백을 처리.
 *		[f] match_char(cub)	: 색상 값들 사이의 쉼표와 공백을 처리.
 * 
 *	[ Logic ]
 *	1. Handling color by color (red, green, blud) in order.
 *	2. red = extract_color_from_map(cub);
 *		convert (100) from map(char type)
 *		to the 'red' with the (int type).
 *	3. match_char(cub, ',');
 * 		go to the next color.
 * 	4. 'green' & 'blue' color have also same logic with 'red' color.
 * 	5. Error handling
 * 		0 <= Color must <= 255
 *  6. Combine all colors(R,G,B) with bit operation (|) and return it.
 * 
 * @param cub 
 * @return uint32_t 
 */
uint32_t	extract_color_path(t_main *cub)
{
	int	red;
	int	green;
	int	blue;

	red = extract_color_from_map(cub);
	read_char(cub);
	match_char(cub, ',');
	while (cub->char_read == ' ')
		read_char(cub);
	green = extract_color_from_map(cub);
	read_char(cub);
	match_char(cub, ',');
	while (cub->char_read == ' ')
		read_char(cub);
	blue = extract_color_from_map(cub);
	if (red < 0 || red > 255 || green < 0
		|| green > 255 || blue < 0 || blue > 255)
		ft_error(ERR_COL_VAL, cub);
	return ((red << 24) | (green << 16) | (blue << 8) | 0xFF);
}

/**	[F]
 * @brief 
 * 	[ Definition ]
 * 	Parsing (color) identifier.
 * 
 * 	[ Logic ]
 * 	1. Almost same with [f] "parse_texture_identifier".
 * 
 * @param cub 
 * @param path 
 * @return true 
 * @return false 
 */
bool	parse_color_identifier(t_main *cub, char *path)
{
	bool	*chosen_fileflag;

	if (match_char(cub, path[0]))
	{
		read_char(cub);
		while (cub->char_read == ' ')
			read_char(cub);
		chosen_fileflag = choose_fileflag(cub, path);
		if (*chosen_fileflag == true)
			ft_error(ERR_DUPL_COL, cub);
		if (!ft_strcmp(path, "F"))
			cub->floor_color = extract_color_path(cub);
		if (!ft_strcmp(path, "C"))
			cub->ceiling_color = extract_color_path(cub);
		*chosen_fileflag = true;
		return (true);
	}
	return (false);
}
