/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_surround_check_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeoan <hyeoan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 16:30:21 by hyeoan            #+#    #+#             */
/*   Updated: 2023/06/07 16:31:45 by hyeoan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_map_edge_wall(t_game_info *game_info, int y, int x)
{
	if (y == 0 || y == game_info->height - 1)
	{
		if (game_info->map[y][x] != '1' && \
			game_info->map[y][x] != '.' && \
			game_info->map[y][x] != ' ')
			return (0);
	}
	else
	{
		if (is_valid_line_end_point(game_info, y) == 0)
			return (0);
	}
	return (1);
}

int	is_row_column_valid(t_game_info *game_info, int y, int x)
{
	int	i;

	if (game_info->map[y][x] != '1' && game_info->map[y][x] != '.' \
		&& game_info->map[y][x] != ' ')
	{
		if (game_info->map[y][x - 1] == ' ' || game_info->map[y][x + 1] == ' ')
			return (0);
		i = y;
		while (0 < i--)
		{
			if (game_info->map[i][x] == '1')
				break ;
			else if (game_info->map[i][x] == '.' || game_info->map[i][x] == ' ')
				return (0);
		}
		while (y < game_info->height)
		{
			if (game_info->map[y][x] == '1')
				return (1);
			else if (game_info->map[y][x] == '.' || game_info->map[y][x] == ' ')
				return (0);
			y++;
		}
	}
	return (1);
}

int	is_valid_line_end_point(t_game_info *game_info, int y)
{
	char	**line;
	int		i;

	line = ft_split(game_info->map[y], ' ');
	if (line == NULL)
		return (0);
	i = 0;
	while (line[i] != NULL)
	{
		if (line[i][0] == '.')
			break ;
		if (is_valid_line_start(line[i][0]) == 0)
		{
			free_2d_array(line);
			return (0);
		}
		if (is_valid_line_end(line[i]) == 0)
		{
			free_2d_array(line);
			return (0);
		}
		i++;
	}
	return (1);
}

int	is_valid_line_start(char line_start)
{
	if (line_start != '1')
		return (0);
	return (1);
}

int	is_valid_line_end(char *line)
{
	int	end;

	end = 0;
	while (line[end] != '\0' && line[end] != '.')
		end++;
	if (line[end - 1] != '1')
		return (0);
	return (1);
}
