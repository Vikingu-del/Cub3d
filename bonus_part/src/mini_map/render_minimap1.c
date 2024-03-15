/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_minimap1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetruni <ipetruni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 16:42:20 by ipetruni          #+#    #+#             */
/*   Updated: 2024/02/26 16:45:23 by ipetruni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_tab(void **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	if (tab)
	{
		free(tab);
		tab = NULL;
	}
}

void	init_img_clean(t_img *img)
{
	img->img = NULL;
	img->addr = NULL;
	img->bpp = 0;
	img->line_length = 0;
	img->endian = 0;
}

void	init_img(t_cube *cube, t_img *image, int width, int height)
{
	init_img_clean(image);
	image->img = mlx_new_image(cube->screen.mlx, width, height);
	if (image->img == NULL)
		exit_program(cube, 1, "Error: mlx_new_image failed");
	image->addr = mlx_get_data_addr(image->img, &image->bpp,
			&image->line_length, &image->endian);
	return ;
}

void	render_minimap_image(t_cube *cube, t_minimap *minimap)
{
	int	img_size;

	img_size = MMAP_PIXEL_SIZE;
	init_img(cube, &cube->minimap, img_size, img_size);
	draw_minimap(minimap);
	mlx_put_image_to_window(cube->screen.mlx, cube->screen.win,
		cube->minimap.img, 10, cube->screen.height
		- (MMAP_PIXEL_SIZE + 15));
	mlx_destroy_image(cube->screen.mlx, cube->minimap.img);
}

void	mm_set_image_pixel(t_img *image, int x, int y, int color)
{
	int	pixel;

	pixel = y * image->line_length + x * (image->bpp / 8);
	image->addr[pixel + 0] = (color >> 0) & 0xFF;
	image->addr[pixel + 1] = (color >> 8) & 0xFF;
	image->addr[pixel + 2] = (color >> 16) & 0xFF;
	image->addr[pixel + 3] = (color >> 24) & 0xFF;
}
