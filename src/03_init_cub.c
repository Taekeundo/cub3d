#include "cub3d.h"
/*	[F]
	[ Definition ]
	Initialize structures (t_main *cub)

	[ Reference ]
	typedef struct mlx
	{
		void*		window;		// window itself.
		void*		context;	// context Abstracted opengl data.
		int32_t		width;		// The width of the window.
		int32_t		height;		// The height of the window.
		double		delta_time; // The time difference between
								// the previous frame and current time.
	}	mlx_t;
*/
void	init_cub(int argc, char **argv, t_main *cub)
{
	cub->key_w_pressed = 0;
	cub->key_s_pressed = 0;
	cub->key_a_pressed = 0;
	cub->key_d_pressed = 0;
	cub->key_left_pressed = 0;
	cub->key_right_pressed = 0;
	cub->texture_alloc = 0;
	cub->tex_paths_alloc = 0;
	cub->move_speed = SQRS_PER_SEC / 100;
	cub->rot_speed = RADS_PER_SEC / 100;
	cub->pitch = 100;
	cub->map.data_c = 0;
	cub->map.data_i = 0;
	cub->map.c_alloc = 0;
	cub->map.i_alloc = 0;
	cub->dir.x = 0;
	cub->dir.y = 0;
	read_subject_file(argv, cub);
	if (argc == 3 && !ft_strcmp(argv[2], "test"))
		print_cub_file_summary(cub);
}

void	init_fileflags(t_main *cub)
{
	cub->fileflags.no = 0;
	cub->fileflags.so = 0;
	cub->fileflags.we = 0;
	cub->fileflags.ea = 0;
	cub->fileflags.f = 0;
	cub->fileflags.c = 0;
}
