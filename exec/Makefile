# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaehjoo <jaehjoo@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/08 11:51:21 by jaehjoo           #+#    #+#              #
#    Updated: 2023/06/08 11:51:22 by jaehjoo          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS = -Wall -Wextra -Werror
ARFLAGS = rc
NAME = exec.a
HEADER = ./include/
RM = rm -f
SRC = exec hook mouse_hook key_hook loop raycasting init_utils map_utils minimap texture error
SRCC = $(addsuffix .c, $(addprefix src/, $(SRC)))
OBJ = $(addsuffix .o, $(addprefix src/, $(SRC)))
SRC_BNS = exec_bonus hook_bonus mouse_hook_bonus key_hook_bonus loop_bonus raycasting_bonus init_utils_bonus map_utils_bonus minimap_bonus texture_bonus error_bonus
SRCC_BNS = $(addsuffix .c, $(addprefix src_bonus/, $(SRC_BNS)))
OBJ_BNS = $(addsuffix .o, $(addprefix src_bonus/, $(SRC_BNS)))
ifdef LINK_BONUS
	OBJ_FILES = $(OBJ_BNS)
else
	OBJ_FILES = $(OBJ)
endif

all : $(NAME)

$(NAME) : $(OBJ_FILES)
	$(AR) $(ARFLAGS) $@ $^

%.o : %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@ -I .

bonus:
	make LINK_BONUS=1 all

clean :
	$(RM) $(OBJ) $(OBJ_BNS)

fclean :
	make -s clean
	$(RM) $(NAME)

re :
	make -s fclean
	make -s all

.PHONY : all clean fclean re