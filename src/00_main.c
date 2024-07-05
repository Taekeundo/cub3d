/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkwak <tkwak@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 10:43:26 by tkwak             #+#    #+#             */
/*   Updated: 2024/06/06 10:44:15 by tkwak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

/**	[F]
 * @brief
 *	[ Variable ]
 *   t_main	cub			: structure, check the info in header file.
 * 
 * 	[ logic ]
 * 	1. check_user_input
 * 	= Check the command from the user (= "user_input(argc, argv)").
 * 	= 사용자로부터 맵 명령어를 확인.
 * 
 * 	2. init_cub
 * 	= Initialize the 'cub' structure.
 * 	= Before program starts, set the data from struct to null.
 * 	= 큐브 구조체 초기화.
 *
 *  3. check_surround_wall
 * 	= Check the map, all exterior must consist of '1(= wall)'.
 *  = Validating the map's wall.
 * 	= ft_error: If meet with error, print error message and exit program.
 * 	= 맵이 벽으로 둘러쌓여있는지 확인.
 *  = 벽으로 둘러쌓여있지 않은 경우 -> 에러메시지 출력 & 프로그램 종료.
 * 
 * 	4. if (argc == 3 ..)
 * 	= Handle special case for information about the test.
 * 	= if (argv[2] == test): meet with 'test' -> end the program.
 * 	= And print all about (info).
 *  = To check input everytime.
 *  = "test" 인자 있으면 프로그램 즉시 종료 & 데이터 전부 프린트.
 * 
 * 	5. init_window
 * 	= Initialize grapic window.
 *  = Empty(Black) window should be opened.
 *    With this initialized window, User can communicate with the computer.
 *  = 윈도우 초기화 & 화면 설정.
 *
 * 	!!! Regist event handler !!!
 * 	!!! 이벤트 핸들러 등록 6,7 !!!
 * 		1. All event handlers must be registered
 * 		2. before executing mlx_loop
 * 		3. to respond appropriately when an event occurs.
 * 
 *  6. mlx_key_hook (키보드 입력을 처리할 함수를 등록)
 * 	= Sets up a hook to handle key input events.
 * 	= Handle keyboard input events with the call-back function.
 * 	= Param (1): mlx_t* mlx			: struct for mlx.
 * 	  Param (2): mlx_keyfunc func	: call-back function.
 * 	  Param (3): void* param		: param for the call-back function.
 * 	= 키보드 입력 이벤트를 처리할 콜백 함수 등록.
 *	= 눌러진 버튼에 따라 (Up to the pressed button) -> 약속된 반응을 한다 (react).
 *
 *  7. mlx_close_hook
 *	= !! Regist event handler !! (창 닫기 버튼 클릭을 처리할 함수를 등록)
 * 	= Sets up a hook(call-back function) to handle the window closing event.
 * 	= This function is automatically called
 * 		when user clicks the window's close button
 * 		or when the system attempts to close the window.
 *  = 창 닫기 이벤트 처리할 콜백 함수 등록.
 *	= 창을 닫으려는 이벤트를 처리할 콜백 함수를 설정.
 *
 *  ------------------------------RENE------------------------------
 *
 *  8. mlx_loop_hook
 * 	= void mlx_loop_hook(void *mlx, int (*f)(), void *param);
 * 		Param(1) mlx	: MLX instance (= 실행중인 MLX)
 * 		Param(2) f		: 주기적으로 호출될 함수
 * 		Param(3) param	: f 함수에 전달될 parameter.
 *  = (2D -> 3d) check how raycast works.
 * 	= `ft_raycast` 함수를 주기적으로 호출할 수 있도록 설정.
 * 	= 메인 루프가 실행되는 동안 ft_raycast 함수를 주기적으로 호출.
 * 	= 누르고 -> 꺼지고 -> 화면 업데이트하고 (ft_raycast).
 * 
 *  9. mlx_loop
 *	= 이벤트 루프를 시작	
 *	= 다른 키 누르는 상황 대비해서, 다시 mlx_key_hook로 돌아가기 위한 함수.
 * 	
 *  10. mlx_terminate & free_cub
 * 	= 프로그램 종료되면 자원 해제 및 mlx종료
 *  = mlx사용이 끝나면 꼭 써줘야 하는 기능.
 *  = 구조체의 할당되었던 모든 메모리 해제.
 * 	
 * @param argc
 * @param argv
 * @return int
 */
int	main(int argc, char **argv)
{
	t_main	cub;

	check_user_input(argc, argv);
	init_cub(argc, argv, &cub);
	if (check_surround_wall(&cub))
		ft_error(ERR_MAP_WALLS, &cub);
	if (argc == 3 && !ft_strcmp(argv[2], "test"))
		exit(0);
	init_window(&cub);
	mlx_key_hook(cub.mlx, &keyhook, &cub);
	mlx_close_hook(cub.mlx, &closehook, &cub);
	mlx_loop_hook(cub.mlx, ft_raycast, &cub);
	mlx_loop(cub.mlx);
	mlx_terminate(cub.mlx);
	free_cub(&cub);
	return (0);
}
