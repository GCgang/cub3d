/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jun <jun@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 21:07:51 by hyeoan            #+#    #+#             */
/*   Updated: 2023/06/07 23:02:04 by jun              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_isdigit(int c)
{
	if ('0' <= c && c <= '9')
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int	result;

	result = 0;
	while ((9 <= *str && *str <= 13) || *str == 32)
		str++;
	while (*str != '\0')
	{
		if (ft_isdigit(*str) == 0)
			return (-1);
		result *= 10;
		result += (*str - '0');
		str++;
	}
	return (result);
}

int	get_rgb_color(char *rgb_value, t_game_info *game_info, \
					t_parse_info *parse_info, t_map_list *map_list)
{
	int		r;
	int		g;
	int		b;
	char	**rgb;

	rgb = ft_split(rgb_value, ',');
	if (rgb == NULL)
		exit_error_control("Error\nft_split() returned NULL.(get_rgb_color)\n", \
											game_info, parse_info, map_list);
	if (rgb[0] == NULL || rgb[1] == NULL || rgb[2] == NULL || rgb[3] != NULL)
	{
		free_2d_array(rgb);
		exit_error_control(RGB_ERROR, game_info, parse_info, map_list);
	}
	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	if (r < 0 || 255 < r || g < 0 || 255 < g || b < 0 || 255 < b)
	{
		free_2d_array(rgb);
		exit_error_control(RGB_ERROR, game_info, parse_info, map_list);
	}
	free_2d_array(rgb);
	return (((r << 16) | (g << 8) | b));
}
