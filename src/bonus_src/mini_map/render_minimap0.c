/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_minimap0.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eseferi <eseferi@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 16:45:38 by ipetruni          #+#    #+#             */
/*   Updated: 2024/02/29 14:34:30 by eseferi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_minimap_tile_pixels(t_minimap *minimap, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < minimap->tile_size)
	{
		j = 0;
		while (j < minimap->tile_size)
		{
			mm_set_image_pixel(minimap->img, x + j, i + y, color);
			j++;
		}
		i++;
	}
}

void	draw_minimap_tile(t_minimap *minimap, int x, int y)
{
	if (minimap->map[y][x] == 'N' || minimap->map[y][x] == 'S'
		|| minimap->map[y][x] == 'E' || minimap->map[y][x] == 'W')
		set_minimap_tile_pixels(minimap, x * minimap->tile_size,
			y * minimap->tile_size, 0x00FF00);
	else if (minimap->map[y][x] == '1')
		set_minimap_tile_pixels(minimap, x * minimap->tile_size,
			y * minimap->tile_size, 0x606060);
	else if (minimap->map[y][x] == '2')
		set_minimap_tile_pixels(minimap, x * minimap->tile_size,
			y * minimap->tile_size, 0xFF0000);
	else if (minimap->map[y][x] == '3')
		set_minimap_tile_pixels(minimap, x * minimap->tile_size,
			y * minimap->tile_size, 0x80E0E0E0);
	else if (minimap->map[y][x] == '4')
		set_minimap_tile_pixels(minimap, x * minimap->tile_size,
			y * minimap->tile_size, 0x80E0E0E0);
	else if (minimap->map[y][x] == '0')
		set_minimap_tile_pixels(minimap, x * minimap->tile_size,
			y * minimap->tile_size, 0x80E0E0E0);
	else if (minimap->map[y][x] == '\0')
		set_minimap_tile_pixels(minimap, x * minimap->tile_size,
			y * minimap->tile_size, 0x000000);
	else
		set_minimap_tile_pixels(minimap, x * minimap->tile_size,
			y * minimap->tile_size, 0x000000);
}

void	set_minimap_border_image_pixels(t_minimap *minimap, int color)
{
	int	size;
	int	x;
	int	y;

	size = MMAP_PIXEL_SIZE ;
	y = 0;
	while (y < size)
	{
		x = 0;
		while (x < size)
		{
			if (x < 3 || x > size - 3 || y < 3 || y > size - 3)
				mm_set_image_pixel(minimap->img, x, y, color);
			x++;
		}
		y++;
	}
}

void	draw_minimap(t_minimap *minimap)
{
	int	x;
	int	y;

	y = 0;
	while (y < minimap->size)
	{
		x = 0;
		while (x < minimap->size)
		{
			if (!minimap->map[y] || !minimap->map[y][x]
				|| minimap->map[y][x] == '\0')
				break ;
			draw_minimap_tile(minimap, x, y);
			x++;
		}
		y++;
	}
	set_minimap_border_image_pixels(minimap, 0x000000);
}
