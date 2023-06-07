/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehjoo <jaehjoo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 12:00:29 by jaehjoo           #+#    #+#             */
/*   Updated: 2023/06/07 16:41:09 by jaehjoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec_bonus.h"

static void	minimap_put_pixel_to_img(t_img *img, int x, int y, int color)
{
	char	*dest;

	if (0 <= y && 0 <= x)
	{
		dest = img->img_addr + (y * img->size_len + x * (img->bpp / 8));
			*(unsigned int *)dest = color;
	}
}

static void	show_player(t_img *img, int box, t_vec player)
{
	t_vec	cur;
	int		x;
	int		y;

	cur.x = (int)(player.x * box);
	cur.y = (int)(player.y * box);
	y = -1;
	while (++y < box / 2)
	{
		x = -1;
		while (++x < box / 2)
		{
			minimap_put_pixel_to_img(img, cur.x + x, cur.y + y, 0xff6347);
			minimap_put_pixel_to_img(img, cur.x + x, cur.y - y, 0xff6347);
			minimap_put_pixel_to_img(img, cur.x - x, cur.y - y, 0xff6347);
			minimap_put_pixel_to_img(img, cur.x - x, cur.y + y, 0xff6347);
		}
	}
}

void	minimap(t_total *app)
{
	t_vec	map_win;
	t_vec	cur;
	int		square;

	square = app->win.x / 200;
	map_win.x = square * app->map_scale.x;
	map_win.y = square * app->map_scale.y;
	cur.y = -1;
	while (++cur.y < map_win.y)
	{
		cur.x = -1;
		while (++cur.x < map_win.x)
		{
			if (!((int)cur.x % square) || !((int)cur.y % square))
				minimap_put_pixel_to_img(&app->mlx.canvas,
					cur.x, cur.y, 0x808080);
			else if (!app->map[(int)cur.y / square][(int)cur.x / square])
				minimap_put_pixel_to_img(&app->mlx.canvas,
					cur.x, cur.y, 0x008080);
			else
				minimap_put_pixel_to_img(&app->mlx.canvas,
					cur.x, cur.y, 0xFFFFFF);
		}
	}
	show_player(&app->mlx.canvas, square, app->ray.player);
}
