/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cam_dir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetruni <ipetruni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 14:29:57 by ipetruni          #+#    #+#             */
/*   Updated: 2024/02/29 16:28:23 by ipetruni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	north(t_vec *front, t_vec *cam, float fov)
{
	double	tan_half_fov_rad;

	tan_half_fov_rad = tan((fov * (M_PI / 180)) / 2);
	front->dir[X] = 0;
	front->dir[Y] = -1;
	cam->dir[X] = -front->dir[Y] * tan_half_fov_rad;
	cam->dir[Y] = front->dir[X] * tan_half_fov_rad;
}

void	south(t_vec *front, t_vec *cam, float fov)
{
	double	tan_half_fov_rad;

	tan_half_fov_rad = tan((fov * (M_PI / 180)) / 2);
	front->dir[X] = 0;
	front->dir[Y] = 1;
	cam->dir[X] = -front->dir[Y] * tan_half_fov_rad;
	cam->dir[Y] = front->dir[X] * tan_half_fov_rad;
}

void	east(t_vec *front, t_vec *cam, float fov)
{
	double	tan_half_fov_rad;

	tan_half_fov_rad = tan((fov * (M_PI / 180)) / 2);
	front->dir[X] = 1;
	front->dir[Y] = 0;
	cam->dir[X] = -front->dir[Y] * tan_half_fov_rad;
	cam->dir[Y] = front->dir[X] * tan_half_fov_rad;
}

void	west(t_vec *front, t_vec *cam, float fov)
{
	double	tan_half_fov_rad;

	tan_half_fov_rad = tan((fov * (M_PI / 180)) / 2);
	front->dir[X] = -1;
	front->dir[Y] = 0;
	cam->dir[X] = -front->dir[Y] * tan_half_fov_rad;
	cam->dir[Y] = front->dir[X] * tan_half_fov_rad;
}

void	set_fr_cam_v(char player, t_vec *front, t_vec *cam, float fov)
{
	if (player == 'N')
		north(front, cam, fov);
	else if (player == 'S')
		south(front, cam, fov);
	else if (player == 'E')
		east(front, cam, fov);
	else if (player == 'W')
		west(front, cam, fov);
}
