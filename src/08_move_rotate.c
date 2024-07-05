#include "cub3d.h"
/**
 * @brief Rotates the player character left based on the current rotation speed.
 *
 * The new direction and plane vectors are computed using the rotation matrix:
 * - `dir.x = dir.x * cos(rot_speed) - dir.y * sin(rot_speed)`
 * - `dir.y = dir.x * sin(rot_speed) + dir.y * cos(rot_speed)`
 * - `plane.x = plane.x * cos(rot_speed) - plane.y * sin(rot_speed)`
 * - `plane.y = plane.x * sin(rot_speed) + plane.y * cos(rot_speed)`
 * - plane is the middle of the FOV and dir the other rays
 *
 * @param m A pointer to the `t_main` structure that contains the current 
 *          game state, including the player's direction, view plane, and 
 *          rotation speed.
 * @see t_main
 * @see rot_speed
 */
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

/**
 * @brief Rotates the player character right based on the current rotation speed.
 *
 * The new direction and plane vectors are computed using the rotation matrix:
 * - `dir.x = dir.x * cos(-rot_speed) - dir.y * sin(-rot_speed)`
 * - `dir.y = dir.x * sin(-rot_speed) + dir.y * cos(-rot_speed)`
 * - `plane.x = plane.x * cos(-rot_speed) - plane.y * sin(-rot_speed)`
 * - `plane.y = plane.x * sin(-rot_speed) + plane.y * cos(-rot_speed)`
 * - plane is the middle of the FOV and dir the other rays
 *
 * @param m A pointer to the `t_main` structure that contains the current 
 *          game state, including the player's direction, view plane, and 
 *          rotation speed.
 * @see t_main
 * @see rot_speed
 */
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
