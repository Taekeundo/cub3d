/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_readtexture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkwak <tkwak@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 10:46:33 by tkwak             #+#    #+#             */
/*   Updated: 2024/06/06 10:46:35 by tkwak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

/**	[F]
 * @brief 
 *	[ Definition ]
 * 	check path and save it to the path array and return it.
 * 
 * @param cub 
 * @return char* 
 */
char	*extract_texture_path(t_main *cub)
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
int	get_texture_index(char *path)
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
				ft_error(ERR_DUPL_TEX, cub);
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
