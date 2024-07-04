#ifndef CUB3D_H
# define CUB3D_H

/* [ HEADER FILE ] */
# include <stdio.h>		// printf, perror
# include <unistd.h>	// close, read, write, STDIO_FILENO, STDOUT_FILENO
# include <stdlib.h>	// malloc, free, exit, getenv
# include <fcntl.h>		// open, O_RDONLY, O_WRONLY, O_RDWR, O_CREAT, O_TRUNC
# include <limits.h>	// INT_MAX, INT_MIN, UNIT_MAX
# include <stdbool.h>	// bool, true, false
# include <math.h>		// sin, cos, tan, pow, sqrt, exp, log
# include "../MLX42/include/MLX42/MLX42.h"	// For MLX
# include "../libft/include/libft.h"		// For libft

/* [ MACRO for window, speed, texture ] */
/*	[F]
	WIN_WIDTH, WIN_HEIGHT: 1200 * 800

	SQRS_PER_SEC 2.0 // Distance in one second.
	 - 1프레임당 이동할수 있는 거리
	 - 캐릭터는 (2.0그리드/1초)만큼 거리 움직일 수 있다.

	RADS_PER_SEC 3.0 // Radians (angular measurement)
	 - 1프레임당 움직일 수 있는 각도
	 - 캐릭터는 (3.0그리드/1초)만큼 각도 움직일 수 있다.
*/
# define WIN_WIDTH 1200
# define WIN_HEIGHT 800
# define SQRS_PER_SEC 2.0
# define RADS_PER_SEC 3.0
# define NUM_TEXTURES 4
# define TEXTURE_NO 0
# define TEXTURE_SO 1
# define TEXTURE_WE 2
# define TEXTURE_EA 3

/*	[ MACRO for error message ]	*/
/*	[F]
	To handle each of error cases.
*/
# define ERR_ARGS "Wrong number of arguments to program\n"
# define ERR_FILETYPE "Wrong file extension (should be .cub)\n"
# define ERR_FILE "File not found\n"
# define ERR_TEX_PATH "Invalid file format: Invalid texture file path\n"
# define ERR_READ "Could not read from file or unexpectedly reached end\n"

# define ERR_MLX_WIN "Could not create MLX window\n"
# define ERR_MLX_IMG "Could not create MLX image\n"
# define ERR_MLX_IMGWIN "Could not put image to window\n"

# define ERR_MAP_WALLS "Map is not completely surrouned by walls\n"
# define ERR_MEM_ROW "Memory allocation error for row\n"
# define ERR_MEM_ROWPTR "Memory allocation error for row pointers\n"
# define ERR_COL_VAL "Invalid file format: Invalid color value\n"
# define ERR_DUPL_TEX "Invalid file format: Duplicate texture path in file\n"
# define ERR_DUPL_COL "Invalid file format: Duplicate color path in file\n"
# define ERR_PREFIXES "Invalid file format: Prefix not NO, SO, WE, EA, F or C\n"
# define ERR_INVALID_MAP_CHAR "Invalid file format: Invalid character in map\n"
# define ERR_NO_PLAYPOS "Invalid file format: No player position\n"
# define ERR_DUP_PLAYPOS "Invalid file format: Duplicate player position\n"

/*	[ STRUCTURE ]  */
/*	[F]
	[ Initialize ]
	1. init_cub.c
	[f] init_cub
	char	**data_c;		0
	int		**data_i;		0
	bool	c_alloc;		0
	bool	i_alloc;		0

	2. readmap_1.c
	[f] get_map_dims
	int		nrows;			0
	int		ncols;			0
	int		longest_ncols;	0
*/
typedef struct s_map
{
	char	**data_c;
	int		**data_i;
	bool	c_alloc;
	bool	i_alloc;
	int		nrows;
	int		ncols;
	int		longest_ncols;
}	t_map;

/*	[F]
	[ Initialize ]
	1. read.c
	[f] init_flieflags
	bool	no;				0
	bool	so;				0
	bool	we;				0
	bool	ea;				0
	bool	f;				0
	bool	c;				0
*/
typedef struct s_fileflags
{
	bool	no;
	bool	so;
	bool	we;
	bool	ea;
	bool	f;
	bool	c;
}	t_fileflags;

