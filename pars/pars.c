/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehjoo <jaehjoo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 19:10:48 by jun               #+#    #+#             */
/*   Updated: 2023/06/05 16:27:58 by jaehjoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parse_data(t_game_info *game_info, \
							t_parse_info *parse_info, t_map_list *map_list)
{
	parse_info->line = get_next_line(parse_info->fd);
	while (parse_info->line != NULL)
	{
		if (parse_info->line[ft_strlen(parse_info->line) - 1] == '\n')
			parse_info->line[ft_strlen(parse_info->line) - 1] = '\0';
		parse_info->line_type = check_line_type(parse_info->line);
		if (parse_info->line_type == CHECK_PATH)
			is_valid_texture_file_path(parse_info->line, game_info, \
														parse_info, map_list);
		else if (parse_info->line_type == CHECK_RGB)
			check_floor_and_ceiling_rgb(parse_info->line, game_info, \
														parse_info, map_list);
		else if (parse_info->line_type == ONLY_SPACE && game_info->height > 0)
			exit_error_control(MAP_SEPARATED_ERROR, game_info, \
														parse_info, map_list);
		else if (parse_info->line_type == CHECK_MAP)
			store_map_data_in_list(parse_info->line, game_info, \
														parse_info, map_list);
		free(parse_info->line);
		parse_info->line = get_next_line(parse_info->fd);
	}
}

void	leak(void)
{
	system("leaks cub3d");
}
