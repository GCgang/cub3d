/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hook_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehjoo <jaehjoo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 12:00:56 by jaehjoo           #+#    #+#             */
/*   Updated: 2023/06/07 16:41:13 by jaehjoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec_bonus.h"

static void	rotate_sight(t_total *app, double rot, int x)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = app->ray.dir.x;
	old_plane_x = app->ray.plane.x;
	if (0 < x && x < app->mlx.mouse)
	{
		app->ray.dir.x = app->ray.dir.x * cos(-rot)
			- app->ray.dir.y * sin(-rot);
		app->ray.dir.y = old_dir_x * sin(-rot) + app->ray.dir.y * cos(-rot);
		app->ray.plane.x = app->ray.plane.x * cos(-rot)
			- app->ray.plane.y * sin(-rot);
		app->ray.plane.y = old_plane_x * sin(-rot)
			+ app->ray.plane.y * cos(-rot);
	}
	else if (app->mlx.mouse < x && x < app->win.x)
	{
		app->ray.dir.x = app->ray.dir.x * cos(rot) - app->ray.dir.y * sin(rot);
		app->ray.dir.y = old_dir_x * sin(rot) + app->ray.dir.y * cos(rot);
		app->ray.plane.x = app->ray.plane.x * cos(rot)
			- app->ray.plane.y * sin(rot);
		app->ray.plane.y = old_plane_x * sin(rot) + app->ray.plane.y * cos(rot);
	}
}

int	mouse_hook(int x, int y, t_total *app)
{
	double	rot;

	rot = app->rotate_speed;
	if (0 < y && y < app->win.y && 0 < x && x < app->win.x)
		rotate_sight(app, rot, x);
	mlx_mouse_move(app->mlx.win, app->win.x / 2, app->win.y / 2);
	app->mlx.mouse = app->win.x / 2;
	main_loop(app);
	return (0);
}