/*	[F]
	Double array(x, y) for "Double" type.
*/
typedef struct s_point2Dd
{
	double	x;
	double	y;
}	t_pt2d_d;

/*	[F]
	Double array(x, y) for "Integer" type.
*/
typedef struct s_point2Di
{
	int	x;
	int	y;
}	t_pt2d_i;

/*	[F]
	[ Not used ]
	t_pt2d_i		tex;

	[ Initialize ]

1. init_cub.c
[f] init_cub
bool			key_w_pressed;				0
bool			key_s_pressed;				0
bool			key_d_pressed;				0
bool			key_a_pressed;				0
bool			key_left_pressed;			0
bool			key_right_pressed;			0

bool			texture_alloc;				0
bool			tex_paths_alloc;			0
double			move_speed;					0.02 (SPEED: SQRS_PER_SEC 2.0 / 100)
double			rot_speed;					0.03 (SPEED: RADS_PER_SEC 3.0 / 100)
int				pitch;						100

t_map			map;						0 // map.data_c (char **) // rows, cols
											0 // map.data_i (int **) // rows, cols
											0 // map.c_alloc (bool)
											0 // map.i_alloc (bool)

t_pt2d_d		dir;						0 // dir.x (double)
											0 // dir.y (double)

------------------------------------------------------------------------

2. read.c
[f] read_subject_file
char			*filename;					argv[1]
int				total_chars_read;			0
int				fd;							fd(= open file)

	[f] init_fileflags
	t_fileflags		fileflags;				0 // fileflags.no (bool)
											0 // fileflags.so (bool)
											0 // flieflags.we (bool)
											0 // flieflags.ea (bool)
											0 // flieflags.f  (bool)
											0 // flieflags.c  (bool)

	2-1. readutil.c
	[f] read_prefixes
	[f] read_char
	char			char_read;				'onechar'

	[f] read_tex_prefix
	[f] read_wall_tex_path
	char			*tex_paths[4];			NO: 0, SO: 1, WE: 2, EA: 3

	2-2. readcolor.c
	[f] read_color_prefix
	uint32_t		ceiling_color;			read_color of "F" (Floor)
	uint32_t		floor_color;			read_color of "C" (Ceiling)

	2-3. readmap_1.c
	[f] get_map_dims
	t_map			map;					0 // map.longest_ncols (int)
											0 // map.nrows (int)
											0 // map.ncols (int)

	2-4. readmap.c
	[f] get_player_position
	char			map_curr_char;			Don't need to initialize. Just update.

	2-5. readmap_0.c
	[f] set_player_pos
	t_pt2d_d		pos;					row + 0.5 // pos.x (double)
											col + 0.5 // pos.y (double)
		
	[f] set_player_dir_plane
	if (N)
	t_pt2d_d		plane;					0		// plane.x (double)
											-0.66	// plane.y (double)
	if (S)
	t_pt2d_d		plane;					0		// plane.x (double)
											0.66	// plane.y (double)

	[f] set_player_dir_plane_we
	if (W)
	t_pt2d_d		plane;					0.66	// plane.x (double)
											0		// plane.y (double)
	if (E)
	t_pt2d_d		plane;					-0.66	// plane.x (double)
											0		// plane.y (double)

[f] load_textures
mlx_texture_t	*textures[i];				mlx_load_png

------------------------------------------------------------------------

3. init_window.c
[f] mlx_init
mlx_t			*mlx;						Library
mlx_image_t		*img;						Library

------------------------------------------------------------------------

4.raycast.c
[f] ft_raycast
t_pt2d_i		map_pos;					cub->map_pos.x = cub->pos.x (int)
											cub->map_pos.y = cub->pos.y (int)

------------------------------------------------------------------------
		
	5. math.c
	[f] calc_ray_dir
	t_pt2d_d		raydr;					raydr.x (double)
											raydr.y (double)

	[f] calc_delta_dist
	t_pt2d_d		delta_dist;				delta_dist.x = math (double)
											felta_dist.y = math (double)

	[f] calc_step_and_side_dist
	t_pt2d_i		step;					cub->step.x = -1 || 1 (int)
											cub->step.y = -1 || 1 (int)
	t_pt2d_d		side_dist;				cub->side_dist.x = math (double)
											cub->side_dist.y = math (double)
	[f] perform_dda
	[f] handle_wall_hit
	int				side;					cub->side = side
	int				wall_direction;			TEXTURE_NO || TEXTURE_SO
											TEXTURE_WE || TEXTURE_EA

------------------------------------------------------------------------

double			perp_wall_dist;				cub->side_dist.x - cub->delta_dist.x;
										||	cub->side_dist.y - cub->delta_dist.y;

------------------------------------------------------------------------

6. 	draw.c
[f] draw_tex
int				draw_start;					0
int				draw_end;					0
int				line_height;				WIN_HEIGHT / cub->perp_wall_dist;
*/
typedef struct s_main
{
	bool			key_w_pressed;
	bool			key_s_pressed;
	bool			key_d_pressed;
	bool			key_a_pressed;
	bool			key_left_pressed;
	bool			key_right_pressed;

	bool			texture_alloc;
	bool			tex_paths_alloc;

	double			move_speed;
	double			rot_speed;
	int				pitch;

	t_map			map;
	t_pt2d_d		dir;			// Black line: Direction vector.

	char			*filename;
	int				total_chars_read;
	int				fd;

	t_fileflags		fileflags;

	char			char_read;

	char			*tex_paths[4];

	uint32_t		ceiling_color;
	uint32_t		floor_color;

	char			map_curr_char;

	t_pt2d_d		pos;			// Green spot: Player's location.
	t_pt2d_d		plane;			// Blue line: 

	mlx_texture_t	*textures[4];

	mlx_t			*mlx;
	mlx_image_t		*img;

	t_pt2d_i		map_pos;

	t_pt2d_d		raydr;
	t_pt2d_d		delta_dist;
	t_pt2d_i		step;
	t_pt2d_d		side_dist;

	int				side;
	int				wall_direction;
	double			perp_wall_dist;

	int				draw_start;
	int				draw_end;
	int				line_height;
}		t_main;

