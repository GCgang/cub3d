/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehjoo <jaehjoo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 12:00:12 by jaehjoo           #+#    #+#             */
/*   Updated: 2023/06/07 17:30:56 by jaehjoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

static void	free_map(int **map, int y)
{
	int	idx;

	idx = -1;
	while (++idx < y)
		free(map[idx]);
	free(map);
}

void	rotate_key(t_total *app, double rot, int keycode)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = app->ray.dir.x;
	old_plane_x = app->ray.plane.x;
	if (keycode == LEFT_KEY)
	{
		app->ray.dir.x = app->ray.dir.x * cos(-rot)
			- app->ray.dir.y * sin(-rot);
		app->ray.dir.y = old_dir_x * sin(-rot) + app->ray.dir.y * cos(-rot);
		app->ray.plane.x = app->ray.plane.x * cos(-rot)
			- app->ray.plane.y * sin(-rot);
		app->ray.plane.y = old_plane_x * sin(-rot)
			+ app->ray.plane.y * cos(-rot);
	}
	else
	{
		app->ray.dir.x = app->ray.dir.x * cos(rot) - app->ray.dir.y * sin(rot);
		app->ray.dir.y = old_dir_x * sin(rot) + app->ray.dir.y * cos(rot);
		app->ray.plane.x = app->ray.plane.x * cos(rot)
			- app->ray.plane.y * sin(rot);
		app->ray.plane.y = old_plane_x * sin(rot) + app->ray.plane.y * cos(rot);
	}
}

int	mlx_exit(t_total *app)
{
	mlx_destroy_image(app->mlx.mlx, app->mlx.canvas.img);
	mlx_destroy_image(app->mlx.mlx, app->mlx.img[0].img);
	mlx_destroy_image(app->mlx.mlx, app->mlx.img[1].img);
	mlx_destroy_image(app->mlx.mlx, app->mlx.img[2].img);
	mlx_destroy_image(app->mlx.mlx, app->mlx.img[3].img);
	mlx_destroy_window(app->mlx.mlx, app->mlx.win);
	free_map(app->map, app->map_scale.y);
	exit(0);
	return (0);
}

void	chk_mlx_hook(t_total *app)
{
	mlx_hook(app->mlx.win, KEYPRESS, 0, &key_hook, app);
	mlx_hook(app->mlx.win, MOTIONNOTIFY, 0, &mouse_hook, app);
	mlx_hook(app->mlx.win, DESTROYNOTIFY, 0, &mlx_exit, app);
}
