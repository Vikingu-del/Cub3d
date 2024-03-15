/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eseferi <eseferi@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 14:56:30 by ipetruni          #+#    #+#             */
/*   Updated: 2024/02/27 16:38:07 by eseferi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	allocate_text_pixels(t_cube *cube)
{
	int	i;

	i = 0;
	if (cube->wall_text.text_pixels)
		free_2darray((void **)cube->wall_text.text_pixels);
	cube->wall_text.text_pixels = ft_calloc(cube->screen.height \
	+ 1, sizeof * cube->wall_text.text_pixels);
	if (cube->wall_text.text_pixels == NULL)
		exit_program(cube, 1, MALLOC_ERROR);
	while (i < cube->screen.height)
	{
		cube->wall_text.text_pixels[i] = ft_calloc(cube->screen.width \
		+ 1, sizeof * cube->wall_text.text_pixels);
		if (cube->wall_text.text_pixels[i] == NULL)
			exit_program(cube, 1, MALLOC_ERROR);
		i++;
	}
}

void	set_image_pixel(t_img *img, int i[2], int color)
{
	int	pixel;

	pixel = i[Y] * (img->line_length / 4) + i[X];
	img->casted_addr[pixel] = color;
}

void	set_frame_image_pixel(t_cube *cube, t_img *img, int i[2])
{
	if (cube->wall_text.text_pixels[i[Y]][i[X]] > 0)
		set_image_pixel(img, i, cube->wall_text.text_pixels[i[Y]][i[X]]);
	else if (i[Y] < cube->screen.height / 2)
		set_image_pixel(img, i, cube->map.c_col);
	else if (i[Y] < cube->screen.height - 1 && i[Y] >= cube->screen.height / 2)
		set_image_pixel(img, i, cube->map.f_col);
}

void	render_frame(t_cube *cube)
{
	t_img	img;
	int		i[2];

	img.img = mlx_new_image(cube->screen.mlx, \
	cube->screen.width, cube->screen.height);
	if (img.img == NULL)
		exit_program(cube, 1, MLX_IMG_ERROR);
	img.casted_addr = (int *)mlx_get_data_addr(img.img, \
	&img.bpp, &img.line_length, &img.endian);
	i[Y] = -1;
	while (++i[Y] < cube->screen.height)
	{
		i[X] = -1;
		while (++i[X] < cube->screen.width)
			set_frame_image_pixel(cube, &img, i);
	}
	mlx_put_image_to_window(cube->screen.mlx, cube->screen.win, img.img, 0, 0);
	mlx_destroy_image(cube->screen.mlx, img.img);
}
