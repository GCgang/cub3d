/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehjoo <jaehjoo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 13:08:33 by jaehjoo           #+#    #+#             */
/*   Updated: 2023/06/08 12:36:31 by jaehjoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

int	**map_set(char **trans_map, int **map, int width, int height)
{
	int	y;
	int	x;

	y = -1;
	while (++y < height)
	{
		x = -1;
		while (++x < width)
		{
			if (trans_map[y][x] == '1')
				map[y][x] = 1;
			else if (trans_map[y][x] == '0')
				map[y][x] = 0;
			else
				map[y][x] = (int)trans_map[y][x];
		}
	}
	map_free(trans_map, NULL, height + 1, 0);
	return (map);
}

int	map_free(char **trans_map, int **map, int height, int map_h)
{
	int	y;

	if (trans_map)
	{
		y = -1;
		while (++y < height)
			free(trans_map[y]);
		free(trans_map);
	}
	if (map)
	{
		y = -1;
		while (++y < map_h)
			free(map[y]);
		free(map);
	}
	return (0);
}

int	image_free(t_game_info *game_info, t_total *app, int flag)
{
	int	idx;

	free(game_info->no_texture_path);
	free(game_info->so_texture_path);
	free(game_info->we_texture_path);
	free(game_info->ea_texture_path);
	if (flag == 1)
		return (0);
	else
	{
		mlx_destroy_image(app->mlx.mlx, app->mlx.canvas.img);
		idx = 0;
		while (idx < 4)
		{
			if (app->mlx.img[idx].img)
				mlx_destroy_image(app->mlx.mlx, app->mlx.img[idx].img);
			else
				break ;
			idx++;
		}
		mlx_destroy_window(app->mlx.mlx, app->mlx.win);
		map_free(NULL, app->map, 0, (int)app->map_scale.y);
		return (print_error("Don't validated image file\n"));
	}
}
