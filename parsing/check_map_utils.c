/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeoan <hyeoan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 21:11:31 by hyeoan            #+#    #+#             */
/*   Updated: 2023/06/05 14:24:59 by hyeoan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_line_empty(char *line)
{
	while (*line == ' ')
		line++;
	if (*line == '\0')
		return (1);
	return (0);
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

void	allocate_map(t_game_info *game_info, \
								t_parse_info *parse_info, t_map_list *map_list)
{
	int		i;

	i = 0;
	game_info->map = (char **)malloc(sizeof(char *) * game_info->height + 1);
	if (game_info->map == NULL)
		exit_error_control \
		("Error : malloc returned NULL.(convert_list_to_map_array)\n", \
											game_info, parse_info, map_list);
	game_info->map[game_info->height] = NULL;
	while (i < game_info->height)
	{
		game_info->map[i] = (char *)malloc(sizeof(char) * game_info->width + 1);
		if (game_info->map[i] == NULL)
			exit_error_control \
			("Error : malloc returned NULL(convert_list_to_map_array)\n", \
											game_info, parse_info, map_list);
		game_info->map[i][game_info->width] = '\0';
		i++;
	}
}

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
