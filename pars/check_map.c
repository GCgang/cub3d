/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeoan <hyeoan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 12:14:44 by hyeoan            #+#    #+#             */
/*   Updated: 2023/06/07 16:12:49 by hyeoan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_map_validity(char *line, t_game_info *game_info, \
								t_parse_info *parse_info, t_map_list *map_list)
{
	if (is_valid_map_characters(&line, parse_info) == 0)
		exit_error_control(MAP_VALUE_ERROR, game_info, parse_info, map_list);
}

int	is_valid_map_characters(char **line, t_parse_info *parse_info)
{
	int	i;

	i = 0;
	while (line[0][i] != '\0')
	{
		if (line[0][i] != '0' && line[0][i] != '1' \
			&& line[0][i] != 'N' && line[0][i] != 'S' \
			&& line[0][i] != 'W' && line[0][i] != 'E' \
			&& line[0][i] != ' ')
		{
			return (0);
		}
		else if (line[0][i] == 'N')
			parse_info->start_position_count++;
		else if (line[0][i] == 'S')
			parse_info->start_position_count++;
		else if (line[0][i] == 'W')
			parse_info->start_position_count++;
		else if (line[0][i] == 'E')
			parse_info->start_position_count++;
		i++;
	}
	return (1);
}

int	is_only_one_start_position(t_parse_info *parse_info)
{
	if (parse_info->start_position_count != 1)
		return (0);
	return (1);
}

int	check_pre_validation_complete(t_parse_info *parse_info)
{
	if (parse_info->valid_no_texture_file_path_count == 1 \
		&& parse_info->valid_so_texture_file_path_count == 1 \
		&& parse_info->valid_we_texture_file_path_count == 1 \
		&& parse_info->valid_ea_texture_file_path_count == 1 \
		&& parse_info->vaild_floor_rgb_count == 1 \
		&& parse_info->vaild_ceiling_rgb_count == 1)
	{
		return (0);
	}
	return (-1);
}

void	is_map_surround_by_wall(t_game_info *game_info, \
								t_parse_info *parse_info, t_map_list *map_list)
{
	int	y;
	int	x;

	y = 0;
	while (y < game_info->height)
	{
		x = 0;
		while (x < game_info->width)
		{
			if (is_map_edge_wall(game_info, y, x) == 0)
				exit_error_control(MAP_CONFIGURATION_ERROR, game_info, \
													parse_info, map_list);
			else
			{
				if (is_row_column_valid(game_info, y, x) == 0)
					exit_error_control(MAP_CONFIGURATION_ERROR, game_info, \
													parse_info, map_list);
			}
			x++;
		}
		y++;
	}
}
