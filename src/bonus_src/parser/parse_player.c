/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eseferi <eseferi@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 11:57:10 by eseferi           #+#    #+#             */
/*   Updated: 2024/02/29 17:46:10 by eseferi          ###   ########.fr       */
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
	set_fr_cam_v(c->player.init_v, &c->player.front, &c->player.cam);
	c->player.fov = 60;
	c->player.move[X] = 0;
	c->player.move[Y] = 0;
	c->player.rotate = 0;
	c->player.player_speed = PLAYER_SPEED;
	c->player.player_rot_speed = PLAYER_ROT_SPEED;
}

static void	initialize_player_and_count_positions(t_cube *c, int i, \
int *player_start_positions)
{
	if (is_player(c->map.map[i]))
	{
		(*player_start_positions)++;
		initialize_player(c, i);
	}
}

static void	initialize_door_key_enemy(t_cube *c, int i)
{
	if (is_door(c->map.map[i]))
	{
		c->map.door[X] = i;
		c->map.door[Y] = is_door(c->map.map[i]);
	}
	if (is_key(c->map.map[i]))
	{
		c->map.key[X] = i;
		c->map.key[Y] = is_key(c->map.map[i]);
	}
	if (is_enemy(c->map.map[i]))
	{
		c->map.enemy[X] = i;
		c->map.enemy[Y] = is_enemy(c->map.map[i]);
	}
}

void	parse_player(t_cube *c)
{
	int	i;
	int	player_start_positions;

	i = 0;
	player_start_positions = 0;
	while (c->map.map[i])
	{
		initialize_player_and_count_positions(c, i, &player_start_positions);
		initialize_door_key_enemy(c, i);
		i++;
	}
	if (player_start_positions == 0)
		exit_program(c, 1, NO_PLAYER);
	if (c->map.door[X] == 0 && c->map.door[Y] == 0)
		exit_program(c, 1, NO_DOOR);
	if (c->map.key[X] == 0 && c->map.key[Y] == 0)
		exit_program(c, 1, NO_KEY);
	if (c->map.enemy[X] == 0 && c->map.enemy[Y] == 0)
		exit_program(c, 1, NO_ENEMY);
}
