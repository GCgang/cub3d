/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehjoo <jaehjoo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 20:26:27 by hyeoan            #+#    #+#             */
/*   Updated: 2023/06/08 12:54:54 by jaehjoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	check_file(char *file_name, t_game_info *game_info, \
						t_parse_info *parse_info, t_map_list *map_list)
{
	if (is_valid_file_extension(file_name) == -1)
		exit_error_control(FILE_EXTENSION_ERROR, game_info, \
												parse_info, map_list);
	parse_info->fd = open(file_name, O_RDONLY);
	if (parse_info->fd == -1)
		exit_error_control \
		("Error\nFailed to open the file in read mode.(check_file)\n", \
										game_info, parse_info, map_list);
}

int	is_valid_file_extension(char *file_name)
{
	int	file_len;

	file_len = ft_strlen(file_name);
	if (ft_strncmp(file_name + file_len - 4, ".cub", 4) != 0)
		return (-1);
	return (0);
}

int	is_valid_xpm_file(char *file_name)
{
	int	file_len;
	int	fd;

	file_len = ft_strlen(file_name);
	if (ft_strncmp(file_name + file_len - 4, ".xpm", 4) != 0)
		return (-1);
	fd = open(file_name, O_RDONLY);
	if (fd == -1)
	{
		close(fd);
		return (-1);
	}
	return (0);
}
