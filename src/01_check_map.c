#include "cub3d.h"
/**
 * @brief 
 *	Check the (ac, av) condition, matching with the PDF.
 * @param argc 
 * @param argv 
 */
void	check_map_command(int argc, char **argv)
{
	int	i;

	if (argc < 2 || argc > 3)
		ft_error(ERR_ARGS, NULL);
	i = ft_strlen(argv[1]);
	if (ft_strnstr(&argv[1][i - 4], ".cub", 4) == NULL)
		ft_error(ERR_FILETYPE, NULL);
}

int	ft_sc_utils1(char **cmap, int y, int x)
{
	printf("char: y:%i x:%i |%c|\n",y, x, cmap[x][y] );
	if (cmap[x][y] == ' ' || cmap[y][x] == '\0')
		return (1);
	return (0);

}

int	ft_sc_utils2(t_main *cub, int x, int y)
{
	printf("\n\n------------------Line y:%i, x:%x char: |%c|\n", x,y, cub->map.data_c[x][y]);
	return ((ft_sc_utils1(cub->map.data_c, x + 1, y)
			+ ft_sc_utils1(cub->map.data_c, x - 1, y)
			+ ft_sc_utils1(cub->map.data_c, x, y + 1)
			+ ft_sc_utils1(cub->map.data_c, x, y - 1)));
}

int	ft_surround_check_utils3(t_main *cub)
{
	int	y;

	y = 0;
	while (y < (int)ft_strlen(cub->map.data_c[0]))
	{
		if ((cub->map.data_c[0][y] != '1') && (cub->map.data_c[0][y] != ' '))
			return (1);
		y++;
	}
	y = 0;
	while (y < (int)ft_strlen(cub->map.data_c[cub->map.nrows - 1]))
	{
		if ((cub->map.data_c[cub->map.nrows - 1][y] != '1') 
			&& (cub->map.data_c[cub->map.nrows - 1][y] != ' '))
			return (1);
		y++;
	}
	return (0);
}

int	ft_surround_check(t_main *cub)
{
	int	x;
	int	y;

	print_char_array(cub->map.data_c);
	if (ft_surround_check_utils3(cub))
		return (1);
	x = 0;
	while (x < cub->map.nrows)
	{
		printf("check line: %s\n", cub->map.data_c[x]);
		y = 0;
		while (y < cub->map.longest_ncols)
		{
			if (cub->map.data_c[x][y] == '0')
				if (ft_sc_utils2(cub, x, y) > 0)
					return (1);
			y++;
		}
		x++;
	}
	return (0);
}
