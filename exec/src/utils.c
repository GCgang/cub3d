/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehjoo <jaehjoo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 12:02:41 by jaehjoo           #+#    #+#             */
/*   Updated: 2023/06/05 17:24:07 by jaehjoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

static void	set_plane(t_ray *ray, char tgt)
{
	if (tgt == 'N')
	{
		ray->plane.x = 0.66;
		ray->plane.y = 0;
	}
	else if (tgt == 'S')
	{
		ray->plane.x = -0.66;
		ray->plane.y = 0;
	}
	else if (tgt == 'E')
	{
		ray->plane.x = 0;
		ray->plane.y = 0.66;
	}
	else
	{
		ray->plane.x = 0;
		ray->plane.y = -0.66;
	}
}

void	set_dir(t_ray *ray, char tgt)
{
	if (tgt == 'N')
	{
		ray->dir.x = 0;
		ray->dir.y = -1;
	}
	else if (tgt == 'S')
	{
		ray->dir.x = 0;
		ray->dir.y = 1;
	}
	else if (tgt == 'E')
	{
		ray->dir.x = 1;
		ray->dir.y = 0;
	}
	else
	{
		ray->dir.x = -1;
		ray->dir.y = 0;
	}
	set_plane(ray, tgt);
}

void	set_player(int **map, int width, int height, t_vec *player)
{
	int		y;
	int		x;
	char	tgt;

	y = -1;
	while (++y < height)
	{
		x = -1;
		while (++x < width)
		{
			tgt = (char)map[y][x];
			if (tgt == 'N' || tgt == 'S' || tgt == 'E' || tgt == 'W')
			{
				player->x = x;
				player->y = y;
				return ;
			}
		}
	}
}

void	map_free(char **map, int height)
{
	int	y;

	y = -1;
	while (++y < height)
		free(map[y]);
	free(map);
}

void	ft_bzero(void *ptr, size_t num)
{
	size_t			idx;
	unsigned char	*temp;

	idx = 0;
	temp = (unsigned char *)ptr;
	while (idx < num)
	{
		*(temp + idx) = 0;
		idx++;
	}
}
