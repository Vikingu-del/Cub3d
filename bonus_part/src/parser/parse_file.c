/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipetruni <ipetruni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 17:55:39 by ipetruni          #+#    #+#             */
/*   Updated: 2024/02/26 17:00:26 by ipetruni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	read_file_and_store_lines(char *path, char ***buffer, t_cube *cube)
{
	int		fd;
	char	*line;
	int		count;

	count = 0;
	*buffer = ft_calloc(MAX_LINES, sizeof(char *));
	if (!*buffer)
		exit_program(cube, 1, MALLOC_ERROR);
	read_file(path, &fd, cube);
	line = get_next_line(fd);
	while (line)
	{
		(*buffer)[count] = ft_strdup(line);
		count++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (count);
}

static int	copy_lines_to_map_file(char ***map_file, char **buffer, int count)
{
	int		i;

	i = 0;
	*map_file = malloc((count + 1) * sizeof(char *));
	if (!*map_file)
		return (1);
	while (i < count)
	{
		if (buffer[i])
		{
			(*map_file)[i] = ft_strdup(buffer[i]);
			if ((*map_file)[i] == NULL)
				return (1);
		}
		i++;
	}
	(*map_file)[count] = NULL;
	free_2darray((void **)buffer);
	return (0);
}

void	parse_file(char *map_path, char ***map_file, t_cube *cube)
{
	char	**buffer;
	int		count;

	count = read_file_and_store_lines(map_path, &buffer, cube);
	if (!count)
	{
		free_2darray((void **)buffer);
		exit_program(cube, 1, EMPTY_FILE);
	}
	count = copy_lines_to_map_file(map_file, buffer, count);
	if (count)
		exit_program(cube, 1, MALLOC_ERROR);
}
