CFLAGS = -Wall -Wextra -Werror
ARFLAGS = rc
NAME = exec.a
HEADER = ./include/
RM = rm -f
SRC = exec hook mouse_hook key_hook loop raycasting utils minimap texture
SRCC = $(addsuffix .c, $(addprefix src/, $(SRC)))
OBJ = $(addsuffix .o, $(addprefix src/, $(SRC)))

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