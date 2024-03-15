# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: segfault <segfault@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/14 10:13:44 by ipetruni          #+#    #+#              #
#    Updated: 2024/02/16 10:35:38 by segfault         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Variables
CC					=	gcc -Wall -Wextra -Werror
CFLAGS				=	-Iinc -Isrc -O3 -g -I/usr/X11/include #-fsanitize=address -fno-omit-frame-pointer #-I/usr/include/X11/include/

RM					=	rm -rf
CUB3D				=   cub3D
NAME				=	$(CUB3D)

# Libraries
LIBFT				=	libft.a
LIBFT_DIR			=	lib/libft
LIBFT_FILE			=	$(LIBFT_DIR)/$(LIBFT)
CFLAGS				+=	-I $(LIBFT_DIR)/include

MLX_MAC				=	lib/mlx_mac
MLX_LIN				=	lib/mlx_linux

# Detect the operating system
UNAME_S := $(shell uname -s)

# debug
VALGRIND_LEAKS = valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose
LEAKS_AT_EXIT = leaks --atExit -- 
VALGRIND = valgrind --tool=memcheck

# macOS
ifeq ($(UNAME_S),Darwin)
MLX_DIR = $(MLX_MAC)
MLX_FILE = $(MLX_DIR)/libmlx.a
LDFLAGS = -L$(MLX_DIR) -L /usr/X11/lib -lmlx -framework OpenGL -framework AppKit -lX11 #-lmlx -lX11 -framework OpenGL -framework AppKit

# Linux
else
MLX_DIR = $(MLX_LIN)
MLX_FILE = $(MLX_DIR)/libmlx.a
LDFLAGS = -L$(MLX_DIR) -L/usr/lib/x86_64-linux-gnu/ -lX11 -lXext -lm -lbsd -lmlx
endif

MAKE_LIB			=	make --no-print-directory -C

# Source and Object Files
VPATH			=	src:includes:src/drawers:src/geometry:src/mlx_window:src/parser:src/startup:include
CUB3D_INC		=	CUB3D.h
CUB3D_SRC		=	$(shell find src -name '*.c')

# Object Files
OBJ_DIR				=	obj
CUB3D_OBJ		=	$(addprefix $(OBJ_DIR)/, $(CUB3D_SRC:.c=.o))

# Rules
all:				$(LIBFT_FILE) $(MLX_FILE) $(NAME)

$(OBJ_DIR)/%.o:		%.c
					@mkdir -p $(dir $@)
					@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT_FILE):
					$(MAKE_LIB) $(LIBFT_DIR)

$(MLX_FILE):
					@$(MAKE_LIB) $(MLX_DIR)

$(NAME):			$(CUB3D_OBJ)
					@$(CC) $(CFLAGS) $(CUB3D_OBJ) $(LIBFT_FILE) $(MLX_FILE) $(LDFLAGS) -o $@
					@echo "$(GREEN)$(NAME) was successfully created!$(DEFAULT)"

lib_clean:
					$(MAKE_LIB) $(LIBFT_DIR) clean
					$(MAKE_LIB) $(MLX_DIR) clean

lib_fclean:
					$(MAKE_LIB) $(LIBFT_DIR) fclean
					$(MAKE_LIB) $(MLX_DIR) clean

clean:				lib_clean
					$(RM) $(OBJ_DIR)
					@echo "$(YELLOW)$(NAME) object files deleted!$(DEFAULT)"

fclean:				clean lib_fclean
					$(RM) $(NAME)
					@echo "$(RED)$(NAME) program deleted!$(DEFAULT)"

re:					fclean all

# Valgrind testing
valgrind:			$(NAME)
					$(VALGRIND) ./$(NAME) maps/testing.cub

# Leaks at exit testing
leaks:				$(NAME)
					$(LEAKS_AT_EXIT) ./$(NAME) maps/testing.cub

leaks_valgrind:		$(NAME)
					$(VALGRIND_LEAKS) ./$(NAME) maps/testing.cub

.SILENT:

.PHONY:				all lib_clean lib_fclean clean fclean re

# COLORS DEFINITION
RED				= \033[1;31m
DEFAULT			= \033[0m
GREEN			= \033[1;32m
BOLD			= \033[1m
YELLOW			= \033[1;33m
