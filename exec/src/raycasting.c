/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehjoo <jaehjoo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 12:01:07 by jaehjoo           #+#    #+#             */
/*   Updated: 2023/06/05 17:25:28 by jaehjoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

static void	find_step(t_ray *ray)
{
	if (ray->ray_dir.x < 0)
	{
		ray->step.x = -1;
		ray->side_dist.x = (ray->player.x - ray->map_loca[0])
			* ray->delta_dist.x;
	}
	else
	{
		ray->step.x = 1;
		ray->side_dist.x = (ray->map_loca[0] + 1.0 - ray->player.x)
			* ray->delta_dist.x;
	}
	if (ray->ray_dir.y < 0)
	{
		ray->step.y = -1;
		ray->side_dist.y = (ray->player.y - ray->map_loca[1])
			* ray->delta_dist.y;
	}
	else
	{
		ray->step.y = 1;
		ray->side_dist.y = (ray->map_loca[1] + 1.0 - ray->player.y)
			* ray->delta_dist.y;
	}
}

static void	wall_hit(t_total *app)
{
	while (app->ray.hit == 0)
	{
		if (app->ray.side_dist.x < app->ray.side_dist.y)
		{
			app->ray.side_dist.x += app->ray.delta_dist.x;
			app->ray.map_loca[0] += (int)app->ray.step.x;
			app->ray.side = 0;
		}
		else
		{
			app->ray.side_dist.y += app->ray.delta_dist.y;
			app->ray.map_loca[1] += (int)app->ray.step.y;
			app->ray.side = 1;
		}
		if (app->map[app->ray.map_loca[1]][app->ray.map_loca[0]] == 1)
			app->ray.hit = 1;
	}
}

void	raycasting(t_total *app)
{
	double	camera_x;
	int		x;

	x = 0;
	while (x < app->win.x)
	{
		camera_x = 2 * x / app->win.x - 1;
		app->ray.ray_dir.x = app->ray.dir.x + app->ray.plane.x * camera_x;
		app->ray.ray_dir.y = app->ray.dir.y + app->ray.plane.y * camera_x;
		app->ray.map_loca[0] = (int)app->ray.player.x;
		app->ray.map_loca[1] = (int)app->ray.player.y;
		app->ray.delta_dist.x = fabs(1 / app->ray.ray_dir.x);
		app->ray.delta_dist.y = fabs(1 / app->ray.ray_dir.y);
		app->ray.hit = 0;
		find_step(&app->ray);
		wall_hit(app);
		draw_texture(app, x);
		x++;
	}
}
