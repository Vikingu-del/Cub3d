/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eseferi <eseferi@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 06:16:31 by eseferi           #+#    #+#             */
/*   Updated: 2024/02/29 12:40:55 by eseferi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	proceed_mapfile(char **map_file, char **buffer, t_cube *cube)
{
	int		i;
	char	*trimmed_line;

	i = -1;
	while (map_file[++i])
	{
		trimmed_line = trim_whitespace(map_file[i]);
		if (!ft_strncmp(trimmed_line, "NO ", 3)
			|| !ft_strncmp(trimmed_line, "SO ", 3)
			|| !ft_strncmp(trimmed_line, "EA ", 3)
			|| !ft_strncmp(trimmed_line, "WE ", 3)
			|| !ft_strncmp(trimmed_line, "F ", 2)
			|| !ft_strncmp(trimmed_line, "C ", 2))
			parse_textures(trimmed_line, cube);
		else if (trimmed_line[0] == '1' || trimmed_line[0] == ' '
			|| trimmed_line[0] == '0')
			parse_map_lines(map_file[i], buffer, cube);
		free(trimmed_line);
	}
}

void	parse_sprites(t_cube *cube)
{
	int			i;
	t_text_info	text_info;

	text_info.cube = cube;
	text_info.mlx = cube->screen.mlx;
	i = -1;
	while (++i <= DOOR)
	{
		if (i == DOOR)
			text_info.path = "./textures/walls/door.xpm";
		else if (i == KEY)
			text_info.path = "./textures/sprites/key.xpm";
		else
			text_info.path = "./textures/sprites/knight.xpm";
		text_info.tx = &cube->sprite.sprite_text[i].pixels;
		text_info.img = &cube->sprite.sprite_text[i].img;
		load_texture(&text_info);
	}
}

void	parse_map(char **map_file, t_cube *cube)
{
	char	**buffer;
	int		i;

	i = 0;
	buffer = ft_calloc(MAX_LINES, sizeof(char *));
	if (!buffer)
		exit_program(cube, 1, MALLOC_ERROR);
	proceed_mapfile(map_file, buffer, cube);
	cube->map.map = malloc(sizeof(char *) * (cube->map.map_height + 1));
	if (!cube->map.map)
		exit_program(cube, 1, MALLOC_ERROR);
	while (i < cube->map.map_height)
	{
		cube->map.map[i] = ft_strdup(buffer[i]);
		if (cube->map.map[i++] == NULL)
			exit_program(cube, 1, DUPLICATE_ERROR);
	}
	cube->map.map[cube->map.map_height] = NULL;
	free_2darray((void **)buffer);
	parse_player(cube);
	parse_sprites(cube);
}
