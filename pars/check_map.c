/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeoan <hyeoan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 12:14:44 by hyeoan            #+#    #+#             */
/*   Updated: 2023/06/05 12:16:50 by hyeoan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_map_validity(char *line, t_game_info *game_info, \
								t_parse_info *parse_info, t_map_list *map_list)
{
	if (is_valid_map_characters(&line) == 0)
		exit_error_control(MAP_VALUE_ERROR, game_info, parse_info, map_list);
	if (is_only_one_start_position(line, parse_info) == 0)
		exit_error_control(MAP_START_POSITION_ERROR, game_info, \
													parse_info, map_list);
}

int	is_valid_map_characters(char **line)
{
	int	i;

	i = 0;
	while (line[0][i] != '\0')
	{
		if (line[0][i] == ' ')
		{
			line[0][i] = '1';
		}
		else if (line[0][i] != '0' && line[0][i] != '1' \
			&& line[0][i] != 'N' && line[0][i] != 'S' \
			&& line[0][i] != 'W' && line[0][i] != 'E')
		{
			return (0);
		}
		i++;
	}
	return (1);
}

int	is_only_one_start_position(char *line, t_parse_info *parse_info)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == 'N')
			parse_info->start_position_count++;
		else if (line[i] == 'S')
			parse_info->start_position_count++;
		else if (line[i] == 'W')
			parse_info->start_position_count++;
		else if (line[i] == 'E')
			parse_info->start_position_count++;
		i++;
	}
	if (parse_info->start_position_count > 1)
		return (0);
	return (1);
}

void	is_map_surround_by_wall(t_game_info *game_info, \
								t_parse_info *parse_info, t_map_list *map_list)
{
	int	y;
	int	x;
	int	line_len;

	y = 0;
	while (y < game_info->height)
	{
		line_len = get_line_len(game_info->map[y]);
		x = 0;
		while (x < game_info->width)
		{
			if (y == 0 || y == game_info->height - 1 || \
					x == 0 || x == line_len - 1)
			{
				if (game_info->map[y][x] != '1' && game_info->map[y][x] != '.')
					exit_error_control(MAP_CONFIGURATION_ERROR, game_info, \
					parse_info, map_list);
			}
			x++;
		}
		y++;
	}
}
