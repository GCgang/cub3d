/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jun <jun@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 21:11:31 by hyeoan            #+#    #+#             */
/*   Updated: 2023/06/06 21:03:18 by jun              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	convert_list_to_map_array(t_game_info *game_info, \
								t_parse_info *parse_info, t_map_list *map_list)
{
	int			i;
	int			j;
	t_map_node	*tmp;

	if (check_pre_validation_complete(parse_info) == -1)
		exit_error_control(PRE_VALIDATION_ERROR, \
											game_info, parse_info, map_list);
	allocate_map(game_info, parse_info, map_list);
	i = 0;
	tmp = map_list->head_node->next;
	while (tmp != NULL)
	{
		j = 0;
		while (j < game_info->width)
		{
			if (j < ft_strlen(tmp->str))
				game_info->map[i][j] = tmp->str[j];
			else
				game_info->map[i][j] = '.';
			j++;
		}
		i++;
		tmp = tmp->next;
	}
	free_list(map_list->head_node);
}

void	allocate_map(t_game_info *game_info, \
								t_parse_info *parse_info, t_map_list *map_list)
{
	int		i;

	i = 0;
	game_info->map = (char **)malloc(sizeof(char *) * (game_info->height + 1));
	if (game_info->map == NULL)
		exit_error_control \
		("Error : malloc returned NULL.(convert_list_to_map_array)\n", \
											game_info, parse_info, map_list);
	game_info->map[game_info->height] = 0;
	while (i < game_info->height)
	{
		game_info->map[i] = (char *)malloc(sizeof(char) * (game_info->width + 1));
		if (game_info->map[i] == NULL)
			exit_error_control \
			("Error : malloc returned NULL(convert_list_to_map_array)\n", \
											game_info, parse_info, map_list);
		game_info->map[i][game_info->width] = '\0';
		i++;
	}
}

int	get_line_len(char *line)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (line[i] != '\0')
	{
		if (line[i] != '.')
			len++;
		i++;
	}
	return (len);
}

int	is_column_valid(t_game_info *game_info, int y, int x)
{
	int	i;

	if (game_info->map[y][x] != '1' && game_info->map[y][x] != '.')
	{
		i = y;
		while (0 < i)
		{
			if (game_info->map[i][x] == '1')
				break ;
			else if (game_info->map[i][x] == '.')
				return (0);
			i--;
		}
		while (y < game_info->height)
		{
			if (game_info->map[y][x] == '1')
				return (1);
			else if (game_info->map[y][x] == '.')
				return (0);
			y++;
		}
	}
	return (1);
}

int	is_map_edge_wall(t_game_info *game_info, int y, int x, int line_len)
{
	if (y == 0 || y == game_info->height - 1 || \
		x == 0 || x == line_len - 1)
	{
		if (game_info->map[y][x] != '1' && game_info->map[y][x] != '.')
			return (0);
	}
	return (1);
}
