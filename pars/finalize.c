/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finalize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeoan <hyeoan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 12:20:41 by hyeoan            #+#    #+#             */
/*   Updated: 2023/06/05 12:21:15 by hyeoan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_2d_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
}

void	exit_error_control(char *error_msg, t_game_info *game_info, \
							t_parse_info *parse_info, t_map_list *map_list)
{
	if (ft_strcmp(error_msg, ARGUMENT_ERROR) != 0)
	{
		if (game_info->no_texture_path != NULL)
			free(game_info->no_texture_path);
		if (game_info->so_texture_path != NULL)
			free(game_info->so_texture_path);
		if (game_info->ea_texture_path != NULL)
			free(game_info->ea_texture_path);
		if (game_info->we_texture_path != NULL)
			free(game_info->we_texture_path);
		if (game_info->map != NULL)
			free_2d_array(game_info->map);
		if (parse_info->fd > 2)
			close(parse_info->fd);
		if (parse_info->line != NULL)
			free(parse_info->line);
		if (map_list->head_node != NULL)
			if (map_list->head_node->next != NULL)
				free_list(map_list->head_node);
		if (map_list->head_node != NULL)
			free(map_list->head_node);
	}
	write(2, error_msg, ft_strlen(error_msg));
	exit(1);
}
