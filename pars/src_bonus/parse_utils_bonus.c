/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehjoo <jaehjoo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 20:36:38 by hyeoan            #+#    #+#             */
/*   Updated: 2023/06/07 16:48:46 by jaehjoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	update_texture_info(char **file, t_game_info *game_info, \
								t_parse_info *parse_info)
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

int	is_line_empty(char *line)
{
	while (*line == ' ')
		line++;
	if (*line == '\0')
		return (1);
	return (0);
}
