/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segfault <segfault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 16:23:32 by ipetruni          #+#    #+#             */
/*   Updated: 2024/02/16 10:34:48 by segfault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# define WRONG_NUM_OF_ARGS "❌ Cube error: Wrong number of arguments\n"
# define WRONG_FILE_EXT "❌ Cube error: Wrong file extension\n"
# define WRONG_FILE_LOC "❌ Cube error: Wrong file location\n"
# define WRONG_FILE_NAMING "❌ Cube error: Wrong file naming\n"
# define EMPTY_MAP "❌ Cube error: Empty map\n"
# define EMPTY_FILE "❌ Cube error: Empty file\n"
# define READ_FILE_ERROR "❌ Cube error: File doesn't exist or failed to read!\n"

# define DISPLAY_ERROR "❌ Display error: Failed to open display\n"
# define MLX_ERROR "❌ Mlx error: Failed to initialize mlx\n"
# define MLX_WIN_ERROR "❌ Mlx error: Failed to create window\n"
# define MLX_IMG_ERROR "❌ Mlx error: Failed to create image\n"

# define MALLOC_ERROR "❌ Malloc error: Failed to allocate memory\n"
# define DUPLICATE_ERROR "❌ Duplicate error: Failed to duplicate string\n"

# define INV_NUM_COL_FLOOR "❌ Cube error: Invalid syntax in floor colors\n"
# define INV_RGB_COL_FLOOR "❌ Cube error: Invalid RGB values in floor colors\n"
# define INV_NUM_COL_CEIL "❌ Cube error: Invalid syntax in ceiling colors\n"
# define INV_RGB_COL_CEIL "❌ Cube error: Invalid RGB values in ceiling colors\n"
# define INV_CHARS "❌ Cube error: Invalid characters in map\n"
# define MULT_PLAYERS "❌ Cube error: Multiple players\n"
# define NO_PLAYER "❌ Cube error: No player\n"
# define TOO_MANY_TEXTURES "❌ Cube error: Too many textures\n"

# define UNCLOSED_MAP "❌ Cube error: Map is not enclosed\n"
# define TEXT_UNEXIST "❌ Texture error: Texture does not exist\n"
# define TEXT_DIR_ERR "❌ Texture error: Invalid texture direction\n"
# define TEXT_LOC_ERR "❌ Texture error: Invalid texture location\n"
# define TEXT_EXT_ERR "❌ Texture error: Invalid texture extension\n"
# define TEXT_ERR_FORMAT "❌ Texture error: Invalid texture format\n"
# define TEXT_LOAD_ERR "❌ Texture error: Failed to load texture\n"

# define HOOKING_ERROR "❌ Hooking error: Failed to hook events\n"

#endif