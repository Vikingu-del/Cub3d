/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_info2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetruni <ipetruni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 12:36:02 by ipetruni          #+#    #+#             */
/*   Updated: 2024/02/13 12:36:15 by ipetruni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parse_floor_color(char *trimmed_line, t_cube *cube)
{
	int	parse_result;

	parse_result = parse_color_code(trimmed_line, cube->map.floor_col);
	if (parse_result == 0)
	{
		free(trimmed_line);
		exit_program(cube, 1, INV_NUM_COL_FLOOR);
	}
	else if (parse_result == -1)
	{
		free(trimmed_line);
		exit_program(cube, 1, INV_RGB_COL_FLOOR);
	}
}

void	parse_ceiling_color(char *trimmed_line, t_cube *cube)
{
	int	parse_result;

	parse_result = parse_color_code(trimmed_line, cube->map.ceiling_col);
	if (parse_result == 0)
	{
		free(trimmed_line);
		exit_program(cube, 1, INV_NUM_COL_CEIL);
	}
	else if (parse_result == -1)
	{
		free(trimmed_line);
		exit_program(cube, 1, INV_RGB_COL_CEIL);
	}
}

void	parse_map_lines(char *line, char **buffer, t_cube *cube)
{
	static int	map_height = 0;
	static int	map_width = 0;

	if (is_valid_line(line, cube) > 1)
		exit_program(cube, 1, MULT_PLAYERS);
	buffer[map_height] = custom_strdup(line);
	if (buffer[map_height] == NULL)
		exit_program(cube, 1, DUPLICATE_ERROR);
	map_height++;
	if ((int)ft_strlen(line) > map_width)
		map_width = ft_strlen(line);
	cube->map.map_height = map_height;
	cube->map.map_width = map_width;
}
