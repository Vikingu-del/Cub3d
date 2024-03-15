/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetruni <ipetruni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 14:57:07 by ipetruni          #+#    #+#             */
/*   Updated: 2024/02/13 14:57:23 by ipetruni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	render_cube(t_cube *cube)
{
	allocate_text_pixels(cube);
	init_ray(&cube->player.ray);
	raycast(cube, &cube->player.ray);
	return (0);
}

int	render(t_cube *cube)
{
	keys_execute(cube);
	render_cube(cube);
	return (0);
}
