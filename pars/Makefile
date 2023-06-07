CFLAGS = -Werror -Wall -Wextra
AR = ar
ARFLAGS = rc
NAME = pars.a
HEADER = ./cub3d.h ./get_next_line.h
RM = rm -f
SRC = check_map_utils check_map file_utils finalize ft_split get_next_line_utils get_next_line initialize list_utils pars parse_utils rgb_utils str_utils map_surround_check_utils
SRCC = $(addsuffix .c, $(SRC))
OBJ = $(addsuffix .o, $(SRC))

all : $(NAME)

$(NAME) : $(OBJ)
	$(AR) $(ARFLAGS) $@ $^

%.o : %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@ -I .

clean : 
	$(RM) $(OBJ)

fclean :
	make -s clean
	$(RM) $(NAME)

re :
	make -s fclean
	make -s all

.PHONY : all clean fclean re