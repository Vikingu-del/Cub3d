/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eseferi <eseferi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 16:32:02 by ipetruni          #+#    #+#             */
/*   Updated: 2024/04/12 12:24:49 by eseferi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	window_close(t_cube *cube)
{
	cleanup(cube, EXIT_SUCCESS);
	return (0);
}

void	check_args(int argc, char *argv[])
{
	if (argc != 2)
		exit_program(NULL, EXIT_FAILURE, WRONG_NUM_OF_ARGS);
	if (ft_strncmp(argv[1] + ft_strlen(argv[1]) - 4, ".cub", 4))
		exit_program(NULL, EXIT_FAILURE, WRONG_FILE_EXT);
	if (ft_strncmp(argv[1], "maps/mand_maps/", 15))
		exit_program(NULL, EXIT_FAILURE, WRONG_FILE_LOC);
	if (ft_strlen(argv[1]) < 10)
		exit_program(NULL, EXIT_FAILURE, WRONG_FILE_NAMING);
}

void	parse(char *map_path, t_cube *cube)
{
	init_cube(cube);
	parse_file(map_path, &cube->map.map_file, cube);
	parse_map(cube->map.map_file, cube);
	check_walls (cube);
}

int	main(int argc, char *argv[])
{
	t_cube	cube;

	check_args(argc, argv);
	ft_bzero(&cube, sizeof(t_cube));
	init_window(&cube);
	parse(argv[1], &cube);
	render_cube(&cube);
	if (hooking(&cube))
		exit_program(&cube, EXIT_FAILURE, HOOKING_ERROR);
}
