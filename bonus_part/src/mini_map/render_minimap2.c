/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_minimap2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetruni <ipetruni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 14:42:26 by ipetruni          #+#    #+#             */
/*   Updated: 2024/02/29 14:11:05 by ipetruni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	get_minimap_character(t_cube *d, t_minimap *m, char **map)
{
	if ((int)d->player.m_pos.x == (m->x + m->offset_x)
		&& (int)d->player.m_pos.y == (m->y + m->offset_y))
		return ('N');
	else if (map[m->y + m->offset_y][m->x + m->offset_x] == '1')
		return ('1');
	else if (map[m->y + m->offset_y][m->x + m->offset_x] == '2')
		return ('2');
	else if (map[m->y + m->offset_y][m->x + m->offset_x] == '3')
		return ('3');
	else if (map[m->y + m->offset_y][m->x + m->offset_x] == '4')
		return ('4');
	else if (map[m->y + m->offset_y][m->x + m->offset_x] == 'F')
		return ('0');
	else if (map[m->y + m->offset_y][m->x + m->offset_x] == '0')
		return ('0');
	else
		return ('\0');
}

char	*add_minimap_line(t_cube *d, t_minimap *m, int y, char **map)
{
	char	*line;
	int		x;

	line = ft_calloc(sizeof(char *), m->longest_line + 1);
	if (!line)
		return (NULL);
	x = 0;
	while (x < m->longest_line + 1)
	{
		m->x = x;
		m->y = y;
		if ((y + m->offset_y) < m->map_lines && (size_t)
			(x + m->offset_x) < ft_strlen(map[y + m->offset_y]))
			line[x] = get_minimap_character(d, m, map);
		else
			line[x] = '0';
		x++;
	}
	return (line);
}

char	**generate_minimap(t_cube *cube, t_minimap *minimap, char **map)
{
	char	**mmap;
	int		y;

	mmap = ft_calloc(sizeof(char **), minimap->map_lines + 1);
	if (!mmap)
		return (NULL);
	y = 0;
	while (y < minimap->map_lines)
	{
		mmap[y] = add_minimap_line(cube, minimap, y, map);
		if (!mmap[y])
		{
			free_tab((void **)mmap);
			return (NULL);
		}
		y++;
	}
	return (mmap);
}
