/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehjoo <jaehjoo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 11:59:47 by jaehjoo           #+#    #+#             */
/*   Updated: 2023/06/05 18:35:14 by jaehjoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

static int	**cpy_map(char **trans_map, int width, int height)
{
	int	x;
	int	y;
	int	**map;

	x = -1;
	y = -1;
	map = (int **)malloc(height * sizeof(int *));
	while (++y < height)
		map[y] = (int *)malloc(width * sizeof(int));
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
	map_free(trans_map, height + 1);
	return (map);
}

static void	set_xpm_image(t_total *app, int num, char *path)
{
	app->mlx.img[num].img = mlx_xpm_file_to_image(app->mlx.mlx,
			path, &app->wall.texture, &app->wall.texture);
	app->mlx.img[num].img_addr = mlx_get_data_addr(app->mlx.img[num].img,
			&app->mlx.img[num].bpp, &app->mlx.img[num].size_len,
			&app->mlx.img[num].endian);
}

static void	set_image(t_total *app, t_game_info *game_info)
{
	app->mlx.canvas.img = mlx_new_image(app->mlx.mlx, app->win.x, app->win.y);
	app->mlx.canvas.img_addr = mlx_get_data_addr(app->mlx.canvas.img,
			&app->mlx.canvas.bpp, &app->mlx.canvas.size_len,
			&app->mlx.canvas.endian);
	set_xpm_image(app, 0, game_info->ea_texture_path);
	set_xpm_image(app, 1, game_info->we_texture_path);
	set_xpm_image(app, 2, game_info->so_texture_path);
	set_xpm_image(app, 3, game_info->no_texture_path);
	free(game_info->ea_texture_path);
	free(game_info->we_texture_path);
	free(game_info->so_texture_path);
	free(game_info->no_texture_path);
}	

static void	exec_init(t_total *app, t_game_info *game_info)
{
	app->map = cpy_map(game_info->map, game_info->width, game_info->height);
	set_player(app->map, game_info->width, game_info->height, &app->ray.player);
	set_dir(&app->ray, app->map[(int)app->ray.player.y]
	[(int)app->ray.player.x]);
	app->map[(int)app->ray.player.y][(int)app->ray.player.x] = 0;
	app->wall.texture = 64;
	app->move_speed = 0.2;
	app->rotate_speed = 0.1;
	app->bg_color[0] = game_info->floor_rgb;
	app->bg_color[1] = game_info->ceiling_rgb;
	app->win.x = 1920;
	app->win.y = 1080;
	app->mlx.mouse = app->win.x / 2;
	app->mlx.mlx = mlx_init();
	app->mlx.win = mlx_new_window(app->mlx.mlx, app->win.x,
			app->win.y, "cub3D");
	app->map_scale.x = game_info->width;
	app->map_scale.y = game_info->height;
	set_image(app, game_info);
}

int	exec(t_game_info *game_info)
{
	t_total	app;

	ft_bzero(&app, sizeof(t_total));
	exec_init(&app, game_info);
	chk_mlx_hook(&app);
	main_loop(&app);
	mlx_loop(app.mlx.mlx);
	return (0);
}
