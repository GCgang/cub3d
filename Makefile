CFLAGS = -Werror -Wall -Wextra
PARSA = ./pars/pars.a
EXECA = ./exec/exec.a
LIBMLX = -L./minilibx/ -lmlx -framework OpenGL -framework AppKit
MLX = ./minilibx/libmlx.a
RM = rm -rf
SRC = main
SRCC = $(addsuffix .c, $(addprefix share/src/, $(SRC)))
OBJ = $(SRCC:c=o)
SRC_BNS = main_bonus
SRCC_BNS = $(addsuffix .c, $(addprefix share/src/, $(SRC_BNS)))
OBJ_BNS = $(SRCC_BNS:c=o)
PARS_SRC = check_map_utils check_map file_utils finalize ft_split get_next_line_utils get_next_line initialize list_utils pars parse_utils rgb_utils str_utils
PARS_SRCC = $(addsuffix .c, $(addprefix pars/, $(PARS_SRC)))
PARS_BNS_SRC = check_map_utils_bonus check_map_bonus file_utils_bonus finalize_bonus ft_split_bonus get_next_line_utils_bonus get_next_line_bonus initialize_bonus list_utils_bonus pars_bonus parse_utils_bonus rgb_utils_bonus str_utils_bonus map_surround_check_utils_bonus
PARS_BNS_SRCC = $(addsuffix .c, $(addprefix pars/src_bonus/, $(PARS_BNS_SRC)))
EXEC_SRC = exec hook mouse_hook key_hook loop raycasting init_utils map_utils minimap texture
EXEC_SRCC = $(addsuffix .c, $(addprefix exec/src/, $(EXEC_SRC)))
EXEC_BNS_SRC = exec_bonus hook_bonus mouse_hook_bonus key_hook_bonus loop_bonus raycasting_bonus init_utils_bonus map_utils_bonus minimap_bonus texture_bonus
EXEC_BNS_SRCC = $(addsuffix .c, $(addprefix exec/src_bonus/, $(EXEC_BNS_SRC)))
HEADER = ./share/init.h
INCLUDES = -I./share
NAME = cub3D
ifdef LINK_BONUS
	OBJ_FILES = $(OBJ_BNS)
	AR_MAKING = make bonus
else
	OBJ_FILES = $(OBJ)
	AR_MAKING = make
endif

all : $(NAME)

$(NAME): $(OBJ_FILES) $(PARSA) $(EXECA) $(MLX)
			$(CC) $(CFLAGS) $(LIBMLX) $(PARSA) $(EXECA) $(OBJ_FILES) $(INCLUDES) -o $(NAME)

%.o: %.c $(HEADER)
			$(CC) -c $(CFLAGS) $(OBJ_FLAGS) $< -o $@ $(INCLUDES)

$(PARSA): $(PARS_SRCC) $(PARS_BNS_SRCC)
		  $(AR_MAKING) -sC ./pars/

$(EXECA): $(EXEC_SRCC) $(EXEC_BNS_SRCC)
		  $(AR_MAKING) -sC ./exec/

$(MLX):
			make -sC ./minilibx/

bonus:
			make LINK_BONUS=1 all

clean:
			$(RM) $(OBJ) $(OBJ_BNS)
			make -sC ./pars clean
			make -sC ./exec clean
			make -sC ./minilibx clean

fclean:
			make -s clean
			make -sC ./pars fclean
			make -sC ./exec fclean
			$(RM) $(NAME) ./minilibx/libmlx.a

re:
			make -s fclean
			make -s all

.PHONY: all clean fclean re
