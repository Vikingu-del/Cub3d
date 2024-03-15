/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetruni <ipetruni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 14:25:53 by ipetruni          #+#    #+#             */
/*   Updated: 2024/02/13 14:30:20 by ipetruni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_vec	rotate_vec(t_vec vec, float ang)
{
	t_vec	new_vec;
	float	rad;

	rad = ang * M_PI / 180;
	new_vec.dir[X] = vec.dir[X] * cos(rad) - vec.dir[Y] * sin(rad);
	new_vec.dir[Y] = vec.dir[X] * sin(rad) + vec.dir[Y] * cos(rad);
	return (new_vec);
}

t_vec	find_casting_vec(t_cube *cube, int x)
{
	double	camera_x;
	t_vec	ray;

	camera_x = 2 * x / (double)cube->screen.width - 1;
	ray.dir[X] = cube->player.front.dir[X] + cube->player.cam.dir[X] * camera_x;
	ray.dir[Y] = cube->player.front.dir[Y] + cube->player.cam.dir[Y] * camera_x;
	return (ray);
}

t_vec	normalize_vec(t_vec vec)
{
	float	magnitude;

	magnitude = sqrt(vec.dir[X] * vec.dir[X] + vec.dir[Y] * vec.dir[Y]);
	vec.dir[X] /= magnitude;
	vec.dir[Y] /= magnitude;
	return (vec);
}
