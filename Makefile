# Variables
CC					=	gcc -Wall -Wextra -Werror
CFLAGS				=	-Iinc -Isrc -O3 -g -I/usr/X11/include #-fsanitize=address -fno-omit-frame-pointer #-I/usr/include/X11/include/

RM					=	rm -rf

# Libraries
LIBFT				=	libft.a
LIBFT_DIR			=	lib/libft
LIBFT_FILE			=	$(LIBFT_DIR)/$(LIBFT)
CFLAGS				+=	-I $(LIBFT_DIR)/inc

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
LDFLAGS = -L$(MLX_DIR) -L /usr/X11/lib -lmlx -framework OpenGL -framework AppKit -lX11
CFLAGS += -I$(MLX_DIR)
# Linux
else
MLX_DIR = $(MLX_LIN)
MLX_FILE = $(MLX_DIR)/libmlx.a
LDFLAGS = -L$(MLX_DIR) -L/usr/lib/x86_64-linux-gnu/ -lX11 -lXext -lm -lbsd -lmlx
CFLAGS += -I$(MLX_DIR)
endif


MAKE_LIB			=	make --no-print-directory -C

# Source and Object Files
VPATH			=	mandatory_part:bonus_part:includes:src/drawers:src/geometry:src/mlx_window:src/parser:src/startup:include
SRC_DIR = src
SRC_MAND = $(shell find $(SRC_DIR)/mandatory_src -name '*.c')
SRC_BONUS = $(shell find $(SRC_DIR)/bonus_src -name '*.c')
INC_DIR = inc
INC_BONUS = $(INC_DIR)/bonus_inc
INC_MAND = $(INC_DIR)/mandatory_inc

# Object Files
OBJ_DIR = obj
OBJ_MAND = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_MAND))
OBJ_BONUS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_BONUS))

# Rules
all:				mandatory bonus

mandatory:			CFLAGS += -I$(INC_MAND)
mandatory:			$(LIBFT_FILE) $(MLX_FILE) $(OBJ_MAND)
					@$(CC) $(CFLAGS) $(OBJ_MAND) $(LIBFT_FILE) $(MLX_FILE) $(LDFLAGS) -o cub3D
					@echo "$(GREEN)cub3D was successfully created!$(DEFAULT)"

bonus:				CFLAGS += -I$(INC_BONUS)
bonus:				$(LIBFT_FILE) $(MLX_FILE) $(OBJ_BONUS)
					@$(CC) $(CFLAGS) $(OBJ_BONUS) $(LIBFT_FILE) $(MLX_FILE) $(LDFLAGS) -o cub3D_bonus
					@echo "$(GREEN)cub3D_bonus was successfully created!$(DEFAULT)"

$(OBJ_DIR)/%.o:		$(SRC_DIR)/%.c
					@mkdir -p $(dir $@)
					@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT_FILE):
					$(MAKE_LIB) $(LIBFT_DIR)

$(MLX_FILE):
					@$(MAKE_LIB) $(MLX_DIR)

lib_clean:
					$(MAKE_LIB) $(LIBFT_DIR) clean
					$(MAKE_LIB) $(MLX_DIR) clean

lib_fclean:
					$(MAKE_LIB) $(LIBFT_DIR) fclean
					$(MAKE_LIB) $(MLX_DIR) clean

clean:				lib_clean
					$(RM) $(OBJ_DIR)
					@echo "$(YELLOW)Object files deleted!$(DEFAULT)"

fclean:				clean lib_fclean
					$(RM) cub3D cub3D_bonus
					@echo "$(RED)Programs deleted!$(DEFAULT)"

re:					fclean all

# Valgrind testing
valgrind:			mandatory bonus
					$(VALGRIND) ./cub3D maps/testing.cub
					$(VALGRIND) ./cub3D_bonus maps/testing.cub

# Leaks at exit testing
leaks:				mandatory bonus
					$(LEAKS_AT_EXIT) ./cub3D maps/testing.cub
					$(LEAKS_AT_EXIT) ./cub3D_bonus maps/testing.cub

leaks_valgrind:		mandatory bonus
					$(VALGRIND_LEAKS) ./cub3D maps/testing.cub
					$(VALGRIND_LEAKS) ./cub3D_bonus maps/testing.cub

.SILENT:

.PHONY:				all lib_clean lib_fclean clean fclean re

# COLORS DEFINITION
RED				= \033[1;31m
DEFAULT			= \033[0m
GREEN			= \033[1;32m
BOLD			= \033[1m
YELLOW			= \033[1;33m