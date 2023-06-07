/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jun <jun@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 15:33:19 by jaehjoo           #+#    #+#             */
/*   Updated: 2023/06/07 23:32:35 by jun              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/init.h"

int	main(int argc, char **argv)
{
	t_game_info		game_info;
	t_parse_info	parse_info;
	t_map_list		map_list;

	if (argc != 2)
		exit_error_control(ARGUMENT_ERROR, &game_info, &parse_info, &map_list);
	initialize(&game_info, &parse_info, &map_list);
	check_file(argv[1], &game_info, &parse_info, &map_list);
	parse_data(&game_info, &parse_info, &map_list);
	convert_list_to_map_array(&game_info, &parse_info, &map_list);
	is_map_surround_by_wall(&game_info, &parse_info, &map_list);
	finalize(&map_list);
	exec(&game_info);
	return (0);
}
