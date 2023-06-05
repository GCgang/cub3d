/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehjoo <jaehjoo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 12:03:00 by jaehjoo           #+#    #+#             */
/*   Updated: 2023/06/05 16:54:39 by jaehjoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURE_H
# define STRUCTURE_H

typedef struct s_vec
{
	double	x;
	double	y;
}	t_vec;

typedef struct s_img
{
	void	*img;
	void	*img_addr;
	int		bpp;
	int		size_len;
	int		endian;	
}	t_img;

typedef struct s_ray
{
	t_vec	player;
	t_vec	dir;
	t_vec	plane;
	t_vec	ray_dir;
	t_vec	side_dist;
	t_vec	delta_dist;
	t_vec	step;
	double	prep_wall_dist;
	int		map_loca[2];
	int		hit;
	int		side;
}	t_ray;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	t_img	canvas;
	t_img	img[4];
	int		mouse;
}	t_mlx;

typedef struct s_wall
{
	int	texture;
	int	color;
	int	x;
	int	line_height;
	int	y_start;
	int	y_end;
}	t_wall;

typedef struct s_total
{
	int		**map;
	t_vec	map_scale;
	t_ray	ray;
	int		bg_color[2];
	t_mlx	mlx;
	t_vec	win;
	t_wall	wall;
	double	move_speed;
	double	rotate_speed;
}	t_total;

#endif
