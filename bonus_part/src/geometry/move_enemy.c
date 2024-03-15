/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_enemy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eseferi <eseferi@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 14:54:38 by eseferi           #+#    #+#             */
/*   Updated: 2024/02/29 17:30:10 by eseferi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	update_position_based_on_direction(enum e_direction direction, \
double *new_x, double *new_y)
{
	if (direction == UP)
		(*new_y) -= 0.5;
	else if (direction == DOWN)
		(*new_y) += 0.5;
	else if (direction == LEFT)
		(*new_x) -= 0.5;
	else if (direction == RIGHT)
		(*new_x) += 0.5;
}

static void	adjust_position_if_wall(t_sprite_info *s_i, \
double *new_x, double *new_y)
{
	if (s_i->m[(int)(*new_y + 1)][(int)*new_x] == '1')
		(*new_y) -= 0.5;
	if (s_i->m[(int)(*new_y - 1)][(int)*new_x] == '1')
		(*new_y) += 0.5;
	if (s_i->m[(int)*new_y][(int)(*new_x + 1)] == '1')
		(*new_x) -= 0.5;
	if (s_i->m[(int)*new_y][(int)(*new_x - 1)] == '1')
		(*new_x) += 0.5;
}

void	move_enemy(t_sprite_info *s_i, double *enemy_x, double *enemy_y)
{
	const int			movement_interval = 7;
	static int			iteration_count = 0;
	enum e_direction	direction;
	double				new[2];

	iteration_count = (iteration_count + 1) % 101;
	if (iteration_count % movement_interval != 0)
		return ;
	direction = rand() % 4;
	new[X] = (*enemy_x);
	new[Y] = (*enemy_y);
	update_position_based_on_direction(direction, &new[X], &new[Y]);
	if (new[X] >= 0 && new[X] < s_i->m_w && new[Y] >= 0 && new[Y] < \
	s_i->m_h && s_i->m[(int)new[Y]][(int)new[X]] != '1' && \
	s_i->m[(int)new[Y]][(int)new[X]] != '2')
	{
		adjust_position_if_wall(s_i, &new[X], &new[Y]);
		*enemy_x = new[X];
		*enemy_y = new[Y];
		if ((int)*enemy_x == (int)s_i->c->player.pos[X] && \
		(int)*enemy_y == (int)s_i->c->player.pos[Y])
			s_i->c->game_status = 1;
	}
}
