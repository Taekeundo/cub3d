/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_readutil.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkwak <tkwak@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 10:46:43 by tkwak             #+#    #+#             */
/*   Updated: 2024/06/06 10:46:46 by tkwak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

/**	[F]
 * @brief 
 * 	[ Definition ]
 * 	Update the member of cub struct, relating with the read char.
 * 	
 * 	[ Logic ]
 * 	1. n_chars_read = read(cub->fd, &one, 1);
 * 		read a char from the file(='fd') and save it to 'one'.
 * 		return value of 'read' is (1), if it success.
 * 		So, (n_chars_read) is currently '1'.
 * 	2. cub->total_chars_read += n_chars_read;
 * 		Update the number of chars that succeed to read from file.
 * 	3. Update the members (total_chars_read & char_read)
 * 
 * 	[ Goal ]
 * 	1. 읽은 문자 수 추적	to "total_chars_read"(member of cub)
 * 	2. 읽은 문자 저장		to "char_read"(member of cub)
 * 
 * @param cub 
 */
void	read_char(t_main *cub)
{
	char	one;
	int		n_chars_read;

	n_chars_read = read(cub->fd, &one, 1);
	if (n_chars_read < 1)
		ft_error(ERR_READ, cub);
	cub->total_chars_read += n_chars_read;
	cub->char_read = one;
}

/**	[F]
 * @brief 
 * 	[ Definition ]
 * 	Check the char from (param2) is same with the member char(char_read).
 * 
 * 	[ Logic ]
 * 	Bool: yes -> 1, no -> 0.
 * 
 * @param cub 
 * @param char_to_match 
 * @return true		// yes (matching)
 * @return false 	// no  (not matching)
 */
bool	match_char(t_main *cub, char char_to_match)
{
	if (cub->char_read == char_to_match)
		return (1);
	return (0);
}

/**	[F]
 * @brief 
 * 	[ Definition ]
 * 
 * 	[ Logic ]
 * 	1. Check the path(param2) is same with the text
 * 		which is identifiers for 4directions, floor and ceiling.
 * 
 * 	2. If same (ft_strcmp's return value is '0')
 * 		return the address of the member(fileflags).
 * 
 * @param cub 
 * @param path 
 * @return true 
 * @return false 
 */
bool	*choose_fileflag(t_main *cub, char *path)
{
	if (!ft_strcmp(path, "NO"))
		return (&cub->fileflags.no);
	if (!ft_strcmp(path, "SO"))
		return (&cub->fileflags.so);
	if (!ft_strcmp(path, "WE"))
		return (&cub->fileflags.we);
	if (!ft_strcmp(path, "EA"))
		return (&cub->fileflags.ea);
	if (!ft_strcmp(path, "F"))
		return (&cub->fileflags.floor);
	if (!ft_strcmp(path, "C"))
		return (&cub->fileflags.ceiling);
	return (NULL);
}

/** [F]
 * @brief
 * 	[ Definition ]
 * 	Parsing (texture & color) identifier.
 * 
 * 	[ long to short ]
 * 	comparing (param) with the given info
 * 	(ex) NO, SO, ... from the mendatory part.
 * 	by using the
 * 	1. [f] parse_texture_identifier &
 * 	2. [f] parse_color_identifier.
 * 
 * 	[ Logic ]
 * 	1. Read char one by one from the map files.
 * 	2. Check texuture identifier first.
 * 	3. Check color identifier second.
 * 
 * @param cub 
 */
void	parse_identifiers(t_main *cub)
{
	read_char(cub);
	while (cub->char_read == '\n')
		read_char(cub);
	if (parse_texture_identifier(cub, "NO"))
		return ;
	if (parse_texture_identifier(cub, "SO"))
		return ;
	if (parse_texture_identifier(cub, "WE"))
		return ;
	if (parse_texture_identifier(cub, "EA"))
		return ;
	if (parse_color_identifier(cub, "F"))
		return ;
	if (parse_color_identifier(cub, "C"))
		return ;
	ft_error(ERR_PREFIXES, cub);
}

/**	[F]
 * @brief 
 * 	[ Definition ]
 * 	Check the type of the texture is png.
 * 
 * @param path 
 * @return int 
 */
int	is_png_file(char *path)
{
	int	len;

	len = ft_strlen(path);
	if (path == NULL || len < 4)
		return (0);
	if (ft_strncmp(path + len - 4, ".png", 4) == 0)
		return (1);
	else
		return (0);
}
