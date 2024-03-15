/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_floor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eseferi <eseferi@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 13:04:04 by eseferi           #+#    #+#             */
/*   Updated: 2024/02/29 13:35:14 by eseferi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render_game_over(t_cube *cube)
{
	int	i;
	int	j;

	i = 0;
	while (i < cube->screen.height)
	{
		j = 0;
		while (j < cube->screen.width)
		{
			cube->text_pixels[i][j] = 0x00FF0000;
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(cube->screen.mlx, cube->screen.win, \
	cube->screen.img.img, 0, 0);
	mlx_string_put(cube->screen.mlx, cube->screen.win, \
	cube->screen.width / 2 - 100, \
	cube->screen.height / 2, 0x00FF0000, "GAME OVER!");
	mlx_do_sync(cube->screen.mlx);
	usleep(1000000);
	exit_program(cube, EXIT_SUCCESS, "Game Over");
}

void	render_win_screen(t_cube *cube)
{
	int	i;
	int	j;

	i = 0;
	while (i < cube->screen.height)
	{
		j = 0;
		while (j < cube->screen.width)
		{
			cube->text_pixels[i][j] = 0x00FF0000;
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(cube->screen.mlx, cube->screen.win, \
	cube->screen.img.img, 0, 0);
	mlx_string_put(cube->screen.mlx, cube->screen.win, cube->screen.width / 2 \
	- 100, cube->screen.height / 2, 0x00FF0000, "YOU WIN!");
	mlx_do_sync(cube->screen.mlx);
	usleep(1000000);
	exit_program(cube, EXIT_SUCCESS, "You Win");
}

static void	update_left_right_rays(t_cube *c)
{
	c->player.ray.ray_dir_l.dir[X] = c->player.front.dir[X]
		- c->player.cam.dir[X];
	c->player.ray.ray_dir_l.dir[Y] = c->player.front.dir[Y]
		- c->player.cam.dir[Y];
	c->player.ray.ray_dir_r.dir[X] = c->player.front.dir[X]
		+ c->player.cam.dir[X];
	c->player.ray.ray_dir_r.dir[Y] = c->player.front.dir[Y]
		+ c->player.cam.dir[Y];
}

static void	setup_floor_param(t_floor_info *inf, t_cube *c, int y)
{
	inf->x = 0;
	update_left_right_rays(c);
	inf->p = y - c->screen.height / 2;
	inf->pos_z = 0.5 * c->screen.height;
	inf->row_distance = inf->pos_z / inf->p;
	inf->floor_step[X] = inf->row_distance * (c->player.ray.ray_dir_r.dir[X] \
	- c->player.ray.ray_dir_l.dir[X]) / c->screen.width;
	inf->floor_step[Y] = inf->row_distance * (c->player.ray.ray_dir_r.dir[Y] \
	- c->player.ray.ray_dir_l.dir[Y]) / c->screen.width;
	inf->floor[X] = c->player.pos[X] + inf->row_distance * \
	c->player.ray.ray_dir_l.dir[X];
	inf->floor[Y] = c->player.pos[Y] + inf->row_distance * \
	c->player.ray.ray_dir_l.dir[Y];
}

void	cast_floor(t_cube *c, int y)
{
	t_floor_info	inf;

	setup_floor_param(&inf, c, y);
	while (inf.x < c->screen.width)
	{
		inf.cell[X] = (int)(inf.floor[X]);
		inf.cell[Y] = (int)(inf.floor[Y]);
		inf.t[X] = (int)(c->wall_text.tex_size * (inf.floor[X] - inf.cell[X])) \
		& (c->wall_text.tex_size - 1);
		inf.t[Y] = (int)(c->wall_text.tex_size * (inf.floor[Y] - inf.cell[Y])) \
		& (c->wall_text.tex_size - 1);
		inf.floor[X] += inf.floor_step[X];
		inf.floor[Y] += inf.floor_step[Y];
		c->text_pixels[y][inf.x] = \
		(c->wall_text.textures[F][c->wall_text.tex_size * inf.t[Y] \
		+ inf.t[X]] >> 1) & 8355711;
		c->text_pixels[c->screen.height - y - 1][inf.x] = \
		(c->wall_text.textures[C][c->wall_text.tex_size * inf.t[Y] \
		+ inf.t[X]] >> 1) & 8355711;
		inf.x++;
	}
}
