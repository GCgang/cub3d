/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeoan <hyeoan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 20:36:38 by hyeoan            #+#    #+#             */
/*   Updated: 2023/06/05 12:10:35 by hyeoan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_line_type(char *line, t_parse_info *parse_info)
{
	int	i;

	i = 0;
	if (is_line_empty(line) == 1)
		return (ONLY_SPACE);
	while (*line == ' ')
		line++;
	if (ft_strncmp(line, "NO ", 3) == 0 \
		|| ft_strncmp(line, "SO ", 3) == 0 \
		|| ft_strncmp(line, "WE ", 3) == 0 \
		|| ft_strncmp(line, "EA ", 3) == 0)
	{
		return (CHECK_PATH);
	}
	else if (ft_strncmp(line, "F ", 2) == 0 \
		|| ft_strncmp(line, "C ", 2) == 0)
	{
		return (CHECK_RGB);
	}
	return (CHECK_MAP);
}

void	is_valid_texture_file_path(char *line, t_game_info *game_info, \
								t_parse_info *parse_info, t_map_list *map_list)
{
	char	**texture_file;

	texture_file = ft_split(line, ' ');
	if (texture_file == NULL)
		exit_error_control \
		("Error : ft_split() returned NULL.(is_valid_texture_file_path)\n", \
		game_info, parse_info, map_list);
	if (texture_file[0] == NULL || texture_file[1] == NULL \
		|| texture_file[2] != NULL)
	{
		free_2d_array(texture_file);
		exit_error_control(TEXTURE_FILE_PATH_ERROR, \
										game_info, parse_info, map_list);
	}
	if (update_texture_info(texture_file, game_info, \
											parse_info, map_list) == -1)
	{
		free_2d_array(texture_file);
		exit_error_control(TEXTURE_FILE_PATH_ERROR, \
										game_info, parse_info, map_list);
	}
	free_2d_array(texture_file);
}

int	update_texture_info(char **file, t_game_info *game_info, \
								t_parse_info *parse_info, t_map_list *map_list)
{
	if (ft_strcmp("NO", file[0]) == 0 && is_valid_xpm_file(file[1]) == 0)
	{
		parse_info->valid_no_texture_file_path_count++;
		game_info->no_texture_path = ft_strdup(file[1]);
	}
	else if (ft_strcmp("SO", file[0]) == 0 && is_valid_xpm_file(file[1]) == 0)
	{
		parse_info->valid_so_texture_file_path_count++;
		game_info->so_texture_path = ft_strdup(file[1]);
	}
	else if (ft_strcmp("WE", file[0]) == 0 && is_valid_xpm_file(file[1]) == 0)
	{
		parse_info->valid_we_texture_file_path_count++;
		game_info->we_texture_path = ft_strdup(file[1]);
	}
	else if (ft_strcmp("EA", file[0]) == 0 && is_valid_xpm_file(file[1]) == 0)
	{
		parse_info->valid_ea_texture_file_path_count++;
		game_info->ea_texture_path = ft_strdup(file[1]);
	}
	else
		return (-1);
	return (1);
}

void	check_floor_and_ceiling_rgb(char *line, t_game_info *game_info, \
								t_parse_info *parse_info, t_map_list *map_list)
{
	char	**rgb_info;

	rgb_info = ft_split(line, ' ');
	if (rgb_info == NULL)
		exit_error_control \
		("Error : ft_split() returned NULL.(check_floor_and_ceiling_rgb)\n", \
		game_info, parse_info, map_list);
	if (rgb_info[0] == NULL || rgb_info[1] == NULL || rgb_info[2] != NULL)
	{
		free_2d_array(rgb_info);
		exit_error_control(RGB_ERROR, game_info, parse_info, map_list);
	}
	if (ft_strcmp("F", rgb_info[0]) == 0)
	{
		game_info->floor_rgb = get_rgb_color(rgb_info[1], game_info, \
											parse_info, map_list);
		parse_info->vaild_floor_rgb_count++;
	}
	if (ft_strcmp("C", rgb_info[0]) == 0)
	{
		game_info->ceiling_rgb = get_rgb_color(rgb_info[1], game_info, \
											parse_info, map_list);
		parse_info->vaild_ceiling_rgb_count++;
	}
	free_2d_array(rgb_info);
}

void	store_map_data_in_list(char *line, t_game_info *game_info, \
								t_parse_info *parse_info, t_map_list *map_list)
{
	t_map_node	*map_node;

	if (check_pre_validation_complete(parse_info) == -1)
		exit_error_control(PRE_VALIDATION_ERROR, \
											game_info, parse_info, map_list);
	check_map_validity(line, game_info, parse_info, map_list);
	map_node = (t_map_node *)malloc(sizeof(t_map_node));
	if (map_node == NULL)
		exit_error_control \
		("Error : malloc returned NULL.(store_map_data_in_list)\n", \
											game_info, parse_info, map_list);
	map_node->str = ft_strdup(line);
	if (map_node->str == NULL)
	{
		free(map_node);
		exit_error_control \
		("Error : ft_strdup returned NULL.(store_map_data_in_list)\n", \
											game_info, parse_info, map_list);
	}
	map_node->next = NULL;
	ft_lstadd_back(map_list->head_node, map_node);
	game_info->height++;
	if (game_info->width <= ft_strlen(line))
		game_info->width = ft_strlen(line);
}
