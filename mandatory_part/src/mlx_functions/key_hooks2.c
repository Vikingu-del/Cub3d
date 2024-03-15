/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetruni <ipetruni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 14:17:43 by ipetruni          #+#    #+#             */
/*   Updated: 2024/02/13 14:17:49 by ipetruni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	increase_player_speed(t_cube *cube)
{
	if (cube->player.player_speed < 0.45)
		cube->player.player_speed += 0.01;
	if (cube->player.player_rot_speed < 0.1)
		cube->player.player_rot_speed += 0.01;
}

void	decrease_player_speed(t_cube *cube)
{
	if (cube->player.player_speed > 0.06)
		cube->player.player_speed -= 0.01;
	if (cube->player.player_rot_speed > 0.04)
		cube->player.player_rot_speed -= 0.01;
}
