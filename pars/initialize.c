/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeoan <hyeoan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 20:12:53 by hyeoan            #+#    #+#             */
/*   Updated: 2023/06/07 12:49:31 by hyeoan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*u_p;

	u_p = (unsigned char *)b;
	while (len--)
	{
		*u_p++ = (unsigned char)c;
	}
	return (b);
}

void	initialize(t_game_info *game_info, \
								t_parse_info *parse_info, t_map_list *map_list)
{
	map_list->head_node = (t_map_node *)malloc(sizeof(t_map_node));
	if (map_list->head_node == NULL)
		exit_error_control("Error : malloc returned NULL.(initialize)\n", \
											game_info, parse_info, map_list);
	map_list->head_node->str = NULL;
	map_list->head_node->next = NULL;
	ft_memset((void *)game_info, 0, sizeof(t_game_info));
	ft_memset((void *)parse_info, 0, sizeof(t_parse_info));
}
