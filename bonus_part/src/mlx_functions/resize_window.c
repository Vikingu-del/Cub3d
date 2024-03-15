/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize_window.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetruni <ipetruni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 16:38:35 by ipetruni          #+#    #+#             */
/*   Updated: 2024/02/13 14:10:53 by ipetruni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	destroy_window(t_cube *cube)
{
	if (cube->screen.img.img)
	{
		mlx_destroy_image(cube->screen.mlx, cube->screen.img.img);
		cube->screen.img.img = NULL;
	}
	if (cube->screen.win)
	{
		mlx_destroy_window(cube->screen.mlx, cube->screen.win);
		cube->screen.win = NULL;
	}
}

static void	update_dimensions(t_cube *cub, int flag)
{
	if (flag == EXPAND)
	{
		if (cub->screen.height > cub->screen.default_h - 1
			|| cub->screen.width > cub->screen.default_w - 1)
			return ;
		cub->screen.width *= 2;
		cub->screen.height *= 2;
	}
	else if (flag == REDUCE)
	{
		if (cub->screen.height < 355 || cub->screen.width < 641)
			return ;
		cub->screen.width /= 2;
		cub->screen.height /= 2;
	}
}

static void	init_new_window(t_cube *cube)
{
	destroy_window(cube);
	cube->screen.win = mlx_new_window(cube->screen.mlx, \
	cube->screen.width, cube->screen.height, "Cub3D");
	if (!cube->screen.win)
		exit_program(cube, EXIT_FAILURE, MLX_WIN_ERROR);
	cube->screen.img.img = mlx_new_image(cube->screen.mlx, \
	cube->screen.width, cube->screen.height);
	if (!cube->screen.img.img)
		exit_program(cube, EXIT_FAILURE, MLX_IMG_ERROR);
	cube->screen.img.addr = mlx_get_data_addr(cube->screen.img.img, \
	&cube->screen.img.bpp, &cube->screen.img.line_length, \
	&cube->screen.img.endian);
}

void	resize_window(t_cube *cub, int flag)
{
	update_dimensions(cub, flag);
	destroy_window(cub);
	init_new_window(cub);
	hooking(cub);
}
