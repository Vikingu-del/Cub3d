/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetruni <ipetruni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 06:16:31 by eseferi           #+#    #+#             */
/*   Updated: 2024/02/13 12:33:06 by ipetruni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	convert_to_rgb(t_map *map)
{
	map->c_col = (map->ceiling_col[0] << 16) \
	+ (map->ceiling_col[1] << 8) + map->ceiling_col[2];
	map->f_col = (map->floor_col[0] << 16) \
	+ (map->floor_col[1] << 8) + map->floor_col[2];
}

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
			|| !ft_strncmp(trimmed_line, "WE ", 3))
			parse_textures(trimmed_line, cube);
		else if (!ft_strncmp(trimmed_line, "F ", 2))
			parse_floor_color(trimmed_line, cube);
		else if (!ft_strncmp(trimmed_line, "C ", 2))
			parse_ceiling_color(trimmed_line, cube);
		else if (trimmed_line[0] == '1' || trimmed_line[0] == ' '
			|| trimmed_line[0] == '0')
			parse_map_lines(map_file[i], buffer, cube);
		free(trimmed_line);
	}
	convert_to_rgb(&cube->map);
}

void	parse_textures_files(t_cube *cube)
{
	int	i;

	i = NO;
	while (i <= EA)
	{
		if (ft_strlen(cube->map.texture[i]) < 16)
			exit_program(cube, 1, TEXT_ERR_FORMAT);
		if (ft_strncmp(cube->map.texture[i], "./textures/", 11))
			exit_program(cube, 1, TEXT_LOC_ERR);
		if (ft_strcmp(&cube->map.texture[i] \
		[ft_strlen(cube->map.texture[i]) - 4], ".xpm"))
			exit_program(cube, 1, TEXT_EXT_ERR);
		i++;
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
	parse_textures_files(cube);
}
