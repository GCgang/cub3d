# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaehjoo <jaehjoo@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/08 12:49:53 by jaehjoo           #+#    #+#              #
#    Updated: 2023/06/08 12:53:29 by jaehjoo          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS = -Werror -Wall -Wextra
AR = ar
ARFLAGS = rc
NAME = pars.a
HEADER = ./cub3d.h ./get_next_line.h
RM = rm -f
SRC = check_map_utils check_map file_utils finalize ft_split get_next_line_utils get_next_line initialize list_utils pars parse_utils rgb_utils str_utils map_surround_check_utils
SRCC = $(addsuffix .c, $(SRC))
OBJ = $(addsuffix .o, $(SRC))
SRC_BNS = check_map_utils_bonus check_map_bonus file_utils_bonus finalize_bonus ft_split_bonus get_next_line_utils_bonus get_next_line_bonus initialize_bonus list_utils_bonus pars_bonus parse_utils_bonus rgb_utils_bonus str_utils_bonus map_surround_check_utils_bonus
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