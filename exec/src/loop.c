/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehjoo <jaehjoo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 12:00:24 by jaehjoo           #+#    #+#             */
/*   Updated: 2023/06/07 15:14:27 by jaehjoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

void	put_pixel_to_img(t_total *app, int y_s, int y_e, int x)
{
	t_img	*img;
	char	*dest;

	img = &app->mlx.canvas;
	if (0 <= y_s && y_s <= y_e
		&& y_s < app->win.y && 0 <= x && x < app->win.x)
	{
		dest = img->img_addr + (y_s * img->size_len + x * (img->bpp / 8));
		*(unsigned int *)dest = app->wall.color;
	}
}

static void	draw_bg(t_total *app, int win_x, int win_y)
{
	t_vec	cur;

	cur.x = 0;
	cur.y = 0;
	while (cur.y < win_y)
	{
		if (cur.y <= win_y / 2)
			app->wall.color = app->bg_color[0];
		else
			app->wall.color = app->bg_color[1];
		cur.x = 0;
		while (cur.x < win_x)
		{
			put_pixel_to_img(app, cur.y, app->win.y, cur.x);
			cur.x++;
		}
		cur.y++;
	}
}

int	main_loop(t_total *app)
{
	draw_bg(app, app->win.x, app->win.y);
	raycasting(app);
	minimap(app);
	mlx_put_image_to_window(app->mlx.mlx, app->mlx.win,
		app->mlx.canvas.img, 0, 0);
	return (0);
}
