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

void	read_subject_file(char **argv, t_main *cub)
{
	int	i;

	cub->filename = argv[1];
	cub->total_chars_read = 0; 
	cub->fd = open(cub->filename, O_RDONLY);
	if (cub->fd == -1)
		ft_error(ERR_FILE, cub);
	init_fileflags(cub);
	i = 0;
	while (i++ < 6)
		read_prefixes(cub);
	while (cub->char_read == '\n')
		read_char(cub);
	get_map_dims(cub);
	fill_map(cub);
	get_player_position(cub);
	convert_map_data_c_to_i(cub);
	load_textures(cub);
}
