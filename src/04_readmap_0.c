#include "cub3d.h"

void	set_player_pos(t_main *cub, int row, int col, bool *found)
{
	if (cub->map_curr_char == 'N' || cub->map_curr_char == 'S'
		|| cub->map_curr_char == 'W' || cub->map_curr_char == 'E')
	{
		if (*found == 1)
			ft_error(ERR_DUP_PLAYPOS, cub);
		cub->pos.x = row + 0.5;
		cub->pos.y = col + 0.5;
		*found = 1;
	}
}

void	set_player_dir_plane_we(t_main *cub)
{
	if (cub->map_curr_char == 'W')
	{
		cub->dir.x = 0;
		cub->dir.y = -1;
		cub->plane.x = 0.66;
		cub->plane.y = 0;
	}
	if (cub->map_curr_char == 'E')
	{
		cub->dir.x = 0;
		cub->dir.y = 1;
		cub->plane.x = -0.66;
		cub->plane.y = 0;
	}
}

void	set_player_dir_plane(t_main *cub)
{
	if (cub->map_curr_char == 'N')
	{
		cub->dir.x = -1;
		cub->dir.y = 0;
		cub->plane.x = 0;
		cub->plane.y = -0.66;
	}
	if (cub->map_curr_char == 'S')
	{
		cub->dir.x = 1;
		cub->dir.y = 0;
		cub->plane.x = 0;
		cub->plane.y = 0.66;
	}
	set_player_dir_plane_we(cub);
}

void	get_player_position(t_main *cub)
{
	int		row;
	int		col;
	bool	found;

	found = 0;
	row = 0;
	while (row < cub->map.nrows)
	{
		col = 0;
		while (col < cub->map.ncols)
		{
			cub->map_curr_char = cub->map.data_c[row][col];
			set_player_pos(cub, row, col, &found);
			set_player_dir_plane(cub);
			col++;
		}
		row++;
	}
	if (found == 0)
		ft_error(ERR_NO_PLAYPOS, cub);
}
