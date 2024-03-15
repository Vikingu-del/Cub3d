/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eseferi <eseferi@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 16:52:03 by ipetruni          #+#    #+#             */
/*   Updated: 2024/02/29 13:32:42 by eseferi          ###   ########.fr       */
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
		if (cube->map.map[ray->map_point[Y]][ray->map_point[X]] == '1'
			|| cube->map.map[ray->map_point[Y]][ray->map_point[X]] == '2')
		{
			if (cube->map.map[ray->map_point[Y]][ray->map_point[X]] == '2')
				ray->hit_door = 1;
			hit = 1;
		}
	}
}

void	update_texts_pixels(t_cube *cube, t_ray *ray, int x)
{
	int	y;
	int	color;
	int	texture_index;

	texture_index = get_texture_index(ray);
	cube->wall_text.text_point[X] = (int)(ray->wall_x * (double)TEXT_SIZE);
	if (((ray->side == X) && (ray->ray_dir.dir[X] > 0))
		|| ((ray->side == Y) && (ray->ray_dir.dir[Y] < 0)))
		cube->wall_text.text_point[X] = TEXT_SIZE - \
		cube->wall_text.text_point[X] - 1;
	cube->wall_text.tex_step = 1.0 * TEXT_SIZE / ray->line_height;
	cube->wall_text.tex_pos = (ray->draw[START] - cube->screen.height \
	/ 2 + ray->line_height / 2) * cube->wall_text.tex_step;
	y = ray->draw[START] - 1;
	while (++y < ray->draw[END])
	{
		cube->wall_text.text_point[Y] = (int)cube->wall_text.tex_pos \
		& (TEXT_SIZE - 1);
		cube->wall_text.tex_pos += cube->wall_text.tex_step;
		color = cube->wall_text.textures[texture_index][TEXT_SIZE * \
		cube->wall_text.text_point[Y] + cube->wall_text.text_point[X]];
		if (ray->side == Y)
			color = (color >> 1) & 8355711;
		cube->text_pixels[y][x] = color;
	}
}

void	render_sprite_and_frames(t_cube *cube, double *z_buffer)
{
	if ((int)cube->player.pos[X] == \
		(int)cube->sprite.sprite_text[KEY].text_point[X] && \
		(int)cube->player.pos[Y] == \
		(int)cube->sprite.sprite_text[KEY].text_point[Y])
		cube->key_status = 1;
	cast_sprites(cube, z_buffer);
	render_frame(cube);
	free(z_buffer);
}

void	raycast_bonus(t_cube *cube, t_ray *ray, int width)
{
	int		x;
	int		y;
	double	*z_buffer;

	z_buffer = malloc(sizeof(double) * width + 1);
	x = -1;
	y = -1;
	if (cube->game_status == 1)
		render_game_over(cube);
	if (cube->game_status == 2)
		render_win_screen(cube);
	while (++y < cube->screen.height)
		cast_floor(cube, y);
	while (++x < width)
	{
		ray_calculations(cube, ray, x);
		z_buffer[x] = ray->wall_dist;
	}
	render_sprite_and_frames(cube, z_buffer);
}
