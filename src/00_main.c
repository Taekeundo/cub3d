#include "cub3d.h"

/**
 * @brief
 *	[ Variable ]
 *   t_main	cub			: structure, check the info in header file.
 * 
 * 	[ Function ]
 * 	check_map_command	: Check the "user_input".
 * 	init_cut			: Initialize struct(= cub), including textures.
 *  ft_surruond_check	: Check the map, all exterior wall must consist of '1'.
 * 	if (argc == 3 ..)	: Handle special case for informing the test.
 * 	init_window			: Initialize window -> Empty(Black) window should be opened.
 *  mlx_key_hook		: 눌러진 버튼에 따라 -> 약속된 반응을 한다 (reaction).
 *  mlx_close_hook		: 눌러진 버튼은 무조건 (훅)이 종료되어야 한다.
 *  mlx_loop_hook		: 누르고 -> 꺼지고 -> 화면 업데이트하고 (ft_raycast).
 *  mlx_loop			: 다른 키 누르는 상황 대비해서, 다시 mlx_key_hook로 돌아가기 위한 함수.
 *  mlx_terminate		: 완전 종료 (mlx사용이 끝나면 꼭 써줘야 하는 기능).
 *  free_cub			: 구조체의 할당되었던 모든 메모리 해제.
 * 
 * @param argc
 * 	argc	: must 2 or 3
 * 				1st: name of the program (= ./cub3D)
 * 				2nd: directory of the maps (= maps/0.cub)
 * @param argv check over argc.
 * @return int 
 */
int	main(int argc, char **argv)
{
	t_main	cub;

	check_map_command(argc, argv);
	init_cub(argc, argv, &cub);
	//if (ft_map_surround_wall(&cub))
	if (ft_surround_check(&cub))
		ft_error(ERR_MAP_WALLS, &cub);
	if (argc == 3 && !ft_strcmp(argv[2], "test"))
		exit(0);
	init_window(&cub);
	mlx_key_hook(cub.mlx, &keyhook, &cub);
	mlx_close_hook(cub.mlx, &closehook, &cub);		// "Jason" finishes to do the documentation until this function.
	mlx_loop_hook(cub.mlx, ft_raycast, &cub);		// "Rene" starts to do the documentation from this function (mlx_loop_hook).
	mlx_loop(cub.mlx);
	mlx_terminate(cub.mlx);
	free_cub(&cub);
	return (0);
}
/*
[ Logic ]
1. read map
2. check all the wall
3. one with int, one with char
4. error handling
5. argc == 3 to check input everytime.
6. understand how raycast works
7. 2D -> 3d racating is math.
*/