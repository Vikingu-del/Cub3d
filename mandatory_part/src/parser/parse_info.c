/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetruni <ipetruni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 13:43:22 by ipetruni          #+#    #+#             */
/*   Updated: 2024/02/29 17:03:16 by ipetruni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	load_image(t_cube *cube, t_img *img, char *path, void *mlx)
{
	img->img = mlx_xpm_file_to_image(mlx, path, \
	&cube->wall_text.tex_size, &cube->wall_text.tex_size);
	if (img->img == NULL)
		exit_program(cube, 1, TEXT_LOAD_ERR);
	img->casted_addr = (int *)mlx_get_data_addr(img->img, \
	&img->bpp, &img->line_length, &img->endian);
}

void	allocate_buffer(t_cube *cube, int **buffer)
{
	*buffer = ft_calloc(1, sizeof **buffer \
	* cube->wall_text.tex_size * cube->wall_text.tex_size);
	if (!(*buffer))
		exit_program(cube, EXIT_FAILURE, MALLOC_ERROR);
}

void	fill_texture(t_cube *cube, t_img *img, int *buffer)
{
	int	i[2];

	i[Y] = -1;
	while (++i[Y] < cube->wall_text.tex_size)
	{
		i[X] = -1;
		while (++i[X] < cube->wall_text.tex_size)
			buffer[i[Y] * cube->wall_text.tex_size \
		+ i[X]] = img->casted_addr[i[Y] * cube->wall_text.tex_size + i[X]];
	}
}

void	load_texture(t_cube *cube)
{
	int		*buffer;
	t_img	*img;
	char	*path;
	void	*mlx;

	img = &cube->wall_text.img_text[cube->map.num_textures];
	path = cube->map.texture[cube->map.num_textures];
	mlx = cube->screen.mlx;
	load_image(cube, img, path, mlx);
	allocate_buffer(cube, &buffer);
	cube->wall_text.textures[cube->map.num_textures] = buffer;
	fill_texture(cube, img, buffer);
	mlx_destroy_image(mlx, img->img);
}

void	parse_textures(char *trimmed_line, t_cube *cube)
{
	char		*texture_path;
	static int	i = 0;

	if (cube->map.num_textures >= MAX_NUM_TEXT)
		exit_program(cube, 1, TOO_MANY_TEXTURES);
	if (check_text_dir(trimmed_line, i) == -1)
		exit_program(cube, 1, TEXT_DIR_ERR);
	texture_path = ft_strdup(trimmed_line + 3);
	if (texture_path == NULL)
		exit_program(cube, 1, DUPLICATE_ERROR);
	cube->map.texture[cube->map.num_textures] = texture_path;
	load_texture(cube);
	cube->map.num_textures++;
	i++;
}
