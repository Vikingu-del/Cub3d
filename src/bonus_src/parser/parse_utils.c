/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eseferi <eseferi@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 10:51:08 by ipetruni          #+#    #+#             */
/*   Updated: 2024/02/29 12:45:49 by eseferi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	multiple_error(int player_dir, int info[3])
{
	if (player_dir > 1)
		exit_program(NULL, 1, MULT_PLAYERS);
	if (info[DOOR] > 1)
		exit_program(NULL, 1, MULT_DOORS);
	if (info[KEY] > 1)
		exit_program(NULL, 1, MULT_KEYS);
	if (info[ENEMY] > 1)
		exit_program(NULL, 1, MULT_ENEMIES);
}

bool	is_valid_char(char c)
{
	if (c == '0' || c == '1' || c == 'N' || c == '2' || c == '3' || c == '4'
		|| c == 'S' || c == 'E' || c == 'W' || c == ' ')
		return (true);
	else
		return (false);
}

void	read_file(char *map_path, int *fd, t_cube *cube)
{
	*fd = open(map_path, O_RDONLY);
	if (*fd < 0)
		exit_program(cube, 1, READ_FILE_ERROR);
}

bool	line_has_walls(char *line)
{
	while (*line)
	{
		if (*line == '1')
			return (true);
		line++;
	}
	return (false);
}
