/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cam_dir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetruni <ipetruni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 14:29:57 by ipetruni          #+#    #+#             */
/*   Updated: 2024/02/22 16:34:04 by ipetruni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	north(t_vec *front, t_vec *cam)
{
	front->dir[X] = 0;
	front->dir[Y] = -1;
	cam->dir[X] = 0.66;
	cam->dir[Y] = 0;
}

void	south(t_vec *front, t_vec *cam)
{
	front->dir[X] = 0;
	front->dir[Y] = 1;
	cam->dir[X] = -0.66;
	cam->dir[Y] = 0;
}

void	east(t_vec *front, t_vec *cam)
{
	front->dir[X] = -1;
	front->dir[Y] = 0;
	cam->dir[X] = 0;
	cam->dir[Y] = -0.66;
}

void	west(t_vec *front, t_vec *cam)
{
	front->dir[X] = 1;
	front->dir[Y] = 0;
	cam->dir[X] = 0;
	cam->dir[Y] = 0.66;
}

void	set_fr_cam_v(char player, t_vec *front, t_vec *cam)
{
	if (player == 'N')
		north(front, cam);
	if (player == 'S')
		south(front, cam);
	if (player == 'E')
		east(front, cam);
	if (player == 'W')
		west(front, cam);
}
