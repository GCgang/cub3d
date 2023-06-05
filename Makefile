CFLAGS = -Werror -Wall -Wextra
PARSA = ./pars/pars.a
EXECA = ./exec/exec.a
LIBMLX = -L./minilibx/ -lmlx -framework OpenGL -framework AppKit
MLX = ./minilibx/libmlx.a
RM = rm -rf
SRC = main
SRCC = $(addsuffix .c, $(addprefix share/src/, $(SRC)))
OBJ = $(SRCC:c=o)
PARS_SRC = check_map_utils check_map file_utils finalize ft_split get_next_line_utils get_next_line initialize list_utils pars parse_utils rgb_utils str_utils
PARS_SRCC = $(addsuffix .c, $(addprefix pars/, $(PARS_SRC)))
EXEC_SRC = exec hook key_hook loop minimap mouse_hook raycasting texture utils
EXEC_SRCC = $(addsuffix .c, $(addprefix exec/src/, $(EXEC_SRC)))
HEADER = ./share/init.h
INCLUDES = -I./share -I./pars/include -I./exec/include
NAME = cub3D

all : $(NAME)

$(NAME): $(OBJ) $(PARSA) $(EXECA) $(MLX)
			$(CC) $(CFLAGS) $(LIBMLX) $(PARSA) $(EXECA) $(OBJ) $(INCLUDES) -o $(NAME)

%.o: %.c $(HEADER)
			$(CC) -c $(CFLAGS) $(OBJ_FLAGS) $< -o $@ $(INCLUDES)

$(PARSA): $(PARS_SRCC)
			make -sC ./pars/

$(EXECA): $(EXEC_SRCC)
			make -sC ./exec/

$(MLX):
			make -sC ./minilibx/

clean:
			$(RM) $(OBJ)
			make -sC ./pars clean
			make -sC ./exec clean
			make -sC ./minilibx clean

fclean:
			make -s clean
			make -sC ./pars fclean
			make -sC ./exec fclean
			$(RM) $(NAME) $(OBJ) ./minilibx/libmlx.a

re:
			make -s fclean
			make -s all

.PHONY: all clean fclean re
