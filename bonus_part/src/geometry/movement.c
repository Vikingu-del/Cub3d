/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eseferi <eseferi@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 20:24:34 by eseferi           #+#    #+#             */
/*   Updated: 2024/02/29 12:48:33 by eseferi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_forward(t_cube *cube)
{
	int	delta_x;
	int	delta_y;

	delta_x = (int)(cube->player.pos[X] + cube->player.front.dir[X] \
	* (cube->player.player_speed * 2));
	delta_y = (int)(cube->player.pos[Y] + cube->player.front.dir[Y] \
	* (cube->player.player_speed * 2));
	if (cube->map.map[(int)cube->player.pos[Y]][delta_x] != '1'
		&& (cube->map.map[(int)cube->player.pos[Y]][delta_x] != '2'))
		cube->player.pos[X] += cube->player.front.dir[X] \
		* cube->player.player_speed;
	if (abs(cube->map.door[X] - (int)cube->player.pos[X]) - \
	abs(cube->map.door[Y] - (int)cube->player.pos[Y]) < 2 && cube->door == 1)
	{
		cube->game_status = 2;
		return ;
	}
	if (cube->map.map[delta_y][(int)cube->player.pos[X]] != '1'
		&& cube->map.map[delta_y][(int)cube->player.pos[X]] != '2')
		cube->player.pos[Y] += cube->player.front.dir[Y] \
		* cube->player.player_speed;
}

void	move_backward(t_cube *cube)
{
	int	delta_x;
	int	delta_y;

	delta_x = (int)(cube->player.pos[X] - cube->player.front.dir[X] \
	* (cube->player.player_speed * 2));
	delta_y = (int)(cube->player.pos[Y] - cube->player.front.dir[Y] \
	* (cube->player.player_speed * 2));
	if (cube->map.map[(int)cube->player.pos[Y]][delta_x] != '1'
		&& cube->map.map[(int)cube->player.pos[Y]][delta_x] != '2')
		cube->player.pos[X] -= cube->player.front.dir[X] \
		* cube->player.player_speed;
	if (cube->map.map[delta_y][(int)cube->player.pos[X]] != '1'
		&& cube->map.map[delta_y][(int)cube->player.pos[X]] != '2')
		cube->player.pos[Y] -= cube->player.front.dir[Y] \
		* cube->player.player_speed;
}

void	move_left(t_cube *cube)
{
	int	delta_x;
	int	delta_y;

	delta_x = (int)(cube->player.pos[X] + cube->player.front.dir[Y] \
	* (cube->player.player_speed * 2));
	delta_y = (int)(cube->player.pos[Y] - cube->player.front.dir[X] \
	* (cube->player.player_speed * 2));
	if (cube->map.map[(int)cube->player.pos[Y]][delta_x] != '1'
		&& cube->map.map[(int)cube->player.pos[Y]][delta_x] != '2')
		cube->player.pos[X] += cube->player.front.dir[Y] \
		* cube->player.player_speed;
	if (cube->map.map[delta_y][(int)cube->player.pos[X]] != '1'
		&& cube->map.map[delta_y][(int)cube->player.pos[X]] != '2')
		cube->player.pos[Y] -= cube->player.front.dir[X] \
		* cube->player.player_speed;
}

void	move_right(t_cube *cube)
{
	int	delta_x;
	int	delta_y;

	delta_x = (int)(cube->player.pos[X] - cube->player.front.dir[Y] \
	* (cube->player.player_speed * 2));
	delta_y = (int)(cube->player.pos[Y] + cube->player.front.dir[X] \
	* (cube->player.player_speed * 2));
	if (cube->map.map[(int)cube->player.pos[Y]][delta_x] != '1'
		&& cube->map.map[(int)cube->player.pos[Y]][delta_x] != '2')
		cube->player.pos[X] -= cube->player.front.dir[Y] \
		* cube->player.player_speed;
	if (cube->map.map[delta_y][(int)cube->player.pos[X]] != '1'
		&& cube->map.map[delta_y][(int)cube->player.pos[X]] != '2')
		cube->player.pos[Y] += cube->player.front.dir[X] \
		* cube->player.player_speed;
}
