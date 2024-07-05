/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_init_cub_window.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkwak <tkwak@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 10:45:06 by tkwak             #+#    #+#             */
/*   Updated: 2024/07/05 09:12:30 by tkwak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

/**	[F]
 * @brief 
 * 	[ Definition ]
 * 	Initialize all flags for 4 directions & floor, ceiling.
 * 
 * @param cub 
 */
static void	init_fileflags(t_main *cub)
{
	cub->fileflags.no = 0;
	cub->fileflags.so = 0;
	cub->fileflags.we = 0;
	cub->fileflags.ea = 0;
	cub->fileflags.floor = 0;
	cub->fileflags.ceiling = 0;
}

/** [F]
 * @brief
 * 	[ Definition ]
 * 	Cpy texture from the path to the member of struct(cub->textures[i])
 * 	If success to cpy -> change the flag of texture_alloc to the 'true'.
 * 
 * @param cub 
 */
static void	load_textures(t_main *cub)
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
static void	init_data_from_file(char **argv, t_main *cub)
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

/**	[F]
 * @brief 
 * 	[ Definition ]
 * 	Initialize structures (t_main *cub)
 * 
 * 	[ Reference ]
 * 	typedef struct mlx
 * 	{
 * 		void*		window;		// window itself.
 * 		void*		context;	// context Abstracted opengl data.
 * 		int32_t		width;		// The width of the window.
 * 		int32_t		height;		// The height of the window.
 * 		double		delta_time; // The time difference between
 * 								// the previous frame and current time.
 * 	}	mlx_t;
 * 
 * 	[ Memo ]
 * 	key_w,s,d,a_pressed		// Keys for 4 directions for moving.
 * 	key_left, right_pressed	// Keys for 2 directions for rotating.
 * 
 * @param argc 
 * @param argv 
 * @param cub 
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
	init_data_from_file(argv, cub);
	if (argc == 3 && !ft_strcmp(argv[2], "test"))
		display_cub_info(cub);
}

/**	[F]
 * @brief 
 * 	[ Definition ]
 * 	Create a graphics window
 * 	using the MLX library and attach images to the window.
 * 	= MLX 라이브러리를 사용하여 그래픽 창을 생성하고, 이미지를 윈도우에 연결.
 * 
 * 	[ Goal ]
 * 	1. Initialize the mlx and img members of the t_main structure.
 * 	= t_main 구조체의 member(mlx & img)를 초기화.
 * 
 * 	2. Set up the "Raycaster(NAME)" program's window and image.
 * 	= Name: "Raycaster" 프로그램의 윈도우와 이미지를 설정.
 * 
 * 	[ Logic ]
 * 	1. mlx_set_setting(MLX_STRETCH_IMAGE, false)
 * 		'MLX_STRETCH_IMAGE' 설정을 false로.
 * 		= Not stretch the image to match with the window size.
 * 		= Ex) window: 800 x 600 pixel
 * 			  Image:  400 x 300 pixel
 * 			  -> !! not muliple !!
 * 			  -> Stick to use original size and scale.
 * 		= 이미지를 스트레칭하지 않겠다.
 * 	2. mlx_init(width, height, title, whether resize or not).
 * 		2-1. if (!cub->mlx): Fail to make the window // 윈도우 생성 실패 시.
 * 	3. mlx_new_image(mlx, width, height).
 * 		3-1. if (!cub->img): Fail to make the image // 이미지 생성 실패 시
 * 	4. mlx_image_to_window(mlx, image, pos.x, pos.y)
 * 		Display the created image in a window.
 * 		생성한 이미지를 윈도우에 표시.
 * 
 * @param cub 
 */
void	init_window(t_main *cub)
{
	mlx_set_setting(MLX_STRETCH_IMAGE, false);
	cub->mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "Raycaster", false);
	if (!cub->mlx)
		ft_error(ERR_MLX_WIN, cub);
	cub->img = mlx_new_image(cub->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!cub->img)
		ft_error(ERR_MLX_IMG, cub);
	if ((mlx_image_to_window(cub->mlx, cub->img, 0, 0) < 0))
		ft_error(ERR_MLX_IMGWIN, cub);
}
