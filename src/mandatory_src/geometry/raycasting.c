/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eseferi <eseferi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 14:37:00 by ipetruni          #+#    #+#             */
/*   Updated: 2024/04/12 11:15:22 by eseferi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	update_texture_index(t_cube *cube, t_ray *ray)
{
	int	texture_index;

	texture_index = get_texture_index(ray);
	(void)texture_index;
	cube->wall_text.text_point[X] = (int)(ray->wall_x \
		* (double)cube->wall_text.tex_size);
	if (((ray->side == 0) && (ray->ray_dir.dir[X] > 0)) \
		|| ((ray->side == 1) && (ray->ray_dir.dir[Y] < 0)))
		cube->wall_text.text_point[X] = cube->wall_text.tex_size \
			- cube->wall_text.text_point[X] - 1;
}

void	update_texture_step_and_pos(t_cube *cube, t_ray *ray)
{
	cube->wall_text.tex_step = 1.0 \
		* cube->wall_text.tex_size / ray->line_height;
	cube->wall_text.tex_pos = (ray->draw[START] - cube->screen.height \
		/ 2 + ray->line_height / 2) * cube->wall_text.tex_step;
}

void	update_texture_pixels(t_cube *cube, t_ray *ray, int x, int text_i)
{
	int	y;
	int	color;

	y = ray->draw[START];
	while (y < ray->draw[END])
	{
		cube->wall_text.text_point[Y] = (int)cube->wall_text.tex_pos \
			& (cube->wall_text.tex_size - 1);
		cube->wall_text.tex_pos += cube->wall_text.tex_step;
		color = cube->wall_text.textures[text_i][cube->wall_text.tex_size \
			* cube->wall_text.text_point[Y] + cube->wall_text.text_point[X]];
		if (ray->side == Y)
			color = (color >> 1) & 8355711;
		cube->wall_text.text_pixels[y][x] = color;
		y++;
	}
}

void	update_texts_pixels(t_cube *cube, t_ray *ray, int x)
{
	int	texture_index;

	update_texture_index(cube, ray);
	update_texture_step_and_pos(cube, ray);
	texture_index = get_texture_index(ray);
	update_texture_pixels(cube, ray, x, texture_index);
}

void	raycast(t_cube *cube, t_ray *ray)
{
	int	x;

	x = 0;
	while (x < cube->screen.width)
	{
		setup_ray_params(cube, ray, x);
		setup_dda_params(cube, ray);
		perform_dda(cube, ray);
		calculate_line_height(cube, ray);
		update_texts_pixels(cube, ray, x);
		x++;
	}
	render_frame(cube);
}
