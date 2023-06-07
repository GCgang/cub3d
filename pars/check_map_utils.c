/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeoan <hyeoan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 21:11:31 by hyeoan            #+#    #+#             */
/*   Updated: 2023/06/07 16:31:38 by hyeoan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	convert_list_to_map_array(t_game_info *game_info, \
								t_parse_info *parse_info, t_map_list *map_list)
{
	int			i;
	int			j;
	t_map_node	*tmp;

	if (is_only_one_start_position(parse_info) == 0)
		exit_error_control(MAP_START_POSITION_ERROR, game_info, \
													parse_info, map_list);
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
		game_info->map[i] = (char *)malloc(sizeof(char) * \
													(game_info->width + 1));
		if (game_info->map[i] == NULL)
			exit_error_control \
			("Error : malloc returned NULL(convert_list_to_map_array)\n", \
											game_info, parse_info, map_list);
		game_info->map[i][game_info->width] = '\0';
		i++;
	}
}
