/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetruni <ipetruni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 14:59:26 by ipetruni          #+#    #+#             */
/*   Updated: 2024/02/13 15:00:55 by ipetruni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate_left(t_cube *cube)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = cube->player.front.dir[X];
	old_plane_x = cube->player.cam.dir[X];
	cube->player.front.dir[X] = cube->player.front.dir[X] \
	* cos(-cube->player.player_rot_speed) - cube->player.front.dir[Y] \
	* sin(-cube->player.player_rot_speed);
	cube->player.front.dir[Y] = old_dir_x * sin(-cube->player.player_rot_speed) \
	+ cube->player.front.dir[Y] * cos(-cube->player.player_rot_speed);
	cube->player.cam.dir[X] = cube->player.cam.dir[X] \
	* cos(-cube->player.player_rot_speed) - cube->player.cam.dir[Y] \
	* sin(-cube->player.player_rot_speed);
	cube->player.cam.dir[Y] = old_plane_x \
	* sin(-cube->player.player_rot_speed) + cube->player.cam.dir[Y] \
	* cos(-cube->player.player_rot_speed);
}

void	rotate_right(t_cube *cube)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = cube->player.front.dir[X];
	old_plane_x = cube->player.cam.dir[X];
	cube->player.front.dir[X] = cube->player.front.dir[X] \
	* cos(cube->player.player_rot_speed) - cube->player.front.dir[Y] \
	* sin(cube->player.player_rot_speed);
	cube->player.front.dir[Y] = old_dir_x \
	* sin(cube->player.player_rot_speed) + cube->player.front.dir[Y] \
	* cos(cube->player.player_rot_speed);
	cube->player.cam.dir[X] = cube->player.cam.dir[X] \
	* cos(cube->player.player_rot_speed) - cube->player.cam.dir[Y] \
	* sin(cube->player.player_rot_speed);
	cube->player.cam.dir[Y] = old_plane_x \
	* sin(cube->player.player_rot_speed) + cube->player.cam.dir[Y] \
	* cos(cube->player.player_rot_speed);
}
