/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehjoo <jaehjoo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 12:00:20 by jaehjoo           #+#    #+#             */
/*   Updated: 2023/06/07 16:40:57 by jaehjoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec_bonus.h"

static void	move_akey(t_total *app, double move)
{
	if (!app->map[(int)(app->ray.player.y)][(int)(app->ray.player.x
			- app->ray.plane.x * 0.5)])
		app->ray.player.x -= app->ray.plane.x * move;
	else
		app->ray.player.x += app->ray.plane.x * move;
	if (!app->map[(int)(app->ray.player.y
			- app->ray.plane.y * 0.5)][(int)(app->ray.player.x)])
		app->ray.player.y -= app->ray.plane.y * move;
	else
		app->ray.player.y += app->ray.plane.y * move;
}

static void	move_dkey(t_total *app, double move)
{
	if (!app->map[(int)(app->ray.player.y)][(int)(app->ray.player.x
			+ app->ray.plane.x * 0.5)])
		app->ray.player.x += app->ray.plane.x * move;
	else
		app->ray.player.x -= app->ray.plane.x * move;
	if (!app->map[(int)(app->ray.player.y
			+ app->ray.plane.y * 0.5)][(int)(app->ray.player.x)])
		app->ray.player.y += app->ray.plane.y * move;
	else
		app->ray.player.y -= app->ray.plane.y * move;
}

static void	move_wkey(t_total *app, double move)
{
	if (!app->map[(int)(app->ray.player.y)][(int)(app->ray.player.x
			+ app->ray.dir.x * 0.3)])
		app->ray.player.x += app->ray.dir.x * move;
	else
		app->ray.player.x -= app->ray.dir.x * move;
	if (!app->map[(int)(app->ray.player.y
			+ app->ray.dir.y * 0.3)][(int)(app->ray.player.x)])
		app->ray.player.y += app->ray.dir.y * move;
	else
		app->ray.player.y -= app->ray.dir.y * move;
}

static void	move_skey(t_total *app, double move)
{
	if (!app->map[(int)(app->ray.player.y)][(int)(app->ray.player.x
			- app->ray.dir.x * 0.3)])
		app->ray.player.x -= app->ray.dir.x * move;
	else
		app->ray.player.x += app->ray.dir.x * move;
	if (!app->map[(int)(app->ray.player.y
			- app->ray.dir.y * 0.3)][(int)(app->ray.player.x)])
		app->ray.player.y -= app->ray.dir.y * move;
	else
		app->ray.player.y += app->ray.dir.y * move;
}

int	key_hook(int keycode, t_total *app)
{
	if (keycode == W_KEY)
		move_wkey(app, app->move_speed);
	if (keycode == S_KEY)
		move_skey(app, app->move_speed);
	if (keycode == A_KEY)
		move_akey(app, app->move_speed);
	if (keycode == D_KEY)
		move_dkey(app, app->move_speed);
	if (keycode == LEFT_KEY || keycode == RIGHT_KEY)
		rotate_key(app, app->rotate_speed, keycode);
	if (keycode == ESC_KEY)
		mlx_exit(app);
	main_loop(app);
	return (0);
}
