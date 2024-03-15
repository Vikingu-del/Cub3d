/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_info2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eseferi <eseferi@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 12:36:02 by ipetruni          #+#    #+#             */
/*   Updated: 2024/02/29 12:42:24 by eseferi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_valid_line(char *line, t_cube *cube)
{
	static int	player_dir = 0;
	static int	info[3] = {0, 0, 0};
	int			i;

	i = 0;
	while (line && line[i] && line[i] != '\n')
	{
		if (!is_valid_char(line[i]))
			exit_program(cube, 1, INV_CHARS);
		if (line[i] == 'N' || line[i] == 'S'
			|| line[i] == 'E' || line[i] == 'W')
			player_dir++;
		if (line[i] == '2')
			info[DOOR]++;
		if (line[i] == '3')
			info[KEY]++;
		if (line[i] == '4')
			info[ENEMY]++;
		i++;
	}
	if (player_dir > 1 || info[DOOR] > 1 || info[KEY] > 1 || info[ENEMY] > 1)
		multiple_error(player_dir, info);
	return (player_dir);
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
