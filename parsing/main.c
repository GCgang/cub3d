/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeoan <hyeoan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 19:10:48 by jun               #+#    #+#             */
/*   Updated: 2023/06/05 15:19:26 by hyeoan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parse_data(t_game_info *game_info, \
							t_parse_info *parse_info, t_map_list *map_list)
{
	parse_info->line = get_next_line(parse_info->fd);
	while (parse_info->line != NULL)
	{
		if (parse_info->line[ft_strlen(parse_info->line) - 1] == '\n')
			parse_info->line[ft_strlen(parse_info->line) - 1] = '\0';
		parse_info->line_type = check_line_type(parse_info->line, parse_info);
		if (parse_info->line_type == CHECK_PATH)
			is_valid_texture_file_path(parse_info->line, game_info, \
														parse_info, map_list);
		else if (parse_info->line_type == CHECK_RGB)
			check_floor_and_ceiling_rgb(parse_info->line, game_info, \
														parse_info, map_list);
		else if (parse_info->line_type == ONLY_SPACE && game_info->height > 0)
			exit_error_control(MAP_SEPARATED_ERROR, game_info, \
														parse_info, map_list);
		else if (parse_info->line_type == CHECK_MAP)
			store_map_data_in_list(parse_info->line, game_info, \
														parse_info, map_list);
		free(parse_info->line);
		parse_info->line = get_next_line(parse_info->fd);
	}
}

void	leak(void)
{
	system("leaks cub3d");
}

int	main(int argc, char **argv)
{
	t_game_info		game_info;
	t_parse_info	parse_info;
	t_map_list		map_list;

	atexit(leak);
	if (argc != 2)
		exit_error_control(ARGUMENT_ERROR, &game_info, &parse_info, &map_list);
	initialize(&game_info, &parse_info, &map_list);
	check_file(argv[1], &game_info, &parse_info, &map_list);
	parse_data(&game_info, &parse_info, &map_list);
	convert_list_to_map_array(&game_info, &parse_info, &map_list);
	is_map_surround_by_wall(&game_info, &parse_info, &map_list);
	exit_error_control("all free\n", &game_info, &parse_info, &map_list);
}

	// printf("no = %s\n", game_info.no_texture_path);
	// printf("so = %s\n", game_info.so_texture_path);
	// printf("ea = %s\n", game_info.ea_texture_path);
	// printf("we = %s\n", game_info.we_texture_path);`
	// printf("floor = %d\n", game_info.floor_rgb);
	// printf("ceiling = %d\n", game_info.ceiling_rgb);
	// printf("height = %d\n", game_info.height);
	// printf("width = %d\n", game_info.width);
	// i = 0;
	// while (game_info.map[i] != NULL)
	// {
	// 	if (i <= 9)
	// 		printf(" ");
	// 	printf("map[%d] = %s\n",i, game_info.map[i]);
	// 	i++;
	// }
	// printf("%d %s\n", i, game_info.map[i]);