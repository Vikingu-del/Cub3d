/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_door.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eseferi <eseferi@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 14:44:12 by eseferi           #+#    #+#             */
/*   Updated: 2024/02/29 17:20:27 by eseferi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_door_pixel(t_cube *cube, t_ray *ray, int x, int y)
{
	int	color;

	cube->sprite.sprite_text[DOOR].text_point[Y] \
	= (int)cube->sprite.sprite_text[DOOR].tex_pos \
	& (TEXT_SIZE - 1);
	cube->sprite.sprite_text[DOOR].tex_pos += \
	cube->sprite.sprite_text[DOOR].tex_step;
	color = cube->sprite.sprite_text[DOOR].pixels
	[TEXT_SIZE * (int)cube->sprite.sprite_text[DOOR].text_point[Y] \
	+ (int)cube->sprite.sprite_text[DOOR].text_point[X]];
	if (ray->side == Y)
		color = (color >> 1) & 8355711;
	cube->text_pixels[y][x] = color;
	if (cube->door == 1)
		cube->text_pixels[y][x] = 0x00FF0000;
}

void	draw_door(t_cube *cube, t_ray *ray, int x)
{
	int	y;

	cube->sprite.sprite_text[DOOR].text_point[X] = (int)(ray->wall_x \
	* (double)TEXT_SIZE);
	if (((ray->side == X) && (ray->ray_dir.dir[X] > 0))
		|| ((ray->side == Y) && (ray->ray_dir.dir[Y] < 0)))
		cube->sprite.sprite_text[DOOR].text_point[X] = TEXT_SIZE \
		- cube->sprite.sprite_text[DOOR].text_point[X] - 1;
	cube->sprite.sprite_text[DOOR].tex_step = 1.0 * TEXT_SIZE \
	/ ray->line_height;
	cube->sprite.sprite_text[DOOR].tex_pos = \
	(ray->draw[START] - cube->screen.height \
	/ 2 + ray->line_height / 2) * cube->sprite.sprite_text[DOOR].tex_step;
	y = ray->draw[START];
	while (y < ray->draw[END])
	{
		draw_door_pixel(cube, ray, x, y);
		y++;
	}
}
