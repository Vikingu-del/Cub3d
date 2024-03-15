/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_events.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eseferi <eseferi@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 14:11:07 by ipetruni          #+#    #+#             */
/*   Updated: 2024/02/27 16:24:07 by eseferi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate_left_mouse(t_cube *cube)
{
	double	old_dir_x;
	double	old_plane_x;
	double	speed;

	old_dir_x = cube->player.front.dir[X];
	old_plane_x = cube->player.cam.dir[X];
	speed = cube->player.player_rot_speed * 1.5;
	cube->player.front.dir[X] = cube->player.front.dir[X] \
	* cos(-speed) - cube->player.front.dir[Y] \
	* sin(-speed);
	cube->player.front.dir[Y] = old_dir_x * sin(-speed) \
	+ cube->player.front.dir[Y] * cos(-speed);
	cube->player.cam.dir[X] = cube->player.cam.dir[X] \
	* cos(-speed) - cube->player.cam.dir[Y] \
	* sin(-speed);
	cube->player.cam.dir[Y] = old_plane_x \
	* sin(-speed) + cube->player.cam.dir[Y] \
	* cos(-speed);
}

void	rotate_right_mouse(t_cube *cube)
{
	double	old_dir_x;
	double	old_plane_x;
	double	speed;

	old_dir_x = cube->player.front.dir[X];
	old_plane_x = cube->player.cam.dir[X];
	speed = cube->player.player_rot_speed * 1.5;
	cube->player.front.dir[X] = cube->player.front.dir[X] \
	* cos(speed) - cube->player.front.dir[Y] \
	* sin(speed);
	cube->player.front.dir[Y] = old_dir_x \
	* sin(speed) + cube->player.front.dir[Y] \
	* cos(speed);
	cube->player.cam.dir[X] = cube->player.cam.dir[X] \
	* cos(speed) - cube->player.cam.dir[Y] \
	* sin(speed);
	cube->player.cam.dir[Y] = old_plane_x \
	* sin(speed) + cube->player.cam.dir[Y] \
	* cos(speed);
}

// int	ft_mouse(t_cube *cube)
// {
// 	int	x;
// 	int	y;
// 	int	dx;

// 	mlx_mouse_hide();
// 	mlx_mouse_get_pos(cube->screen.win, &x, &y);
// 	dx = x - cube->screen.width / 2;
// 	if (dx > 2)
// 		rotate_right_mouse(cube);
// 	else if (dx < -2)
// 		rotate_left_mouse(cube);
// 	mlx_mouse_move(cube->screen.win,
// 		cube->screen.width / 2, cube->screen.height / 2);
// 	return (0);
// }

int	ft_mouse(t_cube *cube)
{
	int	x;
	int	y;
	int	dx;

	#ifdef __APPLE__
    	mlx_mouse_hide();
		mlx_mouse_get_pos(cube->screen.win, &x, &y);
	#else
		mlx_mouse_hide(cube->screen.mlx, cube->screen.win);
		mlx_mouse_get_pos(cube->screen.mlx, cube->screen.win, &x, &y);
	#endif
	dx = x - cube->screen.width / 2;
	if (dx > 2)
		rotate_right_mouse(cube);
	else if (dx < -2)
		rotate_left_mouse(cube);
	#ifdef __APPLE__
		mlx_mouse_move(cube->screen.win,
			cube->screen.width / 2, cube->screen.height / 2);
	#else
		mlx_mouse_move(cube->screen.mlx, cube->screen.win,\
			cube->screen.width / 2, cube->screen.height / 2);
	#endif
	return (0);
}