/* [ FUNCTIONS ] */
//01_check_map
void		check_map_command(int argc, char **argv);
int			ft_surround_check(t_main *cub);

//02_print_map
void		print_map_c(t_map *map);
void		print_map_i(t_map *map);
void		print_cub_file_summary(t_main *cub);

//03_init_cub
void		init_cub(int argc, char **argv, t_main *cub);
void		init_fileflags(t_main *cub);

//03_init_window
void		init_window(t_main *cub);

//04_read
void		load_textures(t_main *cub);
void		read_subject_file(char **argv, t_main *cub);

//04_readcolor
bool		read_color_prefix(t_main *cub, char *path);

//04_readmap_0
void		get_player_position(t_main *cub);

//04_readmap_1
void		get_map_dims(t_main *cub);
void		fill_map(t_main *cub);

//04_readmap_2
void		malloc_map_i(t_main *cub);
void		convert_map_data_c_to_i(t_main *cub);

//04_readtexture
bool		read_tex_prefix(t_main *cub, char *path);

//04_readutil
void		read_char(t_main *cub);
bool		match_char(t_main *cub, char char_to_match);
bool		*choose_fileflag(t_main *cub, char *path);
void		read_prefixes(t_main *cub);

//05_key
void		keyhook(mlx_key_data_t keydata, void *param);

//06_raycast
void		ft_raycast(void *param);

//07_move_wsad
void		move_player(t_main *cub);

//07_move_rotate
void		rotate_left(t_main *cub);
void		rotate_right(t_main *cub);

//09_image
void		clear_image(t_main *cub);

//10_math
t_pt2d_d	calc_ray_dir(int x, t_pt2d_d raydr, t_pt2d_d dir, t_pt2d_d plane);
t_pt2d_d	calc_delta_dist(t_pt2d_d delta_dist, t_pt2d_d raydr);
void		calc_step_and_side_dist(t_main *cub);
void		perform_dda(t_main *cub);

//11_draw
void		draw_tex(t_main *cub, int x);

//end_0
void		ft_error(char *str, t_main *cub);
void		delete_textures(t_main *cub);
void		closehook(void *param);

//end_1
void		free_cub(t_main *cub);

//utiles_test
void		print_char_array(char **array);

//010_check_map_wall
int			ft_map_surround_wall(t_main *cub);

#endif
