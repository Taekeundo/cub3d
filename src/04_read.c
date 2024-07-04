/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_read.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkwak <tkwak@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 10:45:42 by tkwak             #+#    #+#             */
/*   Updated: 2024/06/06 10:48:54 by tkwak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

/** [F]
 * @brief
 * 	[ Definition ]
 * 	Cpy texture from the path to the member of struct(cub->textures[i])
 * 	If success to cpy -> change the flag of texture_alloc to the 'true'.
 * 
 * @param cub 
 */
void	load_textures(t_main *cub)
{
	int	i;
	int	fd;

	i = 0;
	while (i < NUM_TEXTURES)
	{
		fd = open(cub->tex_paths[i], O_RDONLY);
		if (fd == -1)
			ft_error(ERR_TEX_PATH, cub);
		close(fd);
		cub->textures[i] = mlx_load_png(cub->tex_paths[i]);
		i++;
	}
	cub->texture_alloc = true;
}

/**	[F]
 * @brief
 * 	[ Definition ]
 * 	Reads the file and sets(initialize) the necessary data for program(cub3d).
 * 
 * 	[ Logic ]
 * 	set up everything for executing program.
 * 	1. Filename
 * 	2. Total_chars_read
 * 	3. Assign fd (open the file)
 * 	4. Fileflags (w,e,n,s,f,c)
 * 	5. Parse_identifiers (6 times)
 * 		0: NO
 * 		1: SO
 * 		2: EA
 * 		3: WE
 * 		4: F
 * 		5: C
 * 	6. Read every chars in the maps one by one.
 * 		= check, how many chars in the map and save it.
 * 	7. Load the map and fill it with malloc.
 * 	8. Set player's position, direction vector, view plane vector.
 *  9. Convert the char type map to int type map for efficient handling.
 * 	10. The texture appropriate for each direction
 * 		is loaded from the path and assigned.
 * 
 * @param argv
 * @param cub 
 */
void	init_data_from_file(char **argv, t_main *cub)
{
	int	i;

	i = 0;
	cub->filename = argv[1];
	cub->total_chars_read = 0; 
	cub->fd = open(cub->filename, O_RDONLY);
	if (cub->fd == -1)
		ft_error(ERR_FILE, cub);
	init_fileflags(cub);
	while (i++ < 6)
		parse_identifiers(cub);
	while (cub->char_read == '\n')
		read_char(cub);
	check_map_size(cub);
	load_and_fill_map(cub);
	set_player_pos_dir_plane(cub);
	convert_char_map_to_i(cub);
	load_textures(cub);
}
