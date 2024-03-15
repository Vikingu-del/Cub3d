/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetruni <ipetruni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 14:26:05 by ipetruni          #+#    #+#             */
/*   Updated: 2024/02/13 14:27:27 by ipetruni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

float	vec_to_ang(t_vec vec)
{
	double	ang;

	ang = atan2(vec.dir[Y], vec.dir[X]) * 180 / M_PI;
	if (ang < 0)
		ang += 360;
	return (ang);
}

double	ang_to_rad(double ang)
{
	return (ang * M_PI / 180);
}

t_vec	get_vunit(t_point p1, t_point p2)
{
	t_point	point;
	t_vec	vec;
	float	magnitude;

	point.x = p2.x - p1.x;
	point.y = p2.y - p1.y;
	magnitude = sqrt(point.x * point.x + point.y * point.y);
	vec.dir[X] = point.x / magnitude;
	vec.dir[Y] = point.y / magnitude;
	return (vec);
}

t_vec	get_cam_vec(t_vec front, float fov)
{
	t_vec	vec;
	float	half_ang;

	half_ang = fov / 2;
	vec.dir[X] = front.dir[X] * cos(half_ang) - front.dir[Y] * sin(half_ang);
	vec.dir[Y] = front.dir[X] * sin(half_ang) + front.dir[Y] * cos(half_ang);
	return (vec);
}

double	get_front_length(t_cube *cube)
{
	double	front_length;

	front_length = (cube->screen.width / 2) / tan(cube->player.fov / 2);
	return (front_length);
}
