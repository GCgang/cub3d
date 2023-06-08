/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bonus.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehjoo <jaehjoo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 11:59:42 by jaehjoo           #+#    #+#             */
/*   Updated: 2023/06/07 16:40:35 by jaehjoo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_BONUS_H
# define EXEC_BONUS_H

# include "../../share/include/init_bonus.h"
# include "structure_bonus.h"
# include "../../minilibx/mlx.h"
# include "mlx_key_bonus.h"

void	chk_mlx_hook(t_total *app);
int		main_loop(t_total *app);
void	raycasting(t_total *app);
void	put_pixel_to_img(t_total *app, int y_s, int y_e, int x);
void	minimap(t_total *app);
void	draw_texture(t_total *app, int x);
int		key_hook(int keycode, t_total *app);
int		mouse_hook(int x, int y, t_total *app);
int		mlx_exit(t_total *app);
void	rotate_key(t_total *app, double rot, int keycode);
int		map_free(char **trans_map, int **map, int height, int map_h);
void	set_dir(t_ray *ray, char tgt);
void	ft_bzero(void *ptr, size_t num);
void	set_player(int **map, int width, int height, t_vec *player);
int		**map_set(char **trans_map, int **map, int width, int height);
int		image_free(t_game_info *game_info, t_total *app, int flag);
int		print_error(char *str);

#endif
