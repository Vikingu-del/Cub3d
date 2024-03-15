/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_events.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetruni <ipetruni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 14:11:07 by ipetruni          #+#    #+#             */
/*   Updated: 2024/02/13 14:12:28 by ipetruni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	mouse_release(int button, int x, int y, void *param)
{
	t_cube	*cub;

	(void) cub;
	(void) button;
	(void) x;
	(void) y;
	cub = (t_cube *)param;
	return (EXIT_SUCCESS);
}

int	mouse_press(int button, int x, int y, void *param)
{
	t_cube	*cub;

	(void) cub;
	(void) button;
	(void) x;
	(void) y;
	cub = (t_cube *)param;
	return (EXIT_SUCCESS);
}

int	mouse_move(int x, int y, void *param)
{
	t_cube			*cub;
	static t_point	old_pos;
	float			diff;
	float			step;

	cub = (t_cube *)param;
	diff = old_pos.x - x;
	step = diff / 10;
	cub->player.front = rotate_vec(cub->player.front, step);
	cub->player.cam = cub->player.front;
	old_pos.x = x;
	old_pos.y = y;
	return (EXIT_SUCCESS);
}
