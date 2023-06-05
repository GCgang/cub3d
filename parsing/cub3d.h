/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeoan <hyeoan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 15:26:11 by hyeoan            #+#    #+#             */
/*   Updated: 2023/06/05 13:59:06 by hyeoan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include "get_next_line.h"

# define ARGUMENT_ERROR "Error : Invalid argument count. \
Please provide 2 arguments.\n"
# define FILE_EXTENSION_ERROR "Error : Invalid file extension. \
The file extension must be .cub.\n"
# define TEXTURE_FILE_PATH_ERROR "Error : Invalid texture file path. \
Please provide a valid path to the texture file.\n"
# define RGB_ERROR "Error : Invalid RGB value. \
The provided RGB value should represent the ceiling or floor color \
and must be within the range of 0 to 255.\n"
# define PRE_VALIDATION_ERROR "Pre-validation incomplete. \
Please ensure that the texture file path and ceiling/floor \
RGB values are checked before performing map validation.\n"
# define MAP_SEPARATED_ERROR "Error: Map content cannot be \
separated by one or more empty lines.\n"
# define MAP_VALUE_ERROR "Error : Invalid value. \
Only the following characters are allowed in the map: 0 (empty space), \
1 (wall), N (north), W (west), S (south), E (east), and spaces.\n"
# define MAP_CONFIGURATION_ERROR "Error : Invalid map configuration. \
The map should be surrounded by walls (1) on all sides.\n"
# define MAP_START_POSITION_ERROR "Error : Player start position error. \
Only one player start position is allowed in the map.\n"

typedef struct s_parse_info
{
	int		fd;
	int		valid_no_texture_file_path_count;
	int		valid_so_texture_file_path_count;
	int		valid_we_texture_file_path_count;
	int		valid_ea_texture_file_path_count;
	int		vaild_floor_rgb_count;
	int		vaild_ceiling_rgb_count;
	int		start_position_count;
	int		line_type;
	char	*line;
}	t_parse_info;

typedef struct s_map_node
{
	char				*str;
	struct s_map_node	*next;
}	t_map_node;

typedef struct s_map_list
{
	int			height;
	int			width;
	t_map_node	*head_node;
}	t_map_list;

typedef struct s_game_info
{
	char	*no_texture_path;
	char	*so_texture_path;
	char	*ea_texture_path;
	char	*we_texture_path;
	int		floor_rgb;
	int		ceiling_rgb;
	int		direction[2];
	int		height;
	int		width;
	char	**map;
}	t_game_info;

enum	e_DIRECTION
{
	NO = 0,
	SO,
	WE,
	EA,
};

enum	e_LINE_TYPE
{
	CHECK_PATH = 0,
	CHECK_RGB,
	ONLY_SPACE,
	CHECK_MAP
};

//main
void		parse_data(t_game_info *game_info, \
							t_parse_info *parse_info, t_map_list *map_list);
//split
void		*finalize(char	**str_arr);
size_t		ft_word_cnt(const char *str, char charset);
size_t		get_word_len(const char *str, char charset);
char		*put_word(const char *str, char charset);
char		**ft_split(const char *str, char charset);
//str_utils
int			ft_strlen(char *str);
int			ft_strncmp(const char *s1, const char *s2, int n);
int			ft_strcmp(char *s1, char *s2);
char		*ft_strchr(const char *s, int c);
char		*ft_strdup(char *src);
// initialize
void		*ft_memset(void *b, int c, size_t len);
void		initialize(t_game_info *game_info, \
						t_parse_info *parse_info, t_map_list *map_list);
// list_utils
t_map_node	*ft_lstlast(t_map_node *head);
void		ft_lstadd_back(t_map_node *head, t_map_node *new);
void		free_list(t_map_node *head);
// file_utils
void		check_file(char *file_name, t_game_info *game_info, \
						t_parse_info *parse_info, t_map_list *map_list);
int			is_valid_file_extension(char *file_name);
int			is_valid_xpm_file(char *file_name);
// parse_utils

int			check_line_type(char *line, t_parse_info *parse_info);
int			update_texture_info(char **file, t_game_info *game_info, \
								t_parse_info *parse_info, t_map_list *map_list);
void		is_valid_texture_file_path(char *line, t_game_info *game_info, \
								t_parse_info *parse_info, t_map_list *map_list);
void		check_floor_and_ceiling_rgb(char *line, t_game_info *game_info, \
								t_parse_info *parse_info, t_map_list *map_list);
void		store_map_data_in_list(char *line, t_game_info *game_info, \
								t_parse_info *parse_info, t_map_list *map_list);
// rgb_utils
int			ft_isdigit(int c);
int			ft_atoi(const char *str);
int			get_rgb_color(char *rgb_value, t_game_info *game_info, \
					t_parse_info *parse_info, t_map_list *map_list);
// check_map
void		check_map_validity(char *line, t_game_info *game_info, \
								t_parse_info *parse_info, t_map_list *map_list);
int			is_valid_map_characters(char **line);
int			is_only_one_start_position(char *line, t_parse_info *parse_info);
void		is_map_surround_by_wall(t_game_info *game_info, \
								t_parse_info *parse_info, t_map_list *map_list);
// check_map_utils
int			is_line_empty(char *line);
int			check_pre_validation_complete(t_parse_info *parse_info);
void		allocate_map(t_game_info *game_info, \
								t_parse_info *parse_info, t_map_list *map_list);
void		convert_list_to_map_array(t_game_info *game_info, \
								t_parse_info *parse_info, t_map_list *map_list);
int			get_line_len(char *line);
// finalize
void	free_2d_array(char **array);
void	exit_error_control(char *error_msg, t_game_info *game_info, \
							t_parse_info *parse_info, t_map_list *map_list);
#endif