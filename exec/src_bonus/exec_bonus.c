/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehjoo <jaehjoo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 11:59:47 by jaehjoo           #+#    #+#             */
/*   Updated: 2023/06/07 16:40:44 by jaehjoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec_bonus.h"

static int	**cpy_map(char **trans_map, int width, int height)
{
	int	**map;
	int	y;

	map = (int **)malloc(height * sizeof(int *));
	if (!map)
	{
		map_free(trans_map, NULL, height + 1, 0);
		return (NULL);
	}
	y = -1;
	while (++y < height)
	{
		map[y] = (int *)malloc(width * sizeof(int));
		if (!map[y])
		{
			map_free(trans_map, map, height + 1, y);
			return (NULL);
		}
	}
	return (map_set(trans_map, map, width, height));
}

static int	set_xpm_image(t_total *app, int num, char *path)
{
	app->mlx.img[num].img = mlx_xpm_file_to_image(app->mlx.mlx,
			path, &app->wall.texture, &app->wall.texture);
	if (!app->mlx.img[num].img)
		return (1);
	app->mlx.img[num].img_addr = mlx_get_data_addr(app->mlx.img[num].img,
			&app->mlx.img[num].bpp, &app->mlx.img[num].size_len,
			&app->mlx.img[num].endian);
	return (0);
}

static int	set_image(t_total *app, t_game_info *game_info)
{
	app->mlx.canvas.img = mlx_new_image(app->mlx.mlx, app->win.x, app->win.y);
	app->mlx.canvas.img_addr = mlx_get_data_addr(app->mlx.canvas.img,
			&app->mlx.canvas.bpp, &app->mlx.canvas.size_len,
			&app->mlx.canvas.endian);
	if (set_xpm_image(app, 0, game_info->ea_texture_path)
		|| set_xpm_image(app, 1, game_info->we_texture_path)
		|| set_xpm_image(app, 2, game_info->so_texture_path)
		|| set_xpm_image(app, 3, game_info->no_texture_path))
		return (image_free(game_info, app, 0));
	return (image_free(game_info, app, 1));
}	

static int	exec_init(t_total *app, t_game_info *game_info)
{
	app->map = cpy_map(game_info->map, game_info->width, game_info->height);
	if (!app->map)
		return (1);
	set_player(app->map, game_info->width, game_info->height, &app->ray.player);
	set_dir(&app->ray, app->map[(int)app->ray.player.y]
	[(int)app->ray.player.x]);
	app->map[(int)app->ray.player.y][(int)app->ray.player.x] = 0;
	app->wall.texture = 64;
	app->move_speed = 0.15;
	app->rotate_speed = 0.05;
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
	return (set_image(app, game_info));
}

int	exec(t_game_info *game_info)
{
	t_total	app;

	ft_bzero(&app, sizeof(t_total));
	if (exec_init(&app, game_info))
		return (1);
	chk_mlx_hook(&app);
	mlx_mouse_hide();
	main_loop(&app);
	mlx_loop(app.mlx.mlx);
	return (0);
}
