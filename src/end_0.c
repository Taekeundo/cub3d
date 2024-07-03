/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_0.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkwak <tkwak@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 10:48:04 by tkwak             #+#    #+#             */
/*   Updated: 2024/06/06 10:48:05 by tkwak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

/**	[F]
 * @brief 
 * 	[ Definition ]
 * 	Call this function, when you meet with 'error' situation.
 * 
 * 	[ Memo ]
 * 	write(2, str, ft_strlen(str)); // 표준 오류 출력
 * 		Send the error message to the standard Error(= 2: stderr).
 * 
 * 	[ Difference stdout(1) and stderror(2)]
 * 	std-out	  : For printing successful result.
 * 	std-error : For printing error or warning result.
 *	= Can disginguish (Normal output) and (error output) more clearly.
 * 
 * @param str // points to the string, which means errer message.
 * @param cub // for memory free in this function.
 */
void	ft_error(char *str, t_main *cub)
{
	write(2, "Error\n", 6);
	write(2, str, (int)ft_strlen(str));
	if (cub)
		free_cub(cub);
	exit(EXIT_FAILURE);
}

void	delete_textures(t_main *cub)
{
	int	i;

	i = 0;
	while (i < NUM_TEXTURES)
	{
		mlx_delete_texture(cub->textures[i]);
		i++;
	}
}

/**	[F]
 * @brief 
 * 	[ Must ]
 *	All event handlers must be registered before executing mlx_loop
 * 	to respond appropriately when an event occurs.
 * 
 * 	[ Definition ]
 * 	Call-back function for the 'mlx_close_hook' function.
 * 	ex) This function is executed when user click the close button.
 * 
 * 	[ Goal ]
 * 	Clean up MLX's resources and close the window.
 * 	It is used to handle key events (close button).
 *
 * @param prev_cub 
 */
void	closehook(void *prev_cub)
{
	t_main	*new_cub;

	new_cub = (t_main *)prev_cub;
	mlx_terminate(new_cub->mlx);
	free_cub(new_cub);
	exit(EXIT_FAILURE);
}
