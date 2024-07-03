/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_readcolor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkwak <tkwak@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 10:45:50 by tkwak             #+#    #+#             */
/*   Updated: 2024/06/06 10:45:52 by tkwak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

int	read_color_value(t_main *cub)
{
	char	color_str[PATH_MAX];
	int		i;

	i = 0;
	while (cub->char_read >= '0' && cub->char_read <= '9')
	{
		color_str[i++] = cub->char_read;
		read_char(cub);
	}
	if (i == 0)
		ft_error(ERR_COL_VAL, cub);
	color_str[i] = '\0';
	return (ft_atoi(color_str));
}

uint32_t	read_color_path(t_main *cub)
{
	int	red;
	int	green;
	int	blue;

	red = read_color_value(cub);
	read_char(cub);
	match_char(cub, ',');
	while (cub->char_read == ' ')
		read_char(cub);
	green = read_color_value(cub);
	read_char(cub);
	match_char(cub, ',');
	while (cub->char_read == ' ')
		read_char(cub);
	blue = read_color_value(cub);
	if (red < 0 || red > 255 || green < 0
		|| green > 255 || blue < 0 || blue > 255)
		ft_error(ERR_COL_VAL, cub);
	return ((red << 24) | (green << 16) | (blue << 8) | 0xFF);
}

bool	read_color_prefix(t_main *cub, char *path)
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
			cub->floor_color = read_color_path(cub);
		if (!ft_strcmp(path, "C"))
			cub->ceiling_color = read_color_path(cub);
		*chosen_fileflag = true;
		return (true);
	}
	return (false);
}
