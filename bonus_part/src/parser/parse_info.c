/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eseferi <eseferi@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 13:43:22 by ipetruni          #+#    #+#             */
/*   Updated: 2024/02/29 12:37:00 by eseferi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_text_dir(char *text, int i)
{
	if ((i == NO && !ft_strncmp(text, "NO ", 3))
		|| (i == SO && !ft_strncmp(text, "SO ", 3))
		|| (i == EA && !ft_strncmp(text, "EA ", 3))
		|| (i == WE && !ft_strncmp(text, "WE ", 3))
		|| (i == C && !ft_strncmp(text, "C ", 2))
		|| (i == F && !ft_strncmp(text, "F ", 2)))
		return (0);
	else
		return (-1);
}

static void	copy_texture_data(int *i, t_text_info *text_info)
{
	i[X] = -1;
	while (++i[X] < text_info->cube->wall_text.tex_size)
	{
		(*text_info->tx)[i[Y] * text_info->cube->wall_text.tex_size \
		+ i[X]] = text_info->img->casted_addr[i[Y] * \
		text_info->cube->wall_text.tex_size + i[X]];
	}
}

void	load_texture(t_text_info *text_info)
{
	int	i[2];
	int	*buffer;

	text_info->img->img = mlx_xpm_file_to_image(text_info->mlx, \
	text_info->path, &text_info->cube->wall_text.tex_size, \
	&text_info->cube->wall_text.tex_size);
	if (text_info->img->img == NULL)
		exit_program(text_info->cube, 1, TEXT_LOAD_ERR);
	text_info->img->casted_addr = (int *) \
	mlx_get_data_addr(text_info->img->img, &text_info->img->bpp, \
	&text_info->img->line_length, &text_info->img->endian);
	i[Y] = -1;
	buffer = ft_calloc(1, sizeof * buffer \
	* text_info->cube->wall_text.tex_size * \
	text_info->cube->wall_text.tex_size);
	if (!buffer)
		exit_program(text_info->cube, EXIT_FAILURE, MALLOC_ERROR);
	(*text_info->tx) = buffer;
	while (++i[Y] < text_info->cube->wall_text.tex_size)
		copy_texture_data(i, text_info);
	mlx_destroy_image(text_info->mlx, text_info->img->img);
}

void	parse_textures(char *trimmed_line, t_cube *cube)
{
	char		*texture_path;
	static int	i = 0;
	t_text_info	text_info;

	if (cube->map.num_textures >= MAX_NUM_TEXT)
		exit_program(cube, 1, TOO_MANY_TEXTURES);
	if (check_text_dir(trimmed_line, i) == -1)
		exit_program(cube, 1, TEXT_DIR_ERR);
	if (i == F || i == C)
		texture_path = ft_strdup(trimmed_line + 2);
	else
		texture_path = ft_strdup(trimmed_line + 3);
	if (texture_path == NULL)
		exit_program(cube, 1, DUPLICATE_ERROR);
	cube->map.texture[cube->map.num_textures] = texture_path;
	text_info.img = &cube->wall_text.img_text[cube->map.num_textures];
	text_info.mlx = cube->screen.mlx;
	text_info.path = texture_path;
	text_info.cube = cube;
	text_info.tx = &cube->wall_text.textures[cube->map.num_textures];
	load_texture(&text_info);
	cube->map.num_textures++;
	i++;
}
