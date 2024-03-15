/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eseferi <eseferi@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 07:27:34 by eseferi           #+#    #+#             */
/*   Updated: 2024/02/29 11:57:50 by eseferi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	f_fill(t_cube *cube, int p_y, int p_x)
{
	int	c_x;
	int	c_y;
	int	map_h;

	c_x = p_x;
	c_y = p_y;
	map_h = cube->map.map_height;
	if (c_y >= map_h || cube->map.map[c_y][c_x] == ' '
		|| cube->map.map[c_y][c_x] == '\0')
		exit_program (cube, 1, UNCLOSED_MAP);
	if (c_y < 0 || c_x < 0 || cube->map.map[c_y][c_x] == '1'
		|| cube->map.map[c_y][c_x] == '2' || cube->map.map[c_y][c_x] == '3'
		|| cube->map.map[c_y][c_x] == '4' || cube->map.map[c_y][c_x] == 'F')
		return (0);
	cube->map.map[c_y][c_x] = 'F';
	if (f_fill(cube, c_y + 1, c_x)
		|| f_fill(cube, c_y - 1, c_x)
		|| f_fill(cube, c_y, c_x + 1)
		|| f_fill(cube, c_y, c_x - 1))
		return (1);
	return (0);
}

static void	replace_spaces(char **map, int map_h)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < map_h)
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == ' ')
				map[i][j] = '0';
			j++;
		}
		i++;
	}
}

void	check_walls(t_cube *cube)
{
	replace_spaces(cube->map.map, cube->map.map_height);
	f_fill(cube, (int)cube->player.m_pos.y,
		(int)cube->player.m_pos.x);
}
