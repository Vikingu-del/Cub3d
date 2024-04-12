/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_dda.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetruni <ipetruni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 17:12:26 by ipetruni          #+#    #+#             */
/*   Updated: 2024/02/29 17:12:31 by ipetruni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	setup_dda_params(t_cube *cube, t_ray *ray)
{
	if (ray->ray_dir.dir[X] < 0)
	{
		ray->step[X] = -1;
		ray->side_dist[X] = (cube->player.pos[X] - ray->map_point[X]) \
		* ray->delta_dist[X];
	}
	else
	{
		ray->step[X] = 1;
		ray->side_dist[X] = (ray->map_point[X] + 1.0 - cube->player.pos[X]) \
		* ray->delta_dist[X];
	}
	if (ray->ray_dir.dir[Y] < 0)
	{
		ray->step[Y] = -1;
		ray->side_dist[Y] = (cube->player.pos[Y] - ray->map_point[Y]) \
		* ray->delta_dist[Y];
	}
	else
	{
		ray->step[Y] = 1;
		ray->side_dist[Y] = (ray->map_point[Y] + 1.0 - cube->player.pos[Y]) \
		* ray->delta_dist[Y];
	}
}

void	perform_dda(t_cube *cube, t_ray *ray)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (ray->side_dist[X] < ray->side_dist[Y])
		{
			ray->side_dist[X] += ray->delta_dist[X];
			ray->map_point[X] += ray->step[X];
			ray->side = 0;
		}
		else
		{
			ray->side_dist[Y] += ray->delta_dist[Y];
			ray->map_point[Y] += ray->step[Y];
			ray->side = 1;
		}
		if (cube->map.map[(int)ray->map_point[Y]]
			[(int)ray->map_point[X]] == '1')
			hit = 1;
	}
}
