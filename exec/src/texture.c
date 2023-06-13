/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehjoo <jaehjoo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 12:01:12 by jaehjoo           #+#    #+#             */
/*   Updated: 2023/06/13 10:43:51 by jaehjoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

static void	calculate_wall_dist(t_total *app)
{
	if (app->ray.side == 0)
		app->ray.prep_wall_dist = (app->ray.map_loca[0] - app->ray.player.x
				+ (1 - app->ray.step.x) / 2) / app->ray.ray_dir.x;
	else
		app->ray.prep_wall_dist = (app->ray.map_loca[1] - app->ray.player.y
				+ (1 - app->ray.step.y) / 2) / app->ray.ray_dir.y;
}

static int	search_location(t_total *app)
{
	if (app->ray.ray_dir.y >= 0 && app->ray.side == 1)
		return (3);
	else if (app->ray.ray_dir.y < 0 && app->ray.side == 1)
		return (2);
	else if (app->ray.ray_dir.x > 0 && app->ray.side == 0)
		return (1);
	else
		return (0);
}

static int	calculate_tex(t_total *app)
{
	double	wall_x;
	int		tex;

	if (app->ray.side == 0)
		wall_x = app->ray.player.y
			+ app->ray.prep_wall_dist * app->ray.ray_dir.y;
	else
		wall_x = app->ray.player.x
			+ app->ray.prep_wall_dist * app->ray.ray_dir.x;
	wall_x -= floor(wall_x);
	tex = (int)(wall_x * (double)app->wall.texture);
	if (app->ray.side == 0 && app->ray.ray_dir.x > 0)
		tex = app->wall.texture - tex - 1;
	if (app->ray.side == 1 && app->ray.ray_dir.y < 0)
		tex = app->wall.texture - tex - 1;
	return (tex);
}

static void	input_color(t_total *app, t_vec tex)
{
	double	step;
	double	tex_pos;
	int		loca;
	char	*dest;

	step = 1.0 * app->wall.texture / app->wall.line_height;
	tex_pos = (app->wall.y_start - app->win.y / 2
			+ app->wall.line_height / 2) * step;
	loca = search_location(app);
	while (app->wall.y_start < app->wall.y_end)
	{
		tex.y = (int)tex_pos & (app->wall.texture - 1);
		tex_pos += step;
		dest = app->mlx.img[loca].img_addr + ((int)tex.y
				* app->mlx.img[loca].size_len + (int)tex.x
				* (app->mlx.img[loca].bpp / 8));
		app->wall.color = *(unsigned int *)dest;
		put_pixel_to_img(app, app->wall.y_start, app->wall.y_end, app->wall.x);
		app->wall.y_start++;
	}
}

void	draw_texture(t_total *app, int x)
{
	t_vec	tex;

	app->wall.x = x;
	calculate_wall_dist(app);
	tex.x = calculate_tex(app);
	app->wall.line_height = (int)(app->win.y / app->ray.prep_wall_dist);
	app->wall.y_start = -app->wall.line_height / 2 + app->win.y / 2;
	if (app->wall.y_start < 0)
		app->wall.y_start = 0;
	app->wall.y_end = app->wall.line_height / 2 + app->win.y / 2;
	if (app->wall.y_end >= app->win.y)
		app->wall.y_end = app->win.y - 1;
	input_color(app, tex);
}
