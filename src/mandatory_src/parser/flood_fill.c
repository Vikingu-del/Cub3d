/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetruni <ipetruni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 07:27:34 by eseferi           #+#    #+#             */
/*   Updated: 2024/02/29 16:42:56 by ipetruni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	initialize_player(t_cube *c, int i)
{
	c->player.m_pos.x = is_player(c->map.map[i]);
	c->player.m_pos.y = i;
	c->player.pos[X] = (double)c->player.m_pos.x + 0.5;
	c->player.pos[Y] = (double)c->player.m_pos.y + 0.5;
	c->player.init_v = c->map.map[(int)c->player.m_pos.y]
	[(int)c->player.m_pos.x];
	c->player.fov = 66;
	set_fr_cam_v(c->player.init_v, &c->player.front,
		&c->player.cam, c->player.fov);
	c->player.move[X] = 0;
	c->player.move[Y] = 0;
	c->player.rotate = 0;
	c->player.player_speed = PLAYER_SPEED;
	c->player.player_rot_speed = PLAYER_ROT_SPEED;
}

void	parse_player(t_cube *c)
{
	int	i;
	int	player_start_positions;

	i = 0;
	player_start_positions = 0;
	while (c->map.map[i])
	{
		if (is_player(c->map.map[i]))
		{
			player_start_positions++;
			initialize_player(c, i);
		}
		i++;
	}
	if (player_start_positions == 0)
		exit_program(c, 1, NO_PLAYER);
}

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
		|| cube->map.map[c_y][c_x] == 'F')
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
