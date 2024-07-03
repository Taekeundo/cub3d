/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   08_move_rotate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkwak <tkwak@student.42berlin.de>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 10:47:13 by tkwak             #+#    #+#             */
/*   Updated: 2024/06/06 10:47:27 by tkwak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

void	rotate_left(t_main *m)
{
	double	dir_x0;
	double	plane_x0;

	dir_x0 = m->dir.x;
	m->dir.x = m->dir.x * cos(m->rot_speed) - m->dir.y * sin(m->rot_speed);
	m->dir.y = dir_x0 * sin(m->rot_speed) + m->dir.y * cos(m->rot_speed);
	plane_x0 = m->plane.x;
	m->plane.x = m->plane.x * cos(m->rot_speed)
		- m->plane.y * sin(m->rot_speed);
	m->plane.y = plane_x0 * sin(m->rot_speed)
		+ m->plane.y * cos(m->rot_speed);
}

void	rotate_right(t_main *m)
{
	double	dir_x0;
	double	plane_x0;

	dir_x0 = m->dir.x;
	m->dir.x = m->dir.x * cos(-m->rot_speed) - m->dir.y * sin(-m->rot_speed);
	m->dir.y = dir_x0 * sin(-m->rot_speed) + m->dir.y * cos(-m->rot_speed);
	plane_x0 = m->plane.x;
	m->plane.x = m->plane.x * cos(-m->rot_speed)
		- m->plane.y * sin(-m->rot_speed);
	m->plane.y = plane_x0 * sin(-m->rot_speed)
		+ m->plane.y * cos(-m->rot_speed);
}
